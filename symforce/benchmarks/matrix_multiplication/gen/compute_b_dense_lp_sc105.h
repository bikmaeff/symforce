// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cpp_templates/function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once


#include <Eigen/Dense>



namespace sym {


/**
* This function was autogenerated. Do not modify by hand.
*
* Args:
*     x0: Scalar
*     x1: Scalar
*     x2: Scalar
*     x3: Scalar
*     x4: Scalar
*
* Outputs:
*     result: Matrix105_163
*/
template <typename Scalar>
Eigen::Matrix<Scalar, 105, 163> ComputeBDenseLpSc105(const Scalar x0, const Scalar x1, const Scalar x2, const Scalar x3, const Scalar x4) {

    // Total ops: 556

    // Input arrays

    // Intermediate terms (108)
    const Scalar _tmp0 = 2*x1;
    const Scalar _tmp1 = x3 + 1;
    const Scalar _tmp2 = 2*x3;
    const Scalar _tmp3 = x4 + 1;
    const Scalar _tmp4 = x3*x4;
    const Scalar _tmp5 = x1 - 1;
    const Scalar _tmp6 = 4*x0;
    const Scalar _tmp7 = _tmp6*x2;
    const Scalar _tmp8 = _tmp2*x4;
    const Scalar _tmp9 = Scalar(1.0) / (x2);
    const Scalar _tmp10 = Scalar(1.0) / (x0);
    const Scalar _tmp11 = 2*x4;
    const Scalar _tmp12 = 4*x2;
    const Scalar _tmp13 = 4*x1;
    const Scalar _tmp14 = 2*x2;
    const Scalar _tmp15 = -x4;
    const Scalar _tmp16 = x3 + 3;
    const Scalar _tmp17 = -x2;
    const Scalar _tmp18 = _tmp2 + 1;
    const Scalar _tmp19 = x2 + 2;
    const Scalar _tmp20 = x0 - 1;
    const Scalar _tmp21 = x1 + x3;
    const Scalar _tmp22 = x0 + x2;
    const Scalar _tmp23 = 4*x4;
    const Scalar _tmp24 = -_tmp0;
    const Scalar _tmp25 = _tmp24 + x0;
    const Scalar _tmp26 = x2 + 1;
    const Scalar _tmp27 = -x0;
    const Scalar _tmp28 = x1 + 2;
    const Scalar _tmp29 = -x3;
    const Scalar _tmp30 = x2*x4;
    const Scalar _tmp31 = x1*x2;
    const Scalar _tmp32 = x4 - 1;
    const Scalar _tmp33 = x0 - 2;
    const Scalar _tmp34 = x3 - 2;
    const Scalar _tmp35 = Scalar(1.0) / (x1);
    const Scalar _tmp36 = _tmp35*x4;
    const Scalar _tmp37 = 3*x1;
    const Scalar _tmp38 = x2 + x4;
    const Scalar _tmp39 = Scalar(1.0) / (x3);
    const Scalar _tmp40 = std::pow(x2, Scalar(2));
    const Scalar _tmp41 = 2*x0;
    const Scalar _tmp42 = -_tmp41;
    const Scalar _tmp43 = x0 + x3;
    const Scalar _tmp44 = _tmp15 + _tmp41;
    const Scalar _tmp45 = -_tmp11;
    const Scalar _tmp46 = x0 + 1;
    const Scalar _tmp47 = _tmp19 + _tmp27;
    const Scalar _tmp48 = 3*x4;
    const Scalar _tmp49 = std::pow(x4, Scalar(2));
    const Scalar _tmp50 = x1 + 1;
    const Scalar _tmp51 = -x1;
    const Scalar _tmp52 = x2 - 1;
    const Scalar _tmp53 = _tmp11 + x0;
    const Scalar _tmp54 = x0*x3;
    const Scalar _tmp55 = _tmp10*_tmp2;
    const Scalar _tmp56 = std::pow(x3, Scalar(2));
    const Scalar _tmp57 = x3 + x4;
    const Scalar _tmp58 = _tmp14 + 1;
    const Scalar _tmp59 = x3 + 2;
    const Scalar _tmp60 = x0*x4;
    const Scalar _tmp61 = Scalar(1.0) / (_tmp59);
    const Scalar _tmp62 = _tmp14*x0;
    const Scalar _tmp63 = _tmp60*x1;
    const Scalar _tmp64 = -_tmp2 - 2;
    const Scalar _tmp65 = -_tmp48;
    const Scalar _tmp66 = _tmp0*x2;
    const Scalar _tmp67 = x3 - 1;
    const Scalar _tmp68 = std::pow(x0, Scalar(2));
    const Scalar _tmp69 = x1 - 2;
    const Scalar _tmp70 = _tmp69*x1;
    const Scalar _tmp71 = _tmp29 + x1;
    const Scalar _tmp72 = _tmp54 + x0;
    const Scalar _tmp73 = _tmp15 + x2;
    const Scalar _tmp74 = _tmp73 + x1;
    const Scalar _tmp75 = 2*_tmp39;
    const Scalar _tmp76 = Scalar(1.0) / (_tmp52);
    const Scalar _tmp77 = _tmp76*x0;
    const Scalar _tmp78 = _tmp3 + x2;
    const Scalar _tmp79 = -_tmp6;
    const Scalar _tmp80 = x4 - 2;
    const Scalar _tmp81 = Scalar(1.0) / (_tmp50);
    const Scalar _tmp82 = x0*x2;
    const Scalar _tmp83 = _tmp2*_tmp82;
    const Scalar _tmp84 = _tmp29 + 1;
    const Scalar _tmp85 = _tmp27 + 2;
    const Scalar _tmp86 = Scalar(1.0) / (x4);
    const Scalar _tmp87 = x1 - 4;
    const Scalar _tmp88 = _tmp86*x3;
    const Scalar _tmp89 = x1*x4;
    const Scalar _tmp90 = x0 + 2;
    const Scalar _tmp91 = _tmp10*x4;
    const Scalar _tmp92 = x2 + 3;
    const Scalar _tmp93 = x2 - 2;
    const Scalar _tmp94 = _tmp22 + _tmp51;
    const Scalar _tmp95 = -_tmp89;
    const Scalar _tmp96 = x1 + x4;
    const Scalar _tmp97 = 4*x3;
    const Scalar _tmp98 = x2 + x3;
    const Scalar _tmp99 = 2*_tmp49;
    const Scalar _tmp100 = x2*x3;
    const Scalar _tmp101 = _tmp2 - 2;
    const Scalar _tmp102 = _tmp0 + _tmp101;
    const Scalar _tmp103 = std::pow(x1, Scalar(2));
    const Scalar _tmp104 = x0*x1;
    const Scalar _tmp105 = -_tmp5;
    const Scalar _tmp106 = -_tmp31;
    const Scalar _tmp107 = -_tmp80;

    // Output terms (1)
    Eigen::Matrix<Scalar, 105, 163> _result;

    _result.setZero();

    _result(0, 0) = x0;
    _result(1, 1) = -_tmp0 - _tmp1;
    _result(2, 2) = _tmp2 + Scalar(-1.0);
    _result(7, 3) = -_tmp3;
    _result(8, 4) = -_tmp4 - _tmp5;
    _result(9, 5) = -_tmp7;
    _result(10, 6) = _tmp8;
    _result(11, 7) = -x2*(_tmp10*_tmp11*_tmp9 + 2);
    _result(12, 8) = -6;
    _result(18, 9) = _tmp12*x3 - 1;
    _result(19, 10) = -_tmp9*x1 - x1;
    _result(20, 11) = _tmp13 + _tmp14 + _tmp15;
    _result(21, 12) = _tmp16;
    _result(22, 13) = -_tmp17 - _tmp18;
    _result(23, 14) = -_tmp19*x4 - 1;
    _result(29, 15) = -_tmp20*_tmp9 + _tmp21;
    _result(30, 16) = -x3*(_tmp22 + x1);
    _result(31, 17) = (Scalar(1)/Scalar(4))*x0;
    _result(32, 18) = -_tmp23;
    _result(33, 19) = -_tmp25 - x4;
    _result(34, 20) = -_tmp15 - _tmp26;
    _result(40, 21) = _tmp27;
    _result(41, 22) = -_tmp28;
    _result(42, 23) = x3;
    _result(43, 24) = -x3*(_tmp29 + _tmp30);
    _result(45, 26) = _tmp31 + x3;
    _result(51, 27) = -_tmp32;
    _result(52, 28) = -_tmp33*x0;
    _result(53, 29) = -_tmp34*x3;
    _result(54, 30) = _tmp14*_tmp36 - x3;
    _result(55, 31) = -_tmp21*x0;
    _result(56, 32) = -4;
    _result(62, 33) = _tmp37 + 1;
    _result(63, 34) = -x0/_tmp3;
    _result(64, 35) = _tmp38;
    _result(65, 36) = _tmp0*x4;
    _result(66, 37) = -4*_tmp39 - x0 - 4;
    _result(67, 38) = x3*(_tmp40 + 1);
    _result(73, 39) = -_tmp28 - _tmp42;
    _result(74, 40) = -x2*(_tmp43 + 1) - x3;
    _result(75, 41) = _tmp0;
    _result(76, 42) = _tmp44 + 1;
    _result(77, 43) = _tmp15;
    _result(78, 44) = _tmp45 + _tmp46;
    _result(84, 45) = _tmp15;
    _result(85, 46) = _tmp47 + x1;
    _result(86, 47) = -_tmp11 - _tmp14 - 6;
    _result(87, 48) = -_tmp17 - _tmp46;
    _result(88, 49) = 2;
    _result(89, 50) = _tmp10*_tmp48 + _tmp29 + 2;
    _result(95, 51) = -_tmp0*_tmp4;
    _result(96, 52) = _tmp13 + 1;
    _result(97, 53) = _tmp30 + x1;
    _result(98, 54) = _tmp45;
    _result(99, 55) = -_tmp30*x1;
    _result(100, 56) = _tmp49 - _tmp6;
    _result(102, 57) = -_tmp21;
    _result(103, 58) = -x4 + Scalar(-1.0);
    _result(104, 59) = -_tmp50;
    _result(0, 60) = _tmp42;
    _result(1, 60) = -_tmp31 - _tmp51 - _tmp52;
    _result(4, 60) = _tmp15;
    _result(0, 61) = -_tmp35*_tmp53;
    _result(1, 61) = -x0*(Scalar(2.0)*x3 + x4);
    _result(5, 61) = _tmp30 - 2;
    _result(0, 62) = -4;
    _result(1, 62) = x3*(_tmp34 + x1);
    _result(6, 62) = -Scalar(3)/Scalar(2)*x3 + Scalar(-1)/Scalar(2);
    _result(3, 63) = _tmp54*(_tmp4 + x4);
    _result(13, 63) = -_tmp35*_tmp55;
    _result(3, 64) = _tmp32*_tmp56;
    _result(12, 64) = x1*(-_tmp4 + _tmp46);
    _result(14, 64) = -_tmp57*_tmp58;
    _result(4, 65) = -_tmp12 + _tmp59;
    _result(7, 65) = -_tmp60;
    _result(15, 65) = -_tmp14 - _tmp59;
    _result(5, 66) = _tmp15;
    _result(8, 66) = -_tmp8*_tmp9;
    _result(16, 66) = _tmp24;
    _result(6, 67) = -_tmp61*x0;
    _result(9, 67) = 6;
    _result(17, 67) = 1 - _tmp6;
    _result(7, 68) = -_tmp10*(_tmp19 + x4);
    _result(10, 68) = _tmp10*_tmp14;
    _result(8, 69) = _tmp27 + _tmp28;
    _result(11, 69) = -_tmp14 - x3;
    _result(9, 70) = _tmp42;
    _result(12, 70) = -_tmp62;
    _result(10, 71) = x3;
    _result(11, 71) = _tmp63;
    _result(15, 71) = _tmp64;
    _result(10, 72) = _tmp60;
    _result(11, 72) = -_tmp14 - _tmp65;
    _result(16, 72) = 3;
    _result(10, 73) = -2*_tmp10 - x0 - x4;
    _result(11, 73) = _tmp2*_tmp30;
    _result(17, 73) = -_tmp34;
    _result(13, 74) = -_tmp14 - _tmp41 - _tmp66;
    _result(14, 74) = -_tmp50 - _tmp60;
    _result(24, 74) = _tmp67;
    _result(14, 75) = _tmp41*x4;
    _result(23, 75) = -_tmp17 - _tmp68/_tmp22;
    _result(25, 75) = _tmp26;
    _result(15, 76) = -_tmp33;
    _result(18, 76) = _tmp64;
    _result(26, 76) = _tmp20 + _tmp68;
    _result(16, 77) = -_tmp2*_tmp33 + 4;
    _result(19, 77) = _tmp70;
    _result(27, 77) = -_tmp63;
    _result(17, 78) = 2;
    _result(20, 78) = -6;
    _result(28, 78) = -x3*(_tmp17 + x1);
    _result(18, 79) = -_tmp71 - _tmp72;
    _result(21, 79) = Scalar(2.0)*x0;
    _result(19, 80) = -_tmp74*x2;
    _result(22, 80) = _tmp75;
    _result(20, 81) = -3*x2;
    _result(23, 81) = -x1*(x0 + 3);
    _result(21, 82) = _tmp45;
    _result(22, 82) = -_tmp66 + x0;
    _result(26, 82) = _tmp77 - 1;
    _result(21, 83) = -5*x4;
    _result(22, 83) = -_tmp78;
    _result(27, 83) = _tmp79;
    _result(21, 84) = -_tmp36/_tmp80;
    _result(22, 84) = -_tmp44;
    _result(28, 84) = -_tmp15 - _tmp28;
    _result(24, 85) = _tmp31 - _tmp81*x2;
    _result(25, 85) = -2;
    _result(35, 85) = -_tmp17 - _tmp50;
    _result(25, 86) = -_tmp4*(_tmp17 + _tmp73*x1);
    _result(34, 86) = _tmp82*(_tmp54 + 1);
    _result(36, 86) = -_tmp13*_tmp4;
    _result(26, 87) = -_tmp16;
    _result(29, 87) = -x0*(_tmp14 - 2);
    _result(37, 87) = -_tmp83;
    _result(27, 88) = -_tmp26*x4 + _tmp46;
    _result(30, 88) = _tmp73 + x3;
    _result(38, 88) = -_tmp84 - Scalar(1)/Scalar(2)*x0;
    _result(28, 89) = -_tmp23*x0;
    _result(31, 89) = _tmp34;
    _result(39, 89) = _tmp2 + x1;
    _result(32, 90) = -_tmp55;
    _result(30, 91) = _tmp53;
    _result(33, 91) = -_tmp43*x3;
    _result(31, 92) = _tmp5*_tmp62;
    _result(32, 93) = Scalar(2.0)*x1;
    _result(33, 93) = -_tmp85 - Scalar(1)/Scalar(2)*x1;
    _result(37, 93) = -_tmp54*x1 - x4;
    _result(32, 94) = 2*_tmp40;
    _result(33, 94) = -_tmp67*x0;
    _result(38, 94) = -_tmp28*_tmp86;
    _result(32, 95) = _tmp21 + _tmp33;
    _result(33, 95) = -_tmp81*_tmp9*x4;
    _result(39, 95) = x3*(_tmp27 + _tmp59);
    _result(35, 96) = _tmp41 + 2;
    _result(36, 96) = _tmp87;
    _result(46, 96) = _tmp86 + x1 + x2;
    _result(36, 97) = _tmp88;
    _result(45, 97) = _tmp71*x1*x3;
    _result(47, 97) = 4 - _tmp6;
    _result(37, 98) = _tmp58;
    _result(48, 98) = _tmp0*x0 + 1;
    _result(38, 99) = 4;
    _result(41, 99) = _tmp47;
    _result(49, 99) = _tmp0 + _tmp41;
    _result(39, 100) = -x1/(_tmp51 + _tmp82);
    _result(42, 100) = -_tmp34*(_tmp15 + x3);
    _result(50, 100) = _tmp5;
    _result(40, 101) = _tmp15 + _tmp89 + 2;
    _result(43, 101) = _tmp90*x4;
    _result(41, 102) = -_tmp14 - 2;
    _result(44, 102) = x3 - 5;
    _result(42, 103) = -_tmp39*_tmp91;
    _result(45, 103) = _tmp17 + _tmp82 + x0;
    _result(43, 104) = _tmp92;
    _result(44, 104) = _tmp70*_tmp93*x0;
    _result(48, 104) = _tmp30 - _tmp94;
    _result(43, 105) = -_tmp15 - _tmp61*x3;
    _result(44, 105) = _tmp95;
    _result(49, 105) = _tmp41*_tmp86 - 1;
    _result(43, 106) = -x3*(_tmp24 + _tmp38);
    _result(44, 106) = -_tmp56;
    _result(50, 106) = _tmp79;
    _result(46, 107) = _tmp25*x2;
    _result(47, 107) = _tmp15;
    _result(57, 107) = _tmp14;
    _result(47, 108) = -2*_tmp86;
    _result(56, 108) = x2*(_tmp82 + 1);
    _result(58, 108) = _tmp96;
    _result(48, 109) = _tmp57 + 2;
    _result(51, 109) = -_tmp40*_tmp56*x4;
    _result(59, 109) = -_tmp90;
    _result(49, 110) = _tmp97;
    _result(52, 110) = -x0/_tmp98;
    _result(60, 110) = _tmp14;
    _result(53, 111) = -_tmp20 - x4;
    _result(61, 111) = _tmp99 - 2;
    _result(51, 112) = _tmp100*_tmp28;
    _result(54, 112) = _tmp26;
    _result(52, 113) = _tmp19 + _tmp29;
    _result(55, 113) = -_tmp5*x2 + x0;
    _result(53, 114) = -_tmp50*(_tmp30 - 1);
    _result(56, 114) = -_tmp10*x3 - _tmp17 - 2;
    _result(54, 115) = _tmp92;
    _result(55, 115) = -_tmp13 - 4;
    _result(59, 115) = -_tmp100 - _tmp85 - x4;
    _result(54, 116) = _tmp24 + _tmp41;
    _result(55, 116) = 4 - _tmp0;
    _result(60, 116) = _tmp41 + Scalar(2.0);
    _result(54, 117) = -_tmp15 - _tmp37;
    _result(55, 117) = 4 - _tmp12;
    _result(61, 117) = -x4*(_tmp102 + _tmp11);
    _result(57, 118) = _tmp3;
    _result(58, 118) = -_tmp103;
    _result(68, 118) = _tmp87*x1;
    _result(58, 119) = _tmp12 + _tmp41 - 2;
    _result(67, 119) = _tmp92;
    _result(59, 120) = -_tmp56 - 2;
    _result(62, 120) = -_tmp11*_tmp32;
    _result(70, 120) = 8*x4;
    _result(60, 121) = 2 - _tmp6;
    _result(63, 121) = -_tmp104;
    _result(71, 121) = -_tmp69*x2;
    _result(61, 122) = x1;
    _result(64, 122) = -Scalar(1)/Scalar(2)*x4 - 1;
    _result(72, 122) = -_tmp15 - x3*(_tmp11 + x1);
    _result(62, 123) = -_tmp14 - _tmp29;
    _result(65, 123) = _tmp24 + _tmp77*_tmp9;
    _result(63, 124) = _tmp0*_tmp40;
    _result(66, 124) = _tmp28*_tmp63;
    _result(64, 125) = -_tmp50*(_tmp20 + x2);
    _result(67, 125) = -_tmp33 - _tmp51 - x2;
    _result(65, 126) = Scalar(-2.0);
    _result(66, 126) = _tmp40*_tmp75;
    _result(70, 126) = _tmp48 + _tmp50;
    _result(65, 127) = _tmp103*_tmp30;
    _result(66, 127) = _tmp86 + _tmp93;
    _result(71, 127) = -_tmp91 - x4;
    _result(65, 128) = _tmp14 - _tmp41;
    _result(66, 128) = _tmp33;
    _result(72, 128) = _tmp44;
    _result(69, 129) = -_tmp101;
    _result(79, 129) = _tmp67*_tmp7;
    _result(69, 130) = _tmp13*x0 + x2;
    _result(78, 130) = 1;
    _result(80, 130) = -x3*(_tmp68 + x3);
    _result(70, 131) = -_tmp9/_tmp93;
    _result(73, 131) = _tmp83;
    _result(81, 131) = _tmp24 + _tmp76*x2 + x4;
    _result(71, 132) = 1;
    _result(74, 132) = 3 - _tmp0;
    _result(82, 132) = _tmp104;
    _result(72, 133) = _tmp26 + x3;
    _result(75, 133) = _tmp18;
    _result(83, 133) = _tmp26;
    _result(73, 134) = x1;
    _result(76, 134) = x0 - 3;
    _result(74, 135) = _tmp31*_tmp4;
    _result(77, 135) = (Scalar(1)/Scalar(8))*x4;
    _result(75, 136) = _tmp0*(_tmp51 + x0) + x1;
    _result(78, 136) = -_tmp2*_tmp9;
    _result(76, 137) = _tmp105;
    _result(77, 137) = -_tmp22*x0 - x3;
    _result(81, 137) = x4 - 4;
    _result(76, 138) = _tmp71*(_tmp20 + x3);
    _result(77, 138) = -_tmp72;
    _result(82, 138) = _tmp54;
    _result(76, 139) = _tmp106 + _tmp26 + _tmp88;
    _result(77, 139) = _tmp87 + x2;
    _result(83, 139) = _tmp93;
    _result(79, 140) = x0/(_tmp28 + _tmp95 + x0);
    _result(80, 140) = _tmp35*x2 - x0;
    _result(90, 140) = -_tmp27 - _tmp57;
    _result(80, 141) = -_tmp2 - _tmp41;
    _result(89, 141) = _tmp1;
    _result(91, 141) = _tmp90;
    _result(81, 142) = 5*x2 + x3;
    _result(84, 142) = 6*x0 + 6*x2;
    _result(92, 142) = -_tmp50 - x0;
    _result(82, 143) = -_tmp97;
    _result(85, 143) = _tmp107;
    _result(93, 143) = _tmp107;
    _result(83, 144) = _tmp36;
    _result(86, 144) = -_tmp17 - _tmp50*x1;
    _result(94, 144) = 8 - _tmp14;
    _result(84, 145) = -_tmp31 - x0 - x1;
    _result(87, 145) = -_tmp75 - x3;
    _result(85, 146) = _tmp51;
    _result(88, 146) = _tmp90*(_tmp28 + x4);
    _result(86, 147) = x3;
    _result(89, 147) = -x3/_tmp90;
    _result(87, 148) = _tmp46*(_tmp1 + _tmp11);
    _result(88, 148) = -x4*(_tmp29 + x2) + 1;
    _result(92, 148) = Scalar(1.0)*x0 - 2;
    _result(87, 149) = _tmp54 + _tmp78;
    _result(88, 149) = _tmp8;
    _result(93, 149) = _tmp74*x0;
    _result(87, 150) = _tmp102*x0;
    _result(88, 150) = -_tmp0 - _tmp14;
    _result(94, 150) = -_tmp2 - x2;
    _result(90, 151) = _tmp4 + x3;
    _result(91, 151) = _tmp5*x3;
    _result(101, 151) = -_tmp99;
    _result(91, 152) = -_tmp65 - 3*x0;
    _result(100, 152) = 12*_tmp86;
    _result(92, 153) = _tmp22*_tmp30;
    _result(95, 153) = -_tmp51 - x4 - 2;
    _result(93, 154) = -_tmp29 - _tmp94;
    _result(96, 154) = _tmp2;
    _result(97, 155) = _tmp105;
    _result(95, 156) = x4;
    _result(98, 156) = _tmp80*x4 + x4;
    _result(96, 157) = _tmp89 - 2;
    _result(97, 158) = _tmp31;
    _result(100, 158) = _tmp75 + _tmp84;
    _result(98, 159) = -_tmp46*_tmp88*x1;
    _result(99, 159) = _tmp99 + 4;
    _result(102, 159) = _tmp14*_tmp57;
    _result(103, 159) = 6;
    _result(98, 160) = -2*_tmp103 - _tmp29;
    _result(99, 160) = x0/(_tmp14 - _tmp2*_tmp49);
    _result(102, 160) = 1;
    _result(103, 160) = _tmp5;
    _result(98, 161) = -_tmp50*_tmp98 + x3;
    _result(99, 161) = -2;
    _result(102, 161) = _tmp32;
    _result(103, 161) = _tmp96;
    _result(104, 161) = _tmp14 + _tmp9*x0;
    _result(101, 162) = _tmp27 + _tmp3;
    _result(104, 162) = _tmp106;

    return _result;
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym
