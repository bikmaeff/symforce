// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>
#include <sym/rot2.h>

namespace sym {

/**
 * Residual that penalizes the difference between a value and prior (desired / measured value).
 *
 * In vector space terms that would be:
 *     prior - value
 *
 * In lie group terms:
 *     to_tangent(compose(inverse(value), prior))
 *
 * Args:
 *     sqrt_info: Square root information matrix to whiten residual. This can be computed from
 *                a covariance matrix as the cholesky decomposition of the inverse. In the case
 *                of a diagonal it will contain 1/sigma values. Must match the tangent dim.
 *     jacobian: (1x1) jacobian of res wrt arg value (1)
 *     hessian: (1x1) Gauss-Newton hessian for arg value (1)
 *     rhs: (1x1) Gauss-Newton rhs for arg value (1)
 */
template <typename Scalar>
void PriorFactorRot2(const sym::Rot2<Scalar>& value, const sym::Rot2<Scalar>& prior,
                     const Eigen::Matrix<Scalar, 1, 1>& sqrt_info, const Scalar epsilon,
                     Eigen::Matrix<Scalar, 1, 1>* const res = nullptr,
                     Eigen::Matrix<Scalar, 1, 1>* const jacobian = nullptr,
                     Eigen::Matrix<Scalar, 1, 1>* const hessian = nullptr,
                     Eigen::Matrix<Scalar, 1, 1>* const rhs = nullptr) {
  // Total ops: 41

  // Input arrays
  const Eigen::Matrix<Scalar, 2, 1>& _value = value.Data();
  const Eigen::Matrix<Scalar, 2, 1>& _prior = prior.Data();

  // Intermediate terms (11)
  const Scalar _tmp0 = 1.0 / (std::pow<Scalar>(_prior[0], 2) + std::pow<Scalar>(_prior[1], 2));
  const Scalar _tmp1 = _prior[0] * _tmp0;
  const Scalar _tmp2 = _prior[1] * _tmp0;
  const Scalar _tmp3 = _tmp1 * _value[1] - _tmp2 * _value[0];
  const Scalar _tmp4 = _tmp1 * _value[0] + _tmp2 * _value[1];
  const Scalar _tmp5 = sqrt_info(0, 0) * std::atan2(_tmp3, _tmp4);
  const Scalar _tmp6 = 1.0 / (_tmp4);
  const Scalar _tmp7 = std::pow<Scalar>(_tmp4, 2);
  const Scalar _tmp8 = _tmp3 / _tmp7;
  const Scalar _tmp9 = _tmp7 * sqrt_info(0, 0) / (std::pow<Scalar>(_tmp3, 2) + _tmp7);
  const Scalar _tmp10 = _tmp9 * _value[0] * (_tmp1 * _tmp6 - _tmp2 * _tmp8) -
                        _tmp9 * _value[1] * (-_tmp1 * _tmp8 - _tmp2 * _tmp6);

  // Output terms (4)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 1, 1>& _res = (*res);

    _res(0, 0) = _tmp5;
  }

  if (jacobian != nullptr) {
    Eigen::Matrix<Scalar, 1, 1>& _jacobian = (*jacobian);

    _jacobian(0, 0) = _tmp10;
  }

  if (hessian != nullptr) {
    Eigen::Matrix<Scalar, 1, 1>& _hessian = (*hessian);

    _hessian(0, 0) = std::pow<Scalar>(_tmp10, 2);
  }

  if (rhs != nullptr) {
    Eigen::Matrix<Scalar, 1, 1>& _rhs = (*rhs);

    _rhs(0, 0) = _tmp10 * _tmp5;
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
