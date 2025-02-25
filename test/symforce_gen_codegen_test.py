# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------

import math
import os
import sys

import symforce
from symforce import cam
from symforce import geo
from symforce import ops
from symforce import python_util
from symforce import sympy as sm
from symforce import typing as T
from symforce import codegen
from symforce.codegen import cam_package_codegen
from symforce.codegen import codegen_util
from symforce.codegen import geo_factors_codegen
from symforce.codegen import geo_package_codegen
from symforce.codegen import slam_factors_codegen
from symforce.codegen import sym_util_package_codegen
from symforce.codegen import template_util
from symforce.test_util import TestCase, symengine_only
from symforce import path_util

SYMFORCE_DIR = os.path.dirname(os.path.dirname(__file__))
TEST_DATA_DIR = os.path.join(
    SYMFORCE_DIR, "test", "symforce_function_codegen_test_data", symforce.get_backend()
)


class SymforceGenCodegenTest(TestCase):
    """
    Generate everything that goes into symforce/gen
    """

    def generate_cam_example_function(self, output_dir: str) -> None:
        def pixel_to_ray_and_back(
            pixel: geo.Vector2, cam: cam.LinearCameraCal, epsilon: T.Scalar = 0
        ) -> geo.Vector2:
            """
            Transform a given pixel into a ray and project the ray back to
            pixel coordinates. Input and output should match.
            """
            camera_ray, _ = cam.camera_ray_from_pixel(pixel, epsilon)
            reprojected_pixel, _ = cam.pixel_from_camera_point(camera_ray, epsilon)
            return reprojected_pixel

        # Create the specification
        namespace = "cam_function_codegen_test"
        my_func = codegen.Codegen.function(func=pixel_to_ray_and_back, config=codegen.CppConfig())
        cpp_data = my_func.generate_function(output_dir=output_dir, namespace=namespace)

        # Compare against the checked-in test data
        self.compare_or_update_directory(
            actual_dir=os.path.join(output_dir, "cpp/symforce/cam_function_codegen_test"),
            expected_dir=os.path.join(
                TEST_DATA_DIR, "symforce_gen_codegen_test_data", "cam_function_codegen_test"
            ),
        )

    def generate_tangent_d_storage_functions(self, output_dir: str) -> None:
        for cls in geo_package_codegen.DEFAULT_GEO_TYPES:
            tangent_D_storage_codegen = codegen.Codegen.function(
                func=ops.LieGroupOps.tangent_D_storage,
                input_types=[cls],
                config=codegen.CppConfig(),
            )
            tangent_D_storage_codegen.generate_function(
                output_dir=output_dir,
                generated_file_name="tangent_d_storage_" + cls.__name__.lower(),
            )

        # Compare against the checked-in test data
        self.compare_or_update_directory(
            actual_dir=os.path.join(output_dir, "cpp/symforce/sym"),
            expected_dir=os.path.join(
                TEST_DATA_DIR, "symforce_gen_codegen_test_data", "tangent_d_storage"
            ),
        )

    def test_gen_package_codegen_python(self) -> None:
        """
        Test Python code generation
        """
        output_dir = self.make_output_dir("sf_gen_codegen_test_")

        cam_package_codegen.generate(config=codegen.PythonConfig(), output_dir=output_dir)
        template_util.render_template(
            template_path=os.path.join(template_util.PYTHON_TEMPLATE_DIR, "setup.py.jinja"),
            output_path=os.path.join(output_dir, "setup.py"),
            data=dict(
                package_name="symforce-sym",
                version=symforce.__version__,
                description="generated numerical python package",
                long_description="generated numerical python package",
            ),
        )

        # Test against checked-in geo package (only on SymEngine)
        if symforce.get_backend() == "symengine":
            self.compare_or_update_directory(
                actual_dir=os.path.join(output_dir, "sym"),
                expected_dir=os.path.join(SYMFORCE_DIR, "gen", "python", "sym"),
            )
            self.compare_or_update_file(
                new_file=os.path.join(output_dir, "setup.py"),
                path=os.path.join(SYMFORCE_DIR, "gen", "python", "setup.py"),
            )

        # Compare against the checked-in tests
        for test_name in ("cam_package_python_test.py", "geo_package_python_test.py"):
            generated_code_file = os.path.join(output_dir, "tests", test_name)

            self.compare_or_update_file(
                path=os.path.join(SYMFORCE_DIR, "test", test_name),
                new_file=generated_code_file,
            )

            # Run generated example / test from disk in a standalone process
            current_python = sys.executable
            python_util.execute_subprocess([current_python, generated_code_file])

        # Also hot load package directly in to this process
        geo_pkg = codegen_util.load_generated_package("sym", os.path.join(output_dir, "sym"))

        # Test something basic from the hot loaded package
        rot = geo_pkg.Rot3.from_tangent([math.pi / 2, 0, 0])
        rot_inv = rot.inverse()
        identity_expected = rot * rot_inv
        identity_actual = geo_pkg.Rot3.identity()
        for i in range(len(identity_expected.data)):
            self.assertAlmostEqual(identity_expected.data[i], identity_actual.data[i], places=7)

    # This is so slow on sympy that we disable it entirely
    @symengine_only
    def test_gen_package_codegen_cpp(self) -> None:
        """
        Test C++ code generation
        """
        output_dir = self.make_output_dir("sf_gen_codegen_test_")

        # Prior factors, between factors, and SLAM factors for C++.
        geo_factors_codegen.generate(os.path.join(output_dir, "sym"))
        slam_factors_codegen.generate(os.path.join(output_dir, "sym"))

        # Generate typedefs.h
        sym_util_package_codegen.generate(config=codegen.CppConfig(), output_dir=output_dir)

        # Generate cam package, geo package, and tests
        # This calls geo_package_codegen.generate internally
        cam_package_codegen.generate(config=codegen.CppConfig(), output_dir=output_dir)

        # Check against existing generated package (only on SymEngine)
        self.compare_or_update_directory(
            actual_dir=os.path.join(output_dir, "sym"),
            expected_dir=os.path.join(SYMFORCE_DIR, "gen", "cpp", "sym"),
        )

        # Generate functions for testing tangent_D_storage numerical derivatives
        self.generate_tangent_d_storage_functions(output_dir)

        # Generate function that uses camera object as argument
        self.generate_cam_example_function(output_dir)

        # Compare against the checked-in tests
        for test_name in (
            "cam_package_cpp_test.cc",
            "cam_function_codegen_cpp_test.cc",
            "geo_package_cpp_test.cc",
        ):
            self.compare_or_update_file(
                path=os.path.join(SYMFORCE_DIR, "test", test_name),
                new_file=os.path.join(output_dir, "tests", test_name),
            )


if __name__ == "__main__":
    TestCase.main()
