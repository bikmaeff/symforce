# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------

"""
Demonstrates solving a 2D triangulation problem with SymForce. The goal is for a robot
in a 2D plane to compute its trajectory given distance measurements from wheel odometry
and relative bearing angle measurements to known landmarks in the environment.
"""
# pylint: disable=ungrouped-imports

# -----------------------------------------------------------------------------
# Define residual functions
# -----------------------------------------------------------------------------
from symforce import geo
from symforce import sympy as sm
from symforce import typing as T


def bearing_residual(
    pose: geo.Pose2, landmark: geo.V2, angle: T.Scalar, epsilon: T.Scalar
) -> geo.V1:
    """
    Residual from a relative bearing mesurement of a 2D pose to a landmark.
    """
    t_body = pose.inverse() * landmark
    predicted_angle = sm.atan2(t_body[1], t_body[0], epsilon=epsilon)
    return geo.V1(sm.wrap_angle(predicted_angle - angle))


def odometry_residual(
    pose_a: geo.Pose2, pose_b: geo.Pose2, dist: T.Scalar, epsilon: T.Scalar
) -> geo.V1:
    """
    Residual from the scalar distance between two poses.
    """
    return geo.V1((pose_b.t - pose_a.t).norm(epsilon=epsilon) - dist)


# -----------------------------------------------------------------------------
# Create a set of factors to represent the full problem
# -----------------------------------------------------------------------------
from symforce.opt.factor import Factor


def build_factors(num_poses: int, num_landmarks: int) -> T.Iterator[Factor]:
    """
    Build factors for a problem of the given dimensionality.
    """
    for i in range(num_poses - 1):
        yield Factor(
            residual=odometry_residual,
            keys=[f"poses[{i}]", f"poses[{i + 1}]", f"distances[{i}]", "epsilon"],
        )

    for i in range(num_poses):
        for j in range(num_landmarks):
            yield Factor(
                residual=bearing_residual,
                keys=[f"poses[{i}]", f"landmarks[{j}]", f"angles[{i}][{j}]", "epsilon"],
            )


# -----------------------------------------------------------------------------
# Instantiate, optimize, and visualize
# -----------------------------------------------------------------------------
import numpy as np
from symforce.opt.optimizer import Optimizer
from symforce.values import Values


def main() -> None:
    # Create a problem setup and initial guess
    num_poses = 3
    num_landmarks = 3
    initial_values = Values(
        poses=[geo.Pose2.identity()] * num_poses,
        landmarks=[geo.V2(-2, 2), geo.V2(1, -3), geo.V2(5, 2)],
        distances=[1.7, 1.4],
        angles=np.deg2rad([[55, 245, -35], [95, 220, -20], [125, 220, -20]]).tolist(),
        epsilon=sm.default_epsilon,
    )

    # Create factors
    factors = build_factors(num_poses=num_poses, num_landmarks=num_landmarks)

    # Select the keys to optimize - the rest will be held constant
    optimized_keys = [f"poses[{i}]" for i in range(num_poses)]

    # Create the optimizer
    optimizer = Optimizer(
        factors=factors,
        optimized_keys=optimized_keys,
        debug_stats=True,  # Return problem stats for every iteration
        params=Optimizer.Params(verbose=True),  # Customize optimizer behavior
    )

    # Solve and return the result
    result = optimizer.optimize(initial_values)

    # Print some values
    print(f"Num iterations: {len(result.iteration_stats) - 1}")
    print(f"Final error: {result.error():.6f}")

    for i, pose in enumerate(result.optimized_values["poses"]):
        print(f"Pose {i}: t = {pose.position()}, heading = {pose.rotation().to_tangent()[0]}")

    # Plot the result
    # TODO(hayk): mypy gives the below error, but a relative import also doesn't work.
    # Skipping analyzing "symforce.examples.robot_2d_triangulation.plotting":
    #     found module but no type hints or library stubs
    from symforce.examples.robot_2d_triangulation.plotting import plot_solution

    plot_solution(optimizer, result)


# -----------------------------------------------------------------------------
# (Optional) Generate C++ functions for residuals with on-manifold jacobians
# -----------------------------------------------------------------------------
from symforce.codegen import Codegen, CppConfig


def generate_bearing_residual_code() -> None:
    """
    Generate C++ code for the bearing residual function. A C++ Factor can then be
    constructed and optimized from this function without any Python dependency.
    """
    # Create a Codegen object for the symbolic residual function, targeted at C++
    codegen = Codegen.function(bearing_residual, config=CppConfig())

    # Generate the function and print the code
    metadata = codegen.generate_function()
    print(metadata.generated_files[0].read_text())

    # Create a Codegen object that computes a linearization from the residual Codegen object,
    # by introspecting and symbolically differentiating the given arguments
    codegen_with_linearization = codegen.with_linearization(which_args=["pose"])

    # Generate the function and print the code
    metadata = codegen_with_linearization.generate_function()
    print(metadata.generated_files[0].read_text())


if __name__ == "__main__":
    main()

    # Uncomment this to print generated C++ code
    # generate_bearing_residual_code()
