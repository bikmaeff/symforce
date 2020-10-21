//  -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>

#include "../lie_group_ops.h"

// Forward declare class, without including header
namespace geo {
template <typename ScalarType>
class Rot3;
}  // namespace geo

namespace geo {
namespace rot3 {

/**
 * C++ LieGroupOps implementation for <class 'symforce.geo.rot3.Rot3'>.
 */
template <typename Scalar>
struct LieGroupOps {
  static constexpr int32_t TangentDim() {
    return 3;
  }

  using TangentVec = Eigen::Matrix<Scalar, TangentDim(), 1>;

  static geo::Rot3<Scalar> FromTangent(const Eigen::Matrix<Scalar, 3, 1>& vec,
                                       const Scalar epsilon);
  static Eigen::Matrix<Scalar, 3, 1> ToTangent(const geo::Rot3<Scalar>& a, const Scalar epsilon);
  static geo::Rot3<Scalar> Retract(const geo::Rot3<Scalar>& a,
                                   const Eigen::Matrix<Scalar, 3, 1>& vec, const Scalar epsilon);
  static Eigen::Matrix<Scalar, 3, 1> LocalCoordinates(const geo::Rot3<Scalar>& a,
                                                      const geo::Rot3<Scalar>& b,
                                                      const Scalar epsilon);
};

}  // namespace rot3

// Specialization into the top level concept
template <>
struct LieGroupOps<Rot3<double>> : public rot3::LieGroupOps<double> {};
template <>
struct LieGroupOps<Rot3<float>> : public rot3::LieGroupOps<float> {};

}  // namespace geo
