// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <Eigen/Dense>
#include <sym/rot3.h>

namespace codegen_nan_test {

/**
 * This function was autogenerated. Do not modify by hand.
 *
 * Args:
 *     R1: Rot3
 *     e: Scalar
 *
 * Outputs:
 *     dist_D_R1: Scalar
 *
 */
template <typename Scalar>
Scalar IdentityDistJacobian(const sym::Rot3<Scalar>& R1, const Scalar e) {
  // Total ops: 41

  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _R1 = R1.Data();

  // Intermediate terms (14)
  const Scalar _tmp0 = (((_R1[3]) > 0) - ((_R1[3]) < 0));
  const Scalar _tmp1 = std::fabs(_R1[3]);
  const Scalar _tmp2 = 1 - e;
  const Scalar _tmp3 = 8 * _tmp0 * std::pow(Scalar(2 * std::min<Scalar>(0, _tmp0) + 1), Scalar(2)) *
                       Scalar(0.5) * ((((-_tmp1 + _tmp2) >= 0) - ((-_tmp1 + _tmp2) < 0)) + 1);
  const Scalar _tmp4 = std::pow(_R1[0], Scalar(2)) * _tmp3;
  const Scalar _tmp5 = std::min<Scalar>(_tmp1, _tmp2);
  const Scalar _tmp6 = 1 - std::pow(_tmp5, Scalar(2));
  const Scalar _tmp7 = std::acos(_tmp5);
  const Scalar _tmp8 = _tmp7 / (_tmp6 * std::sqrt(_tmp6));
  const Scalar _tmp9 = std::pow(_R1[1], Scalar(2));
  const Scalar _tmp10 = _tmp3 * _tmp8;
  const Scalar _tmp11 = std::pow(_R1[2], Scalar(2));
  const Scalar _tmp12 = _tmp5 * std::pow(_tmp7, Scalar(2)) / std::pow(_tmp6, Scalar(2));
  const Scalar _tmp13 = _tmp12 * _tmp3;

  // Output terms (1)
  Scalar _dist_D_R1;

  _dist_D_R1 = -_tmp10 * _tmp11 - _tmp10 * _tmp9 + _tmp11 * _tmp13 + _tmp12 * _tmp4 +
               _tmp13 * _tmp9 - _tmp4 * _tmp8;

  return _dist_D_R1;
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace codegen_nan_test
