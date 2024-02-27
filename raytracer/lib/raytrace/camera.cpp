#include "camera.hpp"

Camera::Camera(int width, int height, double fov)
    : width_(width), height_(height), fov_(fov),
      transformation_(math_constants::m4_identity) {
  half_view_ = std::tan(fov_ / 2.0);
  aspect_ = static_cast<double>(width_) / height_;

  if (aspect_ >= 1) {
    half_height_ = half_view_ / aspect_;
    half_width_ = half_view_;
  } else {
    half_height_ = half_view_;
    half_width_ = half_view_ * aspect_;
  }
  pixel_size_ = (half_width_ * 2) / width_;
}
Matrix<4> CalculateTransform(Point from, Point to, Vector up) {
  auto forward = (to - from).Normalized();
  auto upn = up.Normalized();
  auto left = forward.Cross(upn);
  auto true_up = left.Cross(forward);
  auto transformation = Matrix<4>{left.x(),
                                  left.y(),
                                  left.z(),
                                  0,
                                  true_up.x(),
                                  true_up.y(),
                                  true_up.z(),
                                  0,
                                  -forward.x(),
                                  -forward.y(),
                                  -forward.z(),
                                  0,
                                  0,
                                  0,
                                  0,
                                  1};
  return transformation *
         math_constants::TranslationMatrix(-from.x(), -from.y(), -from.z());
}

Ray Camera::RayForPixel(int px, int py) const {
  auto xoffset = (px + 0.5) * pixel_size_;
  auto yoffset = (py + 0.5) * pixel_size_;
  auto world_x = half_width_ - xoffset;
  auto world_y = half_height_ - yoffset;
  auto pixel =
      (transformation_.Eigen().inverse() * Point(world_x, world_y, -1).Eigen());
  auto origin = (transformation_.Eigen().inverse() * Point(0, 0, 0).Eigen());
  auto direction = (pixel - origin).normalized();
  return Ray(Point(origin), Vector(direction));
}

void Camera::SetTransform(const Matrix<4> &transform) {
  transformation_ = transform;
}
const Matrix<4> &Camera::ViewTransform() const { return transformation_; }