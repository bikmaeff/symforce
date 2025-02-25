# -----------------------------------------------------------------------------
# This file was autogenerated by symforce from template:
#     python_templates/tests/geo_package_python_test.py.jinja
# Do NOT modify by hand.
# -----------------------------------------------------------------------------


# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------

import numpy as np
import os
import sys
import unittest

# Add the generated package to the path
sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

import sym


class GeoPackageTest(unittest.TestCase):
    """
    Tests for Python runtime geometry types. Mostly checking basic generation logic
    since the math is tested comprehensively in symbolic form.
    """

    def setUp(self):
        # type: () -> None
        np.random.seed(42)
        # Store verbosity flag so tests can use
        self.verbose = ("-v" in sys.argv) or ("--verbose" in sys.argv)

    def test_storage_ops_Rot2(self):
        # type: () -> None
        """
        Tests:
            sym.Rot2 StorageOps
        """

        geo_class = sym.Rot2
        print("*** Testing StorageOps: " + geo_class.__name__ + " ***")

        value = geo_class()
        self.assertEqual(len(value.data), geo_class.storage_dim())

        vec = value.to_storage()
        self.assertTrue(len(vec) > 0)
        self.assertEqual(len(vec), geo_class.storage_dim())
        for i, element in enumerate(vec):
            self.assertEqual(element, value.data[i])

        value2 = geo_class.from_storage(vec)
        self.assertEqual(value.data, value2.data)
        vec[0] = 2.1
        value3 = geo_class.from_storage(vec)
        self.assertNotEqual(value.data, value3.data)

    def test_group_ops_Rot2(self):
        # type: () -> None
        """
        Tests:
            sym.Rot2 GroupOps
        """
        geo_class = sym.Rot2
        group_ops = sym.ops.rot2.GroupOps
        print("*** Testing GroupOps: " + geo_class.__name__ + " ***")

        identity = geo_class()

        # TODO(Nathan): Consider reorganizing how the generated python geo package is structured so that
        # each class doesn't have to use helper functions to call the underlying group_ops functions
        # Example using the underlying group_ops implementation:
        self.assertEqual(identity, group_ops.identity())

        # Example using the helper functions:
        self.assertEqual(identity, geo_class.identity())
        self.assertEqual(identity, identity.compose(identity))
        self.assertEqual(identity, identity.inverse())
        self.assertEqual(identity, identity.between(identity))

    def test_lie_group_ops_Rot2(self):
        # type: () -> None
        """
        Tests:
            sym.Rot2 LieGroupOps
        """

        geo_class = sym.Rot2
        print("*** Testing LieGroupOps: " + geo_class.__name__ + " ***")

        tangent_dim = geo_class.tangent_dim()
        self.assertTrue(tangent_dim > 0)
        self.assertTrue(tangent_dim <= geo_class.storage_dim())

        perturbation = np.random.rand(tangent_dim).tolist()
        value = geo_class.from_tangent(perturbation)
        recovered_perturbation = geo_class.to_tangent(value)
        np.testing.assert_almost_equal(perturbation, recovered_perturbation)

        identity = geo_class.identity()
        recovered_identity = value.retract([-x for x in recovered_perturbation])
        np.testing.assert_almost_equal(recovered_identity.to_storage(), identity.to_storage())

        perturbation_zero = identity.local_coordinates(recovered_identity)
        np.testing.assert_almost_equal(perturbation_zero, np.zeros(tangent_dim))

    def test_custom_methods_Rot2(self):
        # type: () -> None
        """
        Tests:
            sym.Rot2 custom methods
        """
        geo_class = sym.Rot2
        print("*** Testing Custom Methods: " + geo_class.__name__ + " ***")

        tangent_dim = geo_class.tangent_dim()
        element = geo_class.from_tangent(np.random.normal(size=tangent_dim).tolist())

        vector = np.random.normal(size=2)
        matrix = element.to_rotation_matrix()
        np.testing.assert_almost_equal(np.matmul(matrix, vector), element * vector)

    def test_storage_ops_Pose2(self):
        # type: () -> None
        """
        Tests:
            sym.Pose2 StorageOps
        """

        geo_class = sym.Pose2
        print("*** Testing StorageOps: " + geo_class.__name__ + " ***")

        value = geo_class()
        self.assertEqual(len(value.data), geo_class.storage_dim())

        vec = value.to_storage()
        self.assertTrue(len(vec) > 0)
        self.assertEqual(len(vec), geo_class.storage_dim())
        for i, element in enumerate(vec):
            self.assertEqual(element, value.data[i])

        value2 = geo_class.from_storage(vec)
        self.assertEqual(value.data, value2.data)
        vec[0] = 2.1
        value3 = geo_class.from_storage(vec)
        self.assertNotEqual(value.data, value3.data)

    def test_group_ops_Pose2(self):
        # type: () -> None
        """
        Tests:
            sym.Pose2 GroupOps
        """
        geo_class = sym.Pose2
        group_ops = sym.ops.pose2.GroupOps
        print("*** Testing GroupOps: " + geo_class.__name__ + " ***")

        identity = geo_class()

        # TODO(Nathan): Consider reorganizing how the generated python geo package is structured so that
        # each class doesn't have to use helper functions to call the underlying group_ops functions
        # Example using the underlying group_ops implementation:
        self.assertEqual(identity, group_ops.identity())

        # Example using the helper functions:
        self.assertEqual(identity, geo_class.identity())
        self.assertEqual(identity, identity.compose(identity))
        self.assertEqual(identity, identity.inverse())
        self.assertEqual(identity, identity.between(identity))

    def test_lie_group_ops_Pose2(self):
        # type: () -> None
        """
        Tests:
            sym.Pose2 LieGroupOps
        """

        geo_class = sym.Pose2
        print("*** Testing LieGroupOps: " + geo_class.__name__ + " ***")

        tangent_dim = geo_class.tangent_dim()
        self.assertTrue(tangent_dim > 0)
        self.assertTrue(tangent_dim <= geo_class.storage_dim())

        perturbation = np.random.rand(tangent_dim).tolist()
        value = geo_class.from_tangent(perturbation)
        recovered_perturbation = geo_class.to_tangent(value)
        np.testing.assert_almost_equal(perturbation, recovered_perturbation)

        identity = geo_class.identity()
        recovered_identity = value.retract([-x for x in recovered_perturbation])
        np.testing.assert_almost_equal(recovered_identity.to_storage(), identity.to_storage())

        perturbation_zero = identity.local_coordinates(recovered_identity)
        np.testing.assert_almost_equal(perturbation_zero, np.zeros(tangent_dim))

    def test_custom_methods_Pose2(self):
        # type: () -> None
        """
        Tests:
            sym.Pose2 custom methods
        """
        geo_class = sym.Pose2
        print("*** Testing Custom Methods: " + geo_class.__name__ + " ***")

        tangent_dim = geo_class.tangent_dim()
        element = geo_class.from_tangent(np.random.normal(size=tangent_dim).tolist())

        vector = np.random.normal(size=2)
        vector_as_element = geo_class(t=vector.tolist())
        np.testing.assert_almost_equal(element * vector, (element * vector_as_element).position())

    def test_storage_ops_Rot3(self):
        # type: () -> None
        """
        Tests:
            sym.Rot3 StorageOps
        """

        geo_class = sym.Rot3
        print("*** Testing StorageOps: " + geo_class.__name__ + " ***")

        value = geo_class()
        self.assertEqual(len(value.data), geo_class.storage_dim())

        vec = value.to_storage()
        self.assertTrue(len(vec) > 0)
        self.assertEqual(len(vec), geo_class.storage_dim())
        for i, element in enumerate(vec):
            self.assertEqual(element, value.data[i])

        value2 = geo_class.from_storage(vec)
        self.assertEqual(value.data, value2.data)
        vec[0] = 2.1
        value3 = geo_class.from_storage(vec)
        self.assertNotEqual(value.data, value3.data)

    def test_group_ops_Rot3(self):
        # type: () -> None
        """
        Tests:
            sym.Rot3 GroupOps
        """
        geo_class = sym.Rot3
        group_ops = sym.ops.rot3.GroupOps
        print("*** Testing GroupOps: " + geo_class.__name__ + " ***")

        identity = geo_class()

        # TODO(Nathan): Consider reorganizing how the generated python geo package is structured so that
        # each class doesn't have to use helper functions to call the underlying group_ops functions
        # Example using the underlying group_ops implementation:
        self.assertEqual(identity, group_ops.identity())

        # Example using the helper functions:
        self.assertEqual(identity, geo_class.identity())
        self.assertEqual(identity, identity.compose(identity))
        self.assertEqual(identity, identity.inverse())
        self.assertEqual(identity, identity.between(identity))

    def test_lie_group_ops_Rot3(self):
        # type: () -> None
        """
        Tests:
            sym.Rot3 LieGroupOps
        """

        geo_class = sym.Rot3
        print("*** Testing LieGroupOps: " + geo_class.__name__ + " ***")

        tangent_dim = geo_class.tangent_dim()
        self.assertTrue(tangent_dim > 0)
        self.assertTrue(tangent_dim <= geo_class.storage_dim())

        perturbation = np.random.rand(tangent_dim).tolist()
        value = geo_class.from_tangent(perturbation)
        recovered_perturbation = geo_class.to_tangent(value)
        np.testing.assert_almost_equal(perturbation, recovered_perturbation)

        identity = geo_class.identity()
        recovered_identity = value.retract([-x for x in recovered_perturbation])
        np.testing.assert_almost_equal(recovered_identity.to_storage(), identity.to_storage())

        perturbation_zero = identity.local_coordinates(recovered_identity)
        np.testing.assert_almost_equal(perturbation_zero, np.zeros(tangent_dim))

    def test_custom_methods_Rot3(self):
        # type: () -> None
        """
        Tests:
            sym.Rot3 custom methods
        """
        geo_class = sym.Rot3
        print("*** Testing Custom Methods: " + geo_class.__name__ + " ***")

        tangent_dim = geo_class.tangent_dim()
        element = geo_class.from_tangent(np.random.normal(size=tangent_dim).tolist())

        vector = np.random.normal(size=3)
        matrix = element.to_rotation_matrix()
        np.testing.assert_almost_equal(np.matmul(matrix, vector), element * vector)

    def test_storage_ops_Pose3(self):
        # type: () -> None
        """
        Tests:
            sym.Pose3 StorageOps
        """

        geo_class = sym.Pose3
        print("*** Testing StorageOps: " + geo_class.__name__ + " ***")

        value = geo_class()
        self.assertEqual(len(value.data), geo_class.storage_dim())

        vec = value.to_storage()
        self.assertTrue(len(vec) > 0)
        self.assertEqual(len(vec), geo_class.storage_dim())
        for i, element in enumerate(vec):
            self.assertEqual(element, value.data[i])

        value2 = geo_class.from_storage(vec)
        self.assertEqual(value.data, value2.data)
        vec[0] = 2.1
        value3 = geo_class.from_storage(vec)
        self.assertNotEqual(value.data, value3.data)

    def test_group_ops_Pose3(self):
        # type: () -> None
        """
        Tests:
            sym.Pose3 GroupOps
        """
        geo_class = sym.Pose3
        group_ops = sym.ops.pose3.GroupOps
        print("*** Testing GroupOps: " + geo_class.__name__ + " ***")

        identity = geo_class()

        # TODO(Nathan): Consider reorganizing how the generated python geo package is structured so that
        # each class doesn't have to use helper functions to call the underlying group_ops functions
        # Example using the underlying group_ops implementation:
        self.assertEqual(identity, group_ops.identity())

        # Example using the helper functions:
        self.assertEqual(identity, geo_class.identity())
        self.assertEqual(identity, identity.compose(identity))
        self.assertEqual(identity, identity.inverse())
        self.assertEqual(identity, identity.between(identity))

    def test_lie_group_ops_Pose3(self):
        # type: () -> None
        """
        Tests:
            sym.Pose3 LieGroupOps
        """

        geo_class = sym.Pose3
        print("*** Testing LieGroupOps: " + geo_class.__name__ + " ***")

        tangent_dim = geo_class.tangent_dim()
        self.assertTrue(tangent_dim > 0)
        self.assertTrue(tangent_dim <= geo_class.storage_dim())

        perturbation = np.random.rand(tangent_dim).tolist()
        value = geo_class.from_tangent(perturbation)
        recovered_perturbation = geo_class.to_tangent(value)
        np.testing.assert_almost_equal(perturbation, recovered_perturbation)

        identity = geo_class.identity()
        recovered_identity = value.retract([-x for x in recovered_perturbation])
        np.testing.assert_almost_equal(recovered_identity.to_storage(), identity.to_storage())

        perturbation_zero = identity.local_coordinates(recovered_identity)
        np.testing.assert_almost_equal(perturbation_zero, np.zeros(tangent_dim))

    def test_custom_methods_Pose3(self):
        # type: () -> None
        """
        Tests:
            sym.Pose3 custom methods
        """
        geo_class = sym.Pose3
        print("*** Testing Custom Methods: " + geo_class.__name__ + " ***")

        tangent_dim = geo_class.tangent_dim()
        element = geo_class.from_tangent(np.random.normal(size=tangent_dim).tolist())

        vector = np.random.normal(size=3)
        vector_as_element = geo_class(t=vector.tolist())
        np.testing.assert_almost_equal(element * vector, (element * vector_as_element).position())


if __name__ == "__main__":
    unittest.main()
