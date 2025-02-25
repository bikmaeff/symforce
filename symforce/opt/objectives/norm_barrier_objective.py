# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------
from __future__ import annotations

from dataclasses import dataclass

from symforce import geo
from symforce.opt import objective, noise_models, barrier_functions
from symforce.opt.residual_block import ResidualBlock
from symforce import typing as T


class NormBarrierObjective(objective.TimestepObjective):
    @dataclass
    class Params:
        """
        Fields:
            norm_nominal: Value of the norm at which the error is equal to error_nominal.
            error_nominal: Error returned when the norm is equal to `norm_nominal`.
            dist_zero_to_nominal: The distance from norm_nominal to the region of zero error. Must
                be a positive number.
        """

        norm_nominal: T.Scalar
        error_nominal: T.Scalar
        dist_zero_to_nominal: T.Scalar

    @dataclass
    class ExtraValues:
        """
        Fields:
            unwhitened_residual: Error after applying the barrier function but before applying the
                cost scaling.
        """

        unwhitened_residual: geo.V1

    @staticmethod
    def residual_at_timestep(
        vector: geo.Matrix,
        params: NormBarrierObjective.Params,
        epsilon: T.Scalar,
        cost_scaling: T.Scalar = 1,
        power: T.Scalar = 1,
    ) -> ResidualBlock:
        """
        Returns the residual block for the given timestep, where the residual is computed by
        applying a max barrier function to the norm of the given vector, and then optionally scaling
        the corresponding cost in the overall optimization problem by `cost_scaling`.

        Args:
            vector: Vector whose norm we wish to apply a barrier to.
            params: Parameters defining the barrier function.
            power: Power of the barrier function. Defaults to 1, producing a linear barrier function
                in the residual, which corresponds to a quadratic cost in the overall optimization
                problem.
            cost_scaling: Optional scaling parameter. Corresponds to multiplying the cost in the
                overall optimization problem by a constant.
        """
        unwhitened_residual = geo.V1(
            barrier_functions.max_power_barrier(
                x=vector.norm(epsilon),
                x_nominal=params.norm_nominal,
                error_nominal=params.error_nominal,
                dist_zero_to_nominal=params.dist_zero_to_nominal,
                power=power,
            )
        )

        noise_model = noise_models.IsotropicNoiseModel(scalar_information=cost_scaling)
        whitened_residual = noise_model.whiten(unwhitened_residual)

        return ResidualBlock(
            residual=whitened_residual,
            extra_values=NormBarrierObjective.ExtraValues(unwhitened_residual=unwhitened_residual),
        )
