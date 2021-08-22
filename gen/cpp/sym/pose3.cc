//  -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./pose3.h"

namespace sym {

// Print implementations
std::ostream& operator<<(std::ostream& os, const Pose3d& a) {
  const Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n", "[", "]");
  os << "<Pose3d " << a.Data().transpose().format(fmt) << ">";
  return os;
}
std::ostream& operator<<(std::ostream& os, const Pose3f& a) {
  const Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n", "[", "]");
  os << "<Pose3f " << a.Data().transpose().format(fmt) << ">";
  return os;
}

}  // namespace sym

// --------------------------------------------------------------------------
// Custom generated methods
// --------------------------------------------------------------------------

template <typename Scalar>
Eigen::Matrix<Scalar, 3, 1> sym::Pose3<Scalar>::InverseCompose(
    const Eigen::Matrix<Scalar, 3, 1>& point) const {
  // Total ops: 65

  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _self = Data();

  // Intermediate terms (20)
  const Scalar _tmp0 = 2 * _self[1];
  const Scalar _tmp1 = _self[0] * _tmp0;
  const Scalar _tmp2 = 2 * _self[3];
  const Scalar _tmp3 = _self[2] * _tmp2;
  const Scalar _tmp4 = _tmp1 + _tmp3;
  const Scalar _tmp5 = 2 * _self[0] * _self[2];
  const Scalar _tmp6 = _self[1] * _tmp2;
  const Scalar _tmp7 = _tmp5 - _tmp6;
  const Scalar _tmp8 = -2 * std::pow(_self[2], Scalar(2));
  const Scalar _tmp9 = 1 - 2 * std::pow(_self[1], Scalar(2));
  const Scalar _tmp10 = _tmp8 + _tmp9;
  const Scalar _tmp11 = _tmp1 - _tmp3;
  const Scalar _tmp12 = _self[2] * _tmp0;
  const Scalar _tmp13 = _self[0] * _tmp2;
  const Scalar _tmp14 = _tmp12 + _tmp13;
  const Scalar _tmp15 = -2 * std::pow(_self[0], Scalar(2));
  const Scalar _tmp16 = _tmp15 + _tmp8 + 1;
  const Scalar _tmp17 = _tmp5 + _tmp6;
  const Scalar _tmp18 = _tmp12 - _tmp13;
  const Scalar _tmp19 = _tmp15 + _tmp9;

  // Output terms (1)
  Eigen::Matrix<Scalar, 3, 1> _res;

  _res(0, 0) = -_self[4] * _tmp10 - _self[5] * _tmp4 - _self[6] * _tmp7 + _tmp10 * point(0, 0) +
               _tmp4 * point(1, 0) + _tmp7 * point(2, 0);
  _res(1, 0) = -_self[4] * _tmp11 - _self[5] * _tmp16 - _self[6] * _tmp14 + _tmp11 * point(0, 0) +
               _tmp14 * point(2, 0) + _tmp16 * point(1, 0);
  _res(2, 0) = -_self[4] * _tmp17 - _self[5] * _tmp18 - _self[6] * _tmp19 + _tmp17 * point(0, 0) +
               _tmp18 * point(1, 0) + _tmp19 * point(2, 0);

  return _res;
}

// Explicit instantiation
template class sym::Pose3<double>;
template class sym::Pose3<float>;
