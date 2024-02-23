#pragma once

#include "eigen3/Eigen/Dense"
#include "vector2d.hpp"

template <int size> class Matrix {
public:
  Matrix() = default;
  ~Matrix() = default;
  Matrix(const Eigen::Matrix<double, size, size> &other) : mat_(other) {}
  Matrix(Eigen::Matrix<double, size, size> &&other) : mat_(std::move(other)) {}
  const Eigen::Matrix<double, size, size> &Eigen() const { return mat_; }

  template <typename... Args>
  Matrix(Args... args) : mat_(Eigen::Matrix<double, size, size>()) {
    static_assert(sizeof...(args) == size * size,
                  "The number of arguments must match the matrix size.");
    setValues(0, args...);
  }

  bool operator==(const Matrix<size> &other) const {
    return mat_ == other.Eigen();
  }
  bool operator!=(const Matrix<size> &other) const {
    return mat_ != other.Eigen();
  }

  Matrix<size> operator*(const Matrix<size> &other) const {
    Matrix<size> result;
    result.mat_ = mat_ * other.mat_;
    return result;
  }

  Matrix<size> &operator*=(const Matrix<size> &other) const {
    mat_ *= other.mat_;
    return *this;
  }

  Tuple operator*(const Tuple &other) const {
    return Tuple(mat_ * other.Eigen());
  }

  // copy by value
  Matrix<size> Transposed() {
    return Matrix<size>(
        Eigen::Matrix<double, size, size>(mat_.transpose().eval()));
  }

  // copy by value
  Matrix<size> Inversed() {
    return Matrix<size>(
        Eigen::Matrix<double, size, size>(mat_.inverse().eval()));
  }

//     // maybe also custom functions
//   Matrix<size>& Translate(double x, double y, double z) {
//   }


private:
  template <typename T, typename... Args>
  void setValues(int index, T val, Args... args) {
    int row = index / size;
    int col = index % size;
    mat_(row, col) = val;
    setValues(index + 1, args...);
  }

  void setValues(int index) {}

protected:
  Eigen::Matrix<double, size, size> mat_;
};

namespace math_constants {
static const Matrix<2> m2_identity(1, 0, 0, 1);
static const Matrix<3> m3_identity(1, 0, 0, 0, 1, 0, 0, 0, 1);
static const Matrix<4> m4_identity(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
                                   1);
Matrix<4> TranslationMatrix(double x, double y, double z);
Matrix<4> ScaleMatrix(double x, double y, double z);
Matrix<4> RotationMatrixX(double radians);
Matrix<4> RotationMatrixY(double radians);
Matrix<4> RotationMatrixZ(double radians);
Matrix<4> ShearMatrix(double xy, double xz, double yx, double yz, double zx, double zy);
double Radians(double degrees);
} // namespace math_constants