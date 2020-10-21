//  ----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>
#include <geo/pose2.h>

namespace geo {
namespace pose2 {

/**
 * C++ GroupOps implementation for <class 'symforce.geo.pose2.Pose2'>.
 */
template <typename Scalar>
struct GroupOps {
  using SelfJacobian = Eigen::Matrix<Scalar, geo::LieGroupOps<Pose2<Scalar>>::TangentDim(),
                                     geo::LieGroupOps<Pose2<Scalar>>::TangentDim()>;

  static geo::Pose2<Scalar> Identity();
  static geo::Pose2<Scalar> Inverse(const geo::Pose2<Scalar>& a);
  static geo::Pose2<Scalar> Compose(const geo::Pose2<Scalar>& a, const geo::Pose2<Scalar>& b);
  static geo::Pose2<Scalar> Between(const geo::Pose2<Scalar>& a, const geo::Pose2<Scalar>& b);
  static geo::Pose2<Scalar> InverseWithJacobian(
      const geo::Pose2<Scalar>& a, Eigen::Matrix<Scalar, 3, 3>* const res_D_a = nullptr);
  static geo::Pose2<Scalar> ComposeWithJacobians(
      const geo::Pose2<Scalar>& a, const geo::Pose2<Scalar>& b,
      Eigen::Matrix<Scalar, 3, 3>* const res_D_a = nullptr,
      Eigen::Matrix<Scalar, 3, 3>* const res_D_b = nullptr);
  static geo::Pose2<Scalar> BetweenWithJacobians(
      const geo::Pose2<Scalar>& a, const geo::Pose2<Scalar>& b,
      Eigen::Matrix<Scalar, 3, 3>* const res_D_a = nullptr,
      Eigen::Matrix<Scalar, 3, 3>* const res_D_b = nullptr);
};

}  // namespace pose2

// Wrapper to specialize the public concept
template <>
struct GroupOps<Pose2<double>> : public pose2::GroupOps<double> {};
template <>
struct GroupOps<Pose2<float>> : public pose2::GroupOps<float> {};

}  // namespace geo
