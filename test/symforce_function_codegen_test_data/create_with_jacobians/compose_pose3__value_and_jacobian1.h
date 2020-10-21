// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>
#include <geo/pose3.h>

namespace sym {

/**
 * Composition of two elements in the group.
 *
 * Args:
 *     a (Element):
 *     b (Element):
 *
 * Returns:
 *     Element: a @ b
 *     geo.Matrix: Jacobian for arg 1 (b)
 */
template <typename Scalar>
geo::Pose3<Scalar> ComposePose3_ValueAndJacobian1(
    const geo::Pose3<Scalar>& a, const geo::Pose3<Scalar>& b,
    Eigen::Matrix<Scalar, 6, 6>* const res_D_b = nullptr) {
  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _b = b.Data();

  // Intermediate terms (110)
  const Scalar _tmp0 = _a[0] * _b[3] + _a[1] * _b[2] - _a[2] * _b[1] + _a[3] * _b[0];
  const Scalar _tmp1 = -_a[0] * _b[2] + _a[1] * _b[3] + _a[2] * _b[0] + _a[3] * _b[1];
  const Scalar _tmp2 = _a[0] * _b[1] - _a[1] * _b[0] + _a[2] * _b[3] + _a[3] * _b[2];
  const Scalar _tmp3 = -_a[0] * _b[0] - _a[1] * _b[1] - _a[2] * _b[2] + _a[3] * _b[3];
  const Scalar _tmp4 = 2 * _a[1];
  const Scalar _tmp5 = _a[3] * _tmp4;
  const Scalar _tmp6 = 2 * _a[2];
  const Scalar _tmp7 = _a[0] * _tmp6;
  const Scalar _tmp8 = _tmp5 + _tmp7;
  const Scalar _tmp9 = 2 * _a[3];
  const Scalar _tmp10 = _a[2] * _tmp9;
  const Scalar _tmp11 = _a[0] * _tmp4;
  const Scalar _tmp12 = -_tmp10 + _tmp11;
  const Scalar _tmp13 = -2 * (_a[2] * _a[2]);
  const Scalar _tmp14 = -2 * (_a[1] * _a[1]);
  const Scalar _tmp15 = _tmp13 + _tmp14 + 1;
  const Scalar _tmp16 = _a[0] * _tmp9;
  const Scalar _tmp17 = _a[2] * _tmp4;
  const Scalar _tmp18 = -_tmp16 + _tmp17;
  const Scalar _tmp19 = -2 * (_a[0] * _a[0]) + 1;
  const Scalar _tmp20 = _tmp13 + _tmp19;
  const Scalar _tmp21 = _tmp10 + _tmp11;
  const Scalar _tmp22 = _tmp14 + _tmp19;
  const Scalar _tmp23 = _tmp16 + _tmp17;
  const Scalar _tmp24 = -_tmp5 + _tmp7;
  const Scalar _tmp25 = _tmp0 * _tmp6;
  const Scalar _tmp26 = _tmp1 * _tmp9;
  const Scalar _tmp27 = _tmp3 * _tmp4;
  const Scalar _tmp28 = 2 * _tmp2;
  const Scalar _tmp29 = _a[0] * _tmp28;
  const Scalar _tmp30 = _tmp25 - _tmp26 + _tmp27 - _tmp29;
  const Scalar _tmp31 = (1.0 / 2.0) * _b[1];
  const Scalar _tmp32 = -_tmp30 * _tmp31;
  const Scalar _tmp33 = _tmp0 * _tmp4;
  const Scalar _tmp34 = 2 * _tmp1;
  const Scalar _tmp35 = _a[0] * _tmp34;
  const Scalar _tmp36 = _tmp2 * _tmp9;
  const Scalar _tmp37 = _tmp3 * _tmp6;
  const Scalar _tmp38 = _tmp33 - _tmp35 + _tmp36 - _tmp37;
  const Scalar _tmp39 = (1.0 / 2.0) * _b[2];
  const Scalar _tmp40 = _tmp0 * _tmp9;
  const Scalar _tmp41 = _tmp1 * _tmp6;
  const Scalar _tmp42 = _tmp2 * _tmp4;
  const Scalar _tmp43 = 2 * _tmp3;
  const Scalar _tmp44 = _a[0] * _tmp43;
  const Scalar _tmp45 = -_tmp40 - _tmp41 + _tmp42 + _tmp44;
  const Scalar _tmp46 = (1.0 / 2.0) * _b[0];
  const Scalar _tmp47 = 2 * _a[0] * _tmp0 + _tmp1 * _tmp4 + _tmp2 * _tmp6 + _tmp3 * _tmp9;
  const Scalar _tmp48 = (1.0 / 2.0) * _b[3];
  const Scalar _tmp49 = _tmp47 * _tmp48;
  const Scalar _tmp50 = -_tmp45 * _tmp46 + _tmp49;
  const Scalar _tmp51 = _tmp30 * _tmp46;
  const Scalar _tmp52 = (1.0 / 2.0) * _tmp38;
  const Scalar _tmp53 = _tmp39 * _tmp47;
  const Scalar _tmp54 = _tmp39 * _tmp45;
  const Scalar _tmp55 = _tmp31 * _tmp47;
  const Scalar _tmp56 = _tmp40 + _tmp41 - _tmp42 - _tmp44;
  const Scalar _tmp57 = -_tmp33 + _tmp35 - _tmp36 + _tmp37;
  const Scalar _tmp58 = (1.0 / 2.0) * _tmp57;
  const Scalar _tmp59 = -_tmp39 * _tmp57;
  const Scalar _tmp60 = _tmp46 * _tmp47;
  const Scalar _tmp61 = _b[1] * _tmp58;
  const Scalar _tmp62 = -_tmp25 + _tmp26 - _tmp27 + _tmp29;
  const Scalar _tmp63 = 2 * _b[1] * _b[3];
  const Scalar _tmp64 = 2 * _b[0];
  const Scalar _tmp65 = _b[2] * _tmp64;
  const Scalar _tmp66 = -_tmp63 + _tmp65;
  const Scalar _tmp67 = _tmp1 * _tmp43;
  const Scalar _tmp68 = _tmp0 * _tmp28;
  const Scalar _tmp69 = -_tmp67 + _tmp68;
  const Scalar _tmp70 = _tmp28 * _tmp3;
  const Scalar _tmp71 = _tmp0 * _tmp34;
  const Scalar _tmp72 = _tmp70 + _tmp71;
  const Scalar _tmp73 = -2 * (_tmp1 * _tmp1);
  const Scalar _tmp74 = -2 * (_tmp2 * _tmp2) + 1;
  const Scalar _tmp75 = _tmp73 + _tmp74;
  const Scalar _tmp76 = _tmp18 * _tmp72 + _tmp22 * _tmp69 + _tmp75 * _tmp8;
  const Scalar _tmp77 = 2 * _b[2];
  const Scalar _tmp78 = _b[3] * _tmp77;
  const Scalar _tmp79 = _b[1] * _tmp64;
  const Scalar _tmp80 = _tmp78 + _tmp79;
  const Scalar _tmp81 = _tmp12 * _tmp75 + _tmp20 * _tmp72 + _tmp23 * _tmp69;
  const Scalar _tmp82 = -2 * (_b[2] * _b[2]);
  const Scalar _tmp83 = -2 * (_b[1] * _b[1]) + 1;
  const Scalar _tmp84 = _tmp82 + _tmp83;
  const Scalar _tmp85 = _tmp15 * _tmp75 + _tmp21 * _tmp72 + _tmp24 * _tmp69;
  const Scalar _tmp86 = _b[3] * _tmp64;
  const Scalar _tmp87 = _b[1] * _tmp77;
  const Scalar _tmp88 = _tmp86 + _tmp87;
  const Scalar _tmp89 = -2 * (_b[0] * _b[0]);
  const Scalar _tmp90 = _tmp82 + _tmp89 + 1;
  const Scalar _tmp91 = -_tmp78 + _tmp79;
  const Scalar _tmp92 = -_tmp86 + _tmp87;
  const Scalar _tmp93 = _tmp83 + _tmp89;
  const Scalar _tmp94 = _tmp63 + _tmp65;
  const Scalar _tmp95 = -2 * (_tmp0 * _tmp0);
  const Scalar _tmp96 = _tmp74 + _tmp95;
  const Scalar _tmp97 = _tmp0 * _tmp43;
  const Scalar _tmp98 = _tmp1 * _tmp28;
  const Scalar _tmp99 = _tmp97 + _tmp98;
  const Scalar _tmp100 = -_tmp70 + _tmp71;
  const Scalar _tmp101 = _tmp100 * _tmp8 + _tmp18 * _tmp96 + _tmp22 * _tmp99;
  const Scalar _tmp102 = _tmp100 * _tmp12 + _tmp20 * _tmp96 + _tmp23 * _tmp99;
  const Scalar _tmp103 = _tmp100 * _tmp15 + _tmp21 * _tmp96 + _tmp24 * _tmp99;
  const Scalar _tmp104 = _tmp73 + _tmp95 + 1;
  const Scalar _tmp105 = -_tmp97 + _tmp98;
  const Scalar _tmp106 = _tmp67 + _tmp68;
  const Scalar _tmp107 = _tmp104 * _tmp22 + _tmp105 * _tmp18 + _tmp106 * _tmp8;
  const Scalar _tmp108 = _tmp104 * _tmp23 + _tmp105 * _tmp20 + _tmp106 * _tmp12;
  const Scalar _tmp109 = _tmp104 * _tmp24 + _tmp105 * _tmp21 + _tmp106 * _tmp15;

  // Output terms (2)
  Eigen::Matrix<Scalar, 7, 1> _res;

  _res[0] = _tmp0;
  _res[1] = _tmp1;
  _res[2] = _tmp2;
  _res[3] = _tmp3;
  _res[4] = _a[4] + _b[4] * _tmp15 + _b[5] * _tmp12 + _b[6] * _tmp8;
  _res[5] = _a[5] + _b[4] * _tmp21 + _b[5] * _tmp20 + _b[6] * _tmp18;
  _res[6] = _a[6] + _b[4] * _tmp24 + _b[5] * _tmp23 + _b[6] * _tmp22;

  if (res_D_b != nullptr) {
    Eigen::Matrix<Scalar, 6, 6>& _res_D_b = (*res_D_b);

    _res_D_b(0, 0) = _tmp32 + _tmp38 * _tmp39 + _tmp50;
    _res_D_b(0, 1) = _b[3] * _tmp52 - _tmp31 * _tmp45 + _tmp51 - _tmp53;
    _res_D_b(0, 2) = -_b[0] * _tmp52 + _tmp30 * _tmp48 - _tmp54 + _tmp55;
    _res_D_b(0, 3) = 0;
    _res_D_b(0, 4) = 0;
    _res_D_b(0, 5) = 0;
    _res_D_b(1, 0) = _b[3] * _tmp58 - _tmp31 * _tmp56 - _tmp51 + _tmp53;
    _res_D_b(1, 1) = _tmp32 + _tmp46 * _tmp56 + _tmp49 + _tmp59;
    _res_D_b(1, 2) = -_tmp30 * _tmp39 + _tmp48 * _tmp56 - _tmp60 + _tmp61;
    _res_D_b(1, 3) = 0;
    _res_D_b(1, 4) = 0;
    _res_D_b(1, 5) = 0;
    _res_D_b(2, 0) = -_b[0] * _tmp58 + _tmp48 * _tmp62 + _tmp54 - _tmp55;
    _res_D_b(2, 1) = -_tmp39 * _tmp62 + _tmp45 * _tmp48 + _tmp60 - _tmp61;
    _res_D_b(2, 2) = _tmp31 * _tmp62 + _tmp50 + _tmp59;
    _res_D_b(2, 3) = 0;
    _res_D_b(2, 4) = 0;
    _res_D_b(2, 5) = 0;
    _res_D_b(3, 0) = 0;
    _res_D_b(3, 1) = 0;
    _res_D_b(3, 2) = 0;
    _res_D_b(3, 3) = _tmp66 * _tmp76 + _tmp80 * _tmp81 + _tmp84 * _tmp85;
    _res_D_b(3, 4) = _tmp76 * _tmp88 + _tmp81 * _tmp90 + _tmp85 * _tmp91;
    _res_D_b(3, 5) = _tmp76 * _tmp93 + _tmp81 * _tmp92 + _tmp85 * _tmp94;
    _res_D_b(4, 0) = 0;
    _res_D_b(4, 1) = 0;
    _res_D_b(4, 2) = 0;
    _res_D_b(4, 3) = _tmp101 * _tmp66 + _tmp102 * _tmp80 + _tmp103 * _tmp84;
    _res_D_b(4, 4) = _tmp101 * _tmp88 + _tmp102 * _tmp90 + _tmp103 * _tmp91;
    _res_D_b(4, 5) = _tmp101 * _tmp93 + _tmp102 * _tmp92 + _tmp103 * _tmp94;
    _res_D_b(5, 0) = 0;
    _res_D_b(5, 1) = 0;
    _res_D_b(5, 2) = 0;
    _res_D_b(5, 3) = _tmp107 * _tmp66 + _tmp108 * _tmp80 + _tmp109 * _tmp84;
    _res_D_b(5, 4) = _tmp107 * _tmp88 + _tmp108 * _tmp90 + _tmp109 * _tmp91;
    _res_D_b(5, 5) = _tmp107 * _tmp93 + _tmp108 * _tmp92 + _tmp109 * _tmp94;
  }

  return geo::Pose3<Scalar>(_res);
}

}  // namespace sym
