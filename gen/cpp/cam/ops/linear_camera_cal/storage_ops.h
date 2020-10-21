//  -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <vector>

#include <Eigen/Dense>
#include <cam/linear_camera_cal.h>

namespace cam {
namespace linear_camera_cal {

/**
 * C++ StorageOps implementation for <class 'symforce.cam.linear_camera_cal.LinearCameraCal'>.
 */
template <typename Scalar>
struct StorageOps {
  static constexpr int32_t StorageDim() {
    return 4;
  }

  static void ToStorage(const cam::LinearCameraCal<Scalar>& a, std::vector<Scalar>* vec);
  static cam::LinearCameraCal<Scalar> FromStorage(const std::vector<Scalar>& vec);
};

}  // namespace linear_camera_cal
}  // namespace cam

// Wrapper to specialize the public concept
namespace geo {

template <>
struct StorageOps<cam::LinearCameraCal<double>>
    : public cam::linear_camera_cal::StorageOps<double> {};
template <>
struct StorageOps<cam::LinearCameraCal<float>> : public cam::linear_camera_cal::StorageOps<float> {
};

}  // namespace geo
