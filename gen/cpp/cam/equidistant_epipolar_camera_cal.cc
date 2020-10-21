//  -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./equidistant_epipolar_camera_cal.h"

// Explicit instantiation
template class cam::EquidistantEpipolarCameraCal<double>;
template class cam::EquidistantEpipolarCameraCal<float>;

// Camera operation implementations
namespace cam {

template <typename Scalar>
Eigen::Matrix<Scalar, 2, 1> EquidistantEpipolarCameraCal<Scalar>::FocalLength() const {
  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _self = Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 2, 1> _focal_length;

  _focal_length(0, 0) = _self[0];
  _focal_length(1, 0) = _self[1];

  return _focal_length;
}

template <typename Scalar>
Eigen::Matrix<Scalar, 2, 1> EquidistantEpipolarCameraCal<Scalar>::PrincipalPoint() const {
  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _self = Data();

  // Intermediate terms (0)

  // Output terms (1)
  Eigen::Matrix<Scalar, 2, 1> _principal_point;

  _principal_point(0, 0) = _self[2];
  _principal_point(1, 0) = _self[3];

  return _principal_point;
}

template <typename Scalar>
Eigen::Matrix<Scalar, 2, 1> EquidistantEpipolarCameraCal<Scalar>::PixelFromCameraPoint(
    const Eigen::Matrix<Scalar, 3, 1>& point, const Scalar epsilon, Scalar* const is_valid) const {
  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _self = Data();

  // Intermediate terms (0)

  // Output terms (2)
  Eigen::Matrix<Scalar, 2, 1> _pixel;

  _pixel(0, 0) =
      _self[0] * std::atan2(point(0, 0), std::sqrt(epsilon + (point(1, 0) * point(1, 0)) +
                                                   (point(2, 0) * point(2, 0)))) +
      _self[2];
  _pixel(1, 0) = _self[1] * std::atan2(point(1, 0), epsilon + point(2, 0)) + _self[3];

  if (is_valid != nullptr) {
    Scalar& _is_valid = (*is_valid);

    _is_valid = std::max<Scalar>(0, (((point(2, 0)) > 0) - ((point(2, 0)) < 0)));
  }

  return _pixel;
}

template <typename Scalar>
Eigen::Matrix<Scalar, 3, 1> EquidistantEpipolarCameraCal<Scalar>::CameraRayFromPixel(
    const Eigen::Matrix<Scalar, 2, 1>& pixel, const Scalar epsilon, Scalar* const is_valid) const {
  // Input arrays
  const Eigen::Matrix<Scalar, 4, 1>& _self = Data();

  // Intermediate terms (4)
  const Scalar _tmp0 = (-_self[2] + pixel(0, 0)) / _self[0];
  const Scalar _tmp1 = (-_self[3] + pixel(1, 0)) / _self[1];
  const Scalar _tmp2 = std::cos(_tmp0);
  const Scalar _tmp3 = M_PI_2;

  // Output terms (2)
  Eigen::Matrix<Scalar, 3, 1> _camera_ray;

  _camera_ray(0, 0) = std::sin(_tmp0);
  _camera_ray(1, 0) = _tmp2 * std::sin(_tmp1);
  _camera_ray(2, 0) = _tmp2 * std::cos(_tmp1);

  if (is_valid != nullptr) {
    Scalar& _is_valid = (*is_valid);

    _is_valid =
        std::max<Scalar>(0, (((_tmp3 - std::fabs(_tmp0)) > 0) - ((_tmp3 - std::fabs(_tmp0)) < 0))) *
        std::max<Scalar>(0, (((_tmp3 - std::fabs(_tmp1)) > 0) - ((_tmp3 - std::fabs(_tmp1)) < 0)));
  }

  return _camera_ray;
}

}  // namespace cam

// Print implementations
std::ostream& operator<<(std::ostream& os, const cam::EquidistantEpipolarCameraCald& a) {
  const Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n", "[", "]");
  os << "<EquidistantEpipolarCameraCald " << a.Data().transpose().format(fmt) << ">";
  return os;
}
std::ostream& operator<<(std::ostream& os, const cam::EquidistantEpipolarCameraCalf& a) {
  const Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n", "[", "]");
  os << "<EquidistantEpipolarCameraCalf " << a.Data().transpose().format(fmt) << ">";
  return os;
}

// Concept implementations for this class
#include "./ops/equidistant_epipolar_camera_cal/storage_ops.cc"
