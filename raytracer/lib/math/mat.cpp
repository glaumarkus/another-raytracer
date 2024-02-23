#include "mat.hpp"
#include <cmath>

namespace math_constants {

Matrix<4> TranslationMatrix(double x, double y, double z) {
  return Matrix<4>(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
}
Matrix<4> ScaleMatrix(double x, double y, double z) {
  return Matrix<4>(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
}
Matrix<4> RotationMatrixX(double radians) {
  return Matrix<4>(1, 0, 0, 0,                                  //
                   0, std::cos(radians), -std::sin(radians), 0, //
                   0, std::sin(radians), std::cos(radians), 0,  //
                   0, 0, 0, 1);                                 //
}
Matrix<4> RotationMatrixY(double radians) {
  return Matrix<4>(std::cos(radians), 0, std::sin(radians), 0,  //
                   0, 1, 0, 0,                                  //
                   -std::sin(radians), 0, std::cos(radians), 0, //
                   0, 0, 0, 1);                                 //
}
Matrix<4> RotationMatrixZ(double radians) {
  return Matrix<4>(std::cos(radians), -std::sin(radians), 0, 0, //
                   std::sin(radians), std::cos(radians), 0, 0,  //
                   0, 0, 1, 0,                                  //
                   0, 0, 0, 1);                                 //
}

Matrix<4> ShearMatrix(double xy, double xz, double yx, double yz, double zx,
                      double zy) {
  return Matrix<4>(1, xy, xz, 0, //
                   yx, 1, yz, 0, //
                   zx, zy, 1, 0, //
                   0, 0, 0, 1);  //
}
double Radians(double degrees) { return degrees / 180 * M_PI; }
} // namespace math_constants