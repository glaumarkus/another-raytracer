#pragma once

#include "math/mat.hpp"
#include "math/ray.hpp"
#include "math/vector2d.hpp"

class Camera {
public:
  Camera() = delete;
  Camera(int width, int height, double fov);

  void SetTransform(const Matrix<4> &transform);
  const Matrix<4> &ViewTransform() const;
  Ray RayForPixel(int x, int y) const;
  ~Camera() = default;

protected:
  int width_;
  int height_;
  double fov_;
  Matrix<4> transformation_{};
  double half_view_;
  double aspect_;
  double half_width_;
  double half_height_;
  double pixel_size_;
};

Matrix<4> CalculateTransform(Point from, Point to, Vector up);

// class Pointcamera {
//   Pointcamera()
// };