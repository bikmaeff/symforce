// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>
#include <geo/rot3.h>

namespace sym {

/**
 * Residual that penalizes the difference between(a, b) and a_T_b.
 *
 * In vector space terms that would be:
 *     (b - a) - a_T_b
 *
 * In lie group terms:
 *     local_coordinates(a_T_b, between(a, b))
 *     to_tangent(compose(inverse(a_T_b), compose(inverse(a), b)))
 *
 * Args:
 *     sqrt_info: Square root information matrix to whiten residual. This can be computed from
 *                a covariance matrix as the cholesky decomposition of the inverse. In the case
 *                of a diagonal it will contain 1/sigma values. Must match the tangent dim.
 *
 */
template <typename Scalar>
void BetweenFactorRot3(const geo::Rot3<Scalar>& a, const geo::Rot3<Scalar>& b,
                       const geo::Rot3<Scalar>& a_T_b, const Eigen::Matrix<Scalar, 3, 3>& sqrt_info,
                       const Scalar epsilon, Eigen::Matrix<Scalar, 3, 1>* const res = nullptr,
                       Eigen::Matrix<Scalar, 3, 6>* const jac = nullptr) {
  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _a = a.Data();
  const Eigen::Matrix<Scalar, 4, 1>& _b = b.Data();
  const Eigen::Matrix<Scalar, 4, 1>& _a_T_b = a_T_b.Data();

  // Intermediate terms (191)
  const Scalar _tmp0 = _a[0] * _b[2] - _a[1] * _b[3] - _a[2] * _b[0] + _a[3] * _b[1];
  const Scalar _tmp1 = _a[0] * _b[0] + _a[1] * _b[1] + _a[2] * _b[2] + _a[3] * _b[3];
  const Scalar _tmp2 = -_a[0] * _b[3] - _a[1] * _b[2] + _a[2] * _b[1] + _a[3] * _b[0];
  const Scalar _tmp3 = -_a[0] * _b[1] + _a[1] * _b[0] - _a[2] * _b[3] + _a[3] * _b[2];
  const Scalar _tmp4 =
      -_a_T_b[0] * _tmp0 + _a_T_b[1] * _tmp2 - _a_T_b[2] * _tmp1 + _a_T_b[3] * _tmp3;
  const Scalar _tmp5 =
      _a_T_b[0] * _tmp2 + _a_T_b[1] * _tmp0 + _a_T_b[2] * _tmp3 + _a_T_b[3] * _tmp1;
  const Scalar _tmp6 = -epsilon + 1;
  const Scalar _tmp7 = std::min<Scalar>(_tmp5, _tmp6);
  const Scalar _tmp8 = epsilon - 1;
  const Scalar _tmp9 = std::max<Scalar>(_tmp7, _tmp8);
  const Scalar _tmp10 = -(_tmp9 * _tmp9) + 1;
  const Scalar _tmp11 = std::acos(_tmp9);
  const Scalar _tmp12 = 2 * _tmp11 / std::sqrt(_tmp10);
  const Scalar _tmp13 = _tmp12 * sqrt_info(0, 2);
  const Scalar _tmp14 =
      _a_T_b[0] * _tmp3 - _a_T_b[1] * _tmp1 - _a_T_b[2] * _tmp2 + _a_T_b[3] * _tmp0;
  const Scalar _tmp15 = _tmp12 * sqrt_info(0, 1);
  const Scalar _tmp16 =
      -_a_T_b[0] * _tmp1 - _a_T_b[1] * _tmp3 + _a_T_b[2] * _tmp0 + _a_T_b[3] * _tmp2;
  const Scalar _tmp17 = _tmp12 * sqrt_info(0, 0);
  const Scalar _tmp18 = _tmp12 * _tmp4;
  const Scalar _tmp19 = _tmp12 * sqrt_info(1, 1);
  const Scalar _tmp20 = _tmp12 * _tmp16;
  const Scalar _tmp21 = _tmp12 * sqrt_info(2, 1);
  const Scalar _tmp22 = _a_T_b[3] * _b[3];
  const Scalar _tmp23 = _a_T_b[0] * _b[0];
  const Scalar _tmp24 = _a_T_b[2] * _b[2];
  const Scalar _tmp25 = _a_T_b[1] * _b[1];
  const Scalar _tmp26 = _tmp24 + _tmp25;
  const Scalar _tmp27 = _tmp22 + _tmp23 + _tmp26;
  const Scalar _tmp28 = (1.0 / 2.0) * ((((-_tmp5 + _tmp6) > 0) - ((-_tmp5 + _tmp6) < 0)) + 1) *
                        ((((_tmp7 - _tmp8) > 0) - ((_tmp7 - _tmp8) < 0)) + 1);
  const Scalar _tmp29 = _tmp11 * _tmp28 * _tmp9 / (_tmp10 * std::sqrt(_tmp10));
  const Scalar _tmp30 = _tmp16 * _tmp29;
  const Scalar _tmp31 = _tmp30 * sqrt_info(0, 0);
  const Scalar _tmp32 = _a_T_b[3] * _b[1];
  const Scalar _tmp33 = _a_T_b[0] * _b[2];
  const Scalar _tmp34 = _a_T_b[2] * _b[0];
  const Scalar _tmp35 = -_tmp34;
  const Scalar _tmp36 = _a_T_b[1] * _b[3];
  const Scalar _tmp37 = -_tmp36;
  const Scalar _tmp38 = _tmp35 + _tmp37;
  const Scalar _tmp39 = _tmp32 + _tmp33 + _tmp38;
  const Scalar _tmp40 = _tmp14 * _tmp29;
  const Scalar _tmp41 = _tmp27 * _tmp40;
  const Scalar _tmp42 = _a_T_b[3] * _b[0];
  const Scalar _tmp43 = _a_T_b[2] * _b[1];
  const Scalar _tmp44 = _a_T_b[1] * _b[2];
  const Scalar _tmp45 = -_tmp44;
  const Scalar _tmp46 = _a_T_b[0] * _b[3];
  const Scalar _tmp47 = -_tmp46;
  const Scalar _tmp48 = _tmp45 + _tmp47;
  const Scalar _tmp49 = _tmp42 + _tmp43 + _tmp48;
  const Scalar _tmp50 = _tmp29 * _tmp4;
  const Scalar _tmp51 = _tmp50 * sqrt_info(0, 2);
  const Scalar _tmp52 = _tmp28 / _tmp10;
  const Scalar _tmp53 = _tmp4 * _tmp52;
  const Scalar _tmp54 = _tmp53 * sqrt_info(0, 2);
  const Scalar _tmp55 = _tmp16 * _tmp52;
  const Scalar _tmp56 = _tmp55 * sqrt_info(0, 0);
  const Scalar _tmp57 = _a_T_b[0] * _b[1];
  const Scalar _tmp58 = -_tmp57;
  const Scalar _tmp59 = _a_T_b[1] * _b[0];
  const Scalar _tmp60 = _a_T_b[3] * _b[2];
  const Scalar _tmp61 = _a_T_b[2] * _b[3];
  const Scalar _tmp62 = -_tmp61;
  const Scalar _tmp63 = _tmp60 + _tmp62;
  const Scalar _tmp64 = _tmp58 + _tmp59 + _tmp63;
  const Scalar _tmp65 = _tmp14 * _tmp52;
  const Scalar _tmp66 = _tmp65 * sqrt_info(0, 1);
  const Scalar _tmp67 = _tmp13 * _tmp64 + _tmp15 * _tmp39 + _tmp17 * _tmp49 + _tmp27 * _tmp31 +
                        _tmp27 * _tmp51 - _tmp27 * _tmp54 - _tmp27 * _tmp56 - _tmp27 * _tmp66 +
                        _tmp41 * sqrt_info(0, 1);
  const Scalar _tmp68 = (1.0 / 2.0) * _tmp67;
  const Scalar _tmp69 = -_tmp33;
  const Scalar _tmp70 = _tmp32 + _tmp69;
  const Scalar _tmp71 = _tmp35 + _tmp36 + _tmp70;
  const Scalar _tmp72 = -_tmp59;
  const Scalar _tmp73 = _tmp57 + _tmp63 + _tmp72;
  const Scalar _tmp74 = _tmp30 * _tmp73;
  const Scalar _tmp75 = -_tmp43;
  const Scalar _tmp76 = -_tmp42 + _tmp48 + _tmp75;
  const Scalar _tmp77 = _tmp40 * _tmp73;
  const Scalar _tmp78 = -_tmp22;
  const Scalar _tmp79 = _tmp23 + _tmp78;
  const Scalar _tmp80 = -_tmp24 + _tmp25 + _tmp79;
  const Scalar _tmp81 = (1.0 / 2.0) * _tmp13 * _tmp80 + (1.0 / 2.0) * _tmp15 * _tmp76 +
                        (1.0 / 2.0) * _tmp17 * _tmp71 + (1.0 / 2.0) * _tmp51 * _tmp73 -
                        1.0 / 2.0 * _tmp54 * _tmp73 - 1.0 / 2.0 * _tmp56 * _tmp73 -
                        1.0 / 2.0 * _tmp66 * _tmp73 + (1.0 / 2.0) * _tmp74 * sqrt_info(0, 0) +
                        (1.0 / 2.0) * _tmp77 * sqrt_info(0, 1);
  const Scalar _tmp82 = _tmp34 + _tmp37 + _tmp70;
  const Scalar _tmp83 = _tmp29 * _tmp82;
  const Scalar _tmp84 = _tmp16 * _tmp83;
  const Scalar _tmp85 = _tmp14 * _tmp83;
  const Scalar _tmp86 = _tmp53 * _tmp82;
  const Scalar _tmp87 = _tmp24 - _tmp25 + _tmp79;
  const Scalar _tmp88 = _tmp4 * _tmp83;
  const Scalar _tmp89 = _tmp58 + _tmp72;
  const Scalar _tmp90 = -_tmp60 + _tmp62 + _tmp89;
  const Scalar _tmp91 = _tmp42 + _tmp75;
  const Scalar _tmp92 = _tmp45 + _tmp46 + _tmp91;
  const Scalar _tmp93 = _tmp13 * _tmp92 + _tmp15 * _tmp87 + _tmp17 * _tmp90 - _tmp56 * _tmp82 -
                        _tmp66 * _tmp82 + _tmp84 * sqrt_info(0, 0) + _tmp85 * sqrt_info(0, 1) -
                        _tmp86 * sqrt_info(0, 2) + _tmp88 * sqrt_info(0, 2);
  const Scalar _tmp94 = (1.0 / 2.0) * _a[2];
  const Scalar _tmp95 = -_tmp23 + _tmp26 + _tmp78;
  const Scalar _tmp96 = _tmp44 + _tmp47 + _tmp91;
  const Scalar _tmp97 = _tmp55 * _tmp96;
  const Scalar _tmp98 = _tmp60 + _tmp61 + _tmp89;
  const Scalar _tmp99 = _tmp30 * _tmp96;
  const Scalar _tmp100 = _tmp40 * _tmp96;
  const Scalar _tmp101 = -_tmp32 + _tmp38 + _tmp69;
  const Scalar _tmp102 = _tmp100 * sqrt_info(0, 1) + _tmp101 * _tmp13 + _tmp15 * _tmp98 +
                         _tmp17 * _tmp95 + _tmp51 * _tmp96 - _tmp54 * _tmp96 - _tmp66 * _tmp96 -
                         _tmp97 * sqrt_info(0, 0) + _tmp99 * sqrt_info(0, 0);
  const Scalar _tmp103 = (1.0 / 2.0) * _tmp102;
  const Scalar _tmp104 = (1.0 / 2.0) * _tmp93;
  const Scalar _tmp105 =
      -_a[0] * _a_T_b[0] - _a[1] * _a_T_b[1] - _a[2] * _a_T_b[2] + _a[3] * _a_T_b[3];
  const Scalar _tmp106 = _tmp105 * _tmp55;
  const Scalar _tmp107 = _tmp105 * _tmp30;
  const Scalar _tmp108 = _a[1] * _a_T_b[3];
  const Scalar _tmp109 = _a[0] * _a_T_b[2];
  const Scalar _tmp110 = _a[2] * _a_T_b[0];
  const Scalar _tmp111 = _a[3] * _a_T_b[1];
  const Scalar _tmp112 = -_tmp108 + _tmp109 - _tmp110 - _tmp111;
  const Scalar _tmp113 = _a[0] * _a_T_b[3];
  const Scalar _tmp114 = _a[2] * _a_T_b[1];
  const Scalar _tmp115 = _a[1] * _a_T_b[2];
  const Scalar _tmp116 = _a[3] * _a_T_b[0];
  const Scalar _tmp117 = -_tmp113 + _tmp114 - _tmp115 - _tmp116;
  const Scalar _tmp118 = _tmp40 * sqrt_info(0, 1);
  const Scalar _tmp119 = _a[2] * _a_T_b[3];
  const Scalar _tmp120 = _a[3] * _a_T_b[2];
  const Scalar _tmp121 = _a[0] * _a_T_b[1];
  const Scalar _tmp122 = _a[1] * _a_T_b[0];
  const Scalar _tmp123 = -_tmp119 - _tmp120 - _tmp121 + _tmp122;
  const Scalar _tmp124 = (1.0 / 2.0) * _tmp105 * _tmp118 + (1.0 / 2.0) * _tmp105 * _tmp51 -
                         1.0 / 2.0 * _tmp105 * _tmp54 - 1.0 / 2.0 * _tmp105 * _tmp66 -
                         1.0 / 2.0 * _tmp106 * sqrt_info(0, 0) +
                         (1.0 / 2.0) * _tmp107 * sqrt_info(0, 0) + (1.0 / 2.0) * _tmp112 * _tmp15 +
                         (1.0 / 2.0) * _tmp117 * _tmp17 + (1.0 / 2.0) * _tmp123 * _tmp13;
  const Scalar _tmp125 = _tmp119 + _tmp120 + _tmp121 - _tmp122;
  const Scalar _tmp126 = _tmp125 * _tmp55;
  const Scalar _tmp127 = _tmp113 - _tmp114 + _tmp115 + _tmp116;
  const Scalar _tmp128 = _tmp125 * _tmp40;
  const Scalar _tmp129 = _tmp125 * _tmp65;
  const Scalar _tmp130 = _tmp105 * _tmp12;
  const Scalar _tmp131 = (1.0 / 2.0) * _tmp112 * _tmp17 + (1.0 / 2.0) * _tmp125 * _tmp31 +
                         (1.0 / 2.0) * _tmp125 * _tmp51 - 1.0 / 2.0 * _tmp125 * _tmp54 -
                         1.0 / 2.0 * _tmp126 * sqrt_info(0, 0) + (1.0 / 2.0) * _tmp127 * _tmp15 +
                         (1.0 / 2.0) * _tmp128 * sqrt_info(0, 1) -
                         1.0 / 2.0 * _tmp129 * sqrt_info(0, 1) +
                         (1.0 / 2.0) * _tmp130 * sqrt_info(0, 2);
  const Scalar _tmp132 = _tmp108 - _tmp109 + _tmp110 + _tmp111;
  const Scalar _tmp133 = _tmp132 * _tmp30;
  const Scalar _tmp134 = _tmp132 * _tmp55;
  const Scalar _tmp135 = _tmp132 * _tmp50;
  const Scalar _tmp136 = _tmp117 * _tmp13 + _tmp118 * _tmp132 + _tmp125 * _tmp17 +
                         _tmp130 * sqrt_info(0, 1) - _tmp132 * _tmp54 - _tmp132 * _tmp66 +
                         _tmp133 * sqrt_info(0, 0) - _tmp134 * sqrt_info(0, 0) +
                         _tmp135 * sqrt_info(0, 2);
  const Scalar _tmp137 = (1.0 / 2.0) * _b[2];
  const Scalar _tmp138 = _tmp127 * _tmp55;
  const Scalar _tmp139 = _tmp127 * _tmp53;
  const Scalar _tmp140 = _tmp118 * _tmp127 + _tmp123 * _tmp15 + _tmp127 * _tmp31 +
                         _tmp127 * _tmp51 - _tmp127 * _tmp66 + _tmp13 * _tmp132 +
                         _tmp130 * sqrt_info(0, 0) - _tmp138 * sqrt_info(0, 0) -
                         _tmp139 * sqrt_info(0, 2);
  const Scalar _tmp141 = (1.0 / 2.0) * _b[3];
  const Scalar _tmp142 = (1.0 / 2.0) * _b[0];
  const Scalar _tmp143 = (1.0 / 2.0) * _b[1];
  const Scalar _tmp144 = _tmp12 * sqrt_info(1, 0);
  const Scalar _tmp145 = _tmp55 * sqrt_info(1, 0);
  const Scalar _tmp146 = _tmp53 * _tmp73;
  const Scalar _tmp147 = _tmp50 * sqrt_info(1, 2);
  const Scalar _tmp148 = _tmp12 * sqrt_info(1, 2);
  const Scalar _tmp149 = _tmp65 * sqrt_info(1, 1);
  const Scalar _tmp150 = (1.0 / 2.0) * _tmp144 * _tmp71 - 1.0 / 2.0 * _tmp145 * _tmp73 -
                         1.0 / 2.0 * _tmp146 * sqrt_info(1, 2) + (1.0 / 2.0) * _tmp147 * _tmp73 +
                         (1.0 / 2.0) * _tmp148 * _tmp80 - 1.0 / 2.0 * _tmp149 * _tmp73 +
                         (1.0 / 2.0) * _tmp19 * _tmp76 + (1.0 / 2.0) * _tmp74 * sqrt_info(1, 0) +
                         (1.0 / 2.0) * _tmp77 * sqrt_info(1, 1);
  const Scalar _tmp151 = _tmp30 * sqrt_info(1, 0);
  const Scalar _tmp152 = _tmp27 * _tmp53;
  const Scalar _tmp153 = _tmp144 * _tmp49 - _tmp145 * _tmp27 + _tmp147 * _tmp27 + _tmp148 * _tmp64 -
                         _tmp149 * _tmp27 + _tmp151 * _tmp27 - _tmp152 * sqrt_info(1, 2) +
                         _tmp19 * _tmp39 + _tmp41 * sqrt_info(1, 1);
  const Scalar _tmp154 = (1.0 / 2.0) * _tmp153;
  const Scalar _tmp155 = _tmp144 * _tmp90 - _tmp145 * _tmp82 + _tmp148 * _tmp92 - _tmp149 * _tmp82 +
                         _tmp19 * _tmp87 + _tmp84 * sqrt_info(1, 0) + _tmp85 * sqrt_info(1, 1) -
                         _tmp86 * sqrt_info(1, 2) + _tmp88 * sqrt_info(1, 2);
  const Scalar _tmp156 = _tmp53 * _tmp96;
  const Scalar _tmp157 = _tmp12 * _tmp95;
  const Scalar _tmp158 = _tmp100 * sqrt_info(1, 1) + _tmp101 * _tmp148 + _tmp147 * _tmp96 -
                         _tmp149 * _tmp96 - _tmp156 * sqrt_info(1, 2) + _tmp157 * sqrt_info(1, 0) +
                         _tmp19 * _tmp98 - _tmp97 * sqrt_info(1, 0) + _tmp99 * sqrt_info(1, 0);
  const Scalar _tmp159 = (1.0 / 2.0) * _tmp158;
  const Scalar _tmp160 = (1.0 / 2.0) * _a[3];
  const Scalar _tmp161 = (1.0 / 2.0) * _a[0];
  const Scalar _tmp162 = _tmp125 * _tmp53;
  const Scalar _tmp163 = (1.0 / 2.0) * _tmp112 * _tmp144 + (1.0 / 2.0) * _tmp125 * _tmp147 +
                         (1.0 / 2.0) * _tmp125 * _tmp151 - 1.0 / 2.0 * _tmp126 * sqrt_info(1, 0) +
                         (1.0 / 2.0) * _tmp127 * _tmp19 + (1.0 / 2.0) * _tmp128 * sqrt_info(1, 1) -
                         1.0 / 2.0 * _tmp129 * sqrt_info(1, 1) +
                         (1.0 / 2.0) * _tmp130 * sqrt_info(1, 2) -
                         1.0 / 2.0 * _tmp162 * sqrt_info(1, 2);
  const Scalar _tmp164 = _tmp117 * _tmp12;
  const Scalar _tmp165 = _tmp40 * sqrt_info(1, 1);
  const Scalar _tmp166 = _tmp105 * _tmp53;
  const Scalar _tmp167 = _tmp105 * _tmp147 - _tmp105 * _tmp149 + _tmp105 * _tmp165 -
                         _tmp106 * sqrt_info(1, 0) + _tmp107 * sqrt_info(1, 0) + _tmp112 * _tmp19 +
                         _tmp123 * _tmp148 + _tmp164 * sqrt_info(1, 0) - _tmp166 * sqrt_info(1, 2);
  const Scalar _tmp168 = (1.0 / 2.0) * _tmp167;
  const Scalar _tmp169 = _tmp132 * _tmp53;
  const Scalar _tmp170 = _tmp117 * _tmp148 + _tmp125 * _tmp144 + _tmp130 * sqrt_info(1, 1) -
                         _tmp132 * _tmp149 + _tmp132 * _tmp165 + _tmp133 * sqrt_info(1, 0) -
                         _tmp134 * sqrt_info(1, 0) + _tmp135 * sqrt_info(1, 2) -
                         _tmp169 * sqrt_info(1, 2);
  const Scalar _tmp171 = _tmp123 * _tmp19 + _tmp127 * _tmp147 - _tmp127 * _tmp149 +
                         _tmp127 * _tmp151 + _tmp127 * _tmp165 + _tmp130 * sqrt_info(1, 0) +
                         _tmp132 * _tmp148 - _tmp138 * sqrt_info(1, 0) - _tmp139 * sqrt_info(1, 2);
  const Scalar _tmp172 = _tmp12 * sqrt_info(2, 0);
  const Scalar _tmp173 = _tmp30 * sqrt_info(2, 0);
  const Scalar _tmp174 = _tmp55 * sqrt_info(2, 0);
  const Scalar _tmp175 = _tmp50 * sqrt_info(2, 2);
  const Scalar _tmp176 = _tmp12 * sqrt_info(2, 2);
  const Scalar _tmp177 = _tmp65 * sqrt_info(2, 1);
  const Scalar _tmp178 = -_tmp152 * sqrt_info(2, 2) + _tmp172 * _tmp49 + _tmp173 * _tmp27 -
                         _tmp174 * _tmp27 + _tmp175 * _tmp27 + _tmp176 * _tmp64 - _tmp177 * _tmp27 +
                         _tmp21 * _tmp39 + _tmp41 * sqrt_info(2, 1);
  const Scalar _tmp179 = (1.0 / 2.0) * _tmp178;
  const Scalar _tmp180 = _tmp172 * _tmp90 - _tmp174 * _tmp82 + _tmp176 * _tmp92 - _tmp177 * _tmp82 +
                         _tmp21 * _tmp87 + _tmp84 * sqrt_info(2, 0) + _tmp85 * sqrt_info(2, 1) -
                         _tmp86 * sqrt_info(2, 2) + _tmp88 * sqrt_info(2, 2);
  const Scalar _tmp181 = -1.0 / 2.0 * _tmp146 * sqrt_info(2, 2) + (1.0 / 2.0) * _tmp172 * _tmp71 +
                         (1.0 / 2.0) * _tmp173 * _tmp73 - 1.0 / 2.0 * _tmp174 * _tmp73 +
                         (1.0 / 2.0) * _tmp175 * _tmp73 + (1.0 / 2.0) * _tmp176 * _tmp80 -
                         1.0 / 2.0 * _tmp177 * _tmp73 + (1.0 / 2.0) * _tmp21 * _tmp76 +
                         (1.0 / 2.0) * _tmp77 * sqrt_info(2, 1);
  const Scalar _tmp182 = _tmp100 * sqrt_info(2, 1) + _tmp101 * _tmp176 - _tmp156 * sqrt_info(2, 2) +
                         _tmp157 * sqrt_info(2, 0) + _tmp173 * _tmp96 + _tmp175 * _tmp96 -
                         _tmp177 * _tmp96 + _tmp21 * _tmp98 - _tmp97 * sqrt_info(2, 0);
  const Scalar _tmp183 = (1.0 / 2.0) * _tmp182;
  const Scalar _tmp184 = _tmp105 * sqrt_info(2, 1);
  const Scalar _tmp185 = _tmp105 * _tmp175 - _tmp106 * sqrt_info(2, 0) + _tmp107 * sqrt_info(2, 0) +
                         _tmp112 * _tmp21 + _tmp123 * _tmp176 + _tmp164 * sqrt_info(2, 0) -
                         _tmp166 * sqrt_info(2, 2) + _tmp184 * _tmp40 - _tmp184 * _tmp65;
  const Scalar _tmp186 = (1.0 / 2.0) * _tmp185;
  const Scalar _tmp187 = (1.0 / 2.0) * _tmp112 * _tmp172 + (1.0 / 2.0) * _tmp125 * _tmp173 +
                         (1.0 / 2.0) * _tmp125 * _tmp175 - 1.0 / 2.0 * _tmp125 * _tmp177 -
                         1.0 / 2.0 * _tmp126 * sqrt_info(2, 0) + (1.0 / 2.0) * _tmp127 * _tmp21 +
                         (1.0 / 2.0) * _tmp128 * sqrt_info(2, 1) +
                         (1.0 / 2.0) * _tmp130 * sqrt_info(2, 2) -
                         1.0 / 2.0 * _tmp162 * sqrt_info(2, 2);
  const Scalar _tmp188 = _tmp40 * sqrt_info(2, 1);
  const Scalar _tmp189 = _tmp117 * _tmp176 + _tmp12 * _tmp184 + _tmp125 * _tmp172 +
                         _tmp132 * _tmp173 - _tmp132 * _tmp177 + _tmp132 * _tmp188 -
                         _tmp134 * sqrt_info(2, 0) + _tmp135 * sqrt_info(2, 2) -
                         _tmp169 * sqrt_info(2, 2);
  const Scalar _tmp190 = _tmp123 * _tmp21 + _tmp127 * _tmp173 + _tmp127 * _tmp175 -
                         _tmp127 * _tmp177 + _tmp127 * _tmp188 + _tmp130 * sqrt_info(2, 0) +
                         _tmp132 * _tmp176 - _tmp138 * sqrt_info(2, 0) - _tmp139 * sqrt_info(2, 2);

  // Output terms (2)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 3, 1>& _res = (*res);

    _res(0, 0) = _tmp13 * _tmp4 + _tmp14 * _tmp15 + _tmp16 * _tmp17;
    _res(1, 0) = _tmp14 * _tmp19 + _tmp18 * sqrt_info(1, 2) + _tmp20 * sqrt_info(1, 0);
    _res(2, 0) = _tmp14 * _tmp21 + _tmp18 * sqrt_info(2, 2) + _tmp20 * sqrt_info(2, 0);
  }

  if (jac != nullptr) {
    Eigen::Matrix<Scalar, 3, 6>& _jac = (*jac);

    _jac(0, 0) = -_a[0] * _tmp68 - _a[1] * _tmp81 + _a[3] * _tmp103 + _tmp93 * _tmp94;
    _jac(0, 1) = _a[0] * _tmp81 - _a[1] * _tmp68 + _a[3] * _tmp104 - _tmp102 * _tmp94;
    _jac(0, 2) = -_a[0] * _tmp104 + _a[1] * _tmp103 + _a[3] * _tmp81 - _tmp67 * _tmp94;
    _jac(0, 3) = -_b[0] * _tmp124 - _b[1] * _tmp131 + _tmp136 * _tmp137 + _tmp140 * _tmp141;
    _jac(0, 4) = _b[0] * _tmp131 - _b[1] * _tmp124 + _tmp136 * _tmp141 - _tmp137 * _tmp140;
    _jac(0, 5) = -_b[2] * _tmp124 + _b[3] * _tmp131 - _tmp136 * _tmp142 + _tmp140 * _tmp143;
    _jac(1, 0) = -_a[0] * _tmp154 - _a[1] * _tmp150 + _a[3] * _tmp159 + _tmp155 * _tmp94;
    _jac(1, 1) = _a[0] * _tmp150 - _a[1] * _tmp154 + _tmp155 * _tmp160 - _tmp158 * _tmp94;
    _jac(1, 2) = _a[1] * _tmp159 + _a[3] * _tmp150 - _tmp153 * _tmp94 - _tmp155 * _tmp161;
    _jac(1, 3) = -_b[0] * _tmp168 - _b[1] * _tmp163 + _tmp137 * _tmp170 + _tmp141 * _tmp171;
    _jac(1, 4) = _b[0] * _tmp163 - _tmp137 * _tmp171 + _tmp141 * _tmp170 - _tmp143 * _tmp167;
    _jac(1, 5) = -_b[2] * _tmp168 + _b[3] * _tmp163 - _tmp142 * _tmp170 + _tmp143 * _tmp171;
    _jac(2, 0) = -_a[0] * _tmp179 - _a[1] * _tmp181 + _a[3] * _tmp183 + _tmp180 * _tmp94;
    _jac(2, 1) = _a[0] * _tmp181 - _a[1] * _tmp179 + _tmp160 * _tmp180 - _tmp182 * _tmp94;
    _jac(2, 2) = _a[1] * _tmp183 + _a[3] * _tmp181 - _tmp161 * _tmp180 - _tmp178 * _tmp94;
    _jac(2, 3) = -_b[0] * _tmp186 - _b[1] * _tmp187 + _tmp137 * _tmp189 + _tmp141 * _tmp190;
    _jac(2, 4) = _b[0] * _tmp187 - _tmp137 * _tmp190 + _tmp141 * _tmp189 - _tmp143 * _tmp185;
    _jac(2, 5) = -_b[2] * _tmp186 + _b[3] * _tmp187 - _tmp142 * _tmp189 + _tmp143 * _tmp190;
  }
}

}  // namespace sym
