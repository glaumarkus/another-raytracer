#include "math/constants.hpp"
#include "math/mat.hpp"
#include "primitives/object.hpp"
#include "math/ray.hpp"
#include "raytrace/light.hpp"
#include "raytrace/lighting_model.hpp"
#include <gtest/gtest.h>

auto equalc = [](Color lhs, Color rhs) {
  bool result = false;
  if (std::abs(lhs.r() - rhs.r()) < kEpsilon &&
      std::abs(lhs.g() - rhs.g()) < kEpsilon &&
      std::abs(lhs.b() - rhs.b()) < kEpsilon) {
    result = true;
  }
  return result;
};

TEST(chapter06, sphere_normal) {
  auto p1 = Point(1, 0, 0);
  auto p2 = Point(0, 1, 0);
  auto p3 = Point(0, 0, 1);
  Sphere s;
  EXPECT_EQ(SphereNormal(s, p1), Vector(1, 0, 0));
  EXPECT_EQ(SphereNormal(s, p2), Vector(0, 1, 0));
  EXPECT_EQ(SphereNormal(s, p3), Vector(0, 0, 1));
}

TEST(chapter06, sphere_normal_transformed1) {
  Sphere s;
  s.Transform(math_constants::TranslationMatrix(0, 1, 0));
  auto s_n = SphereNormal(s, Point(0, 1.70711, -0.70711));
  EXPECT_TRUE(equal(s_n.x(), 0));
  EXPECT_TRUE(equal(s_n.y(), 0.70711));
  EXPECT_TRUE(equal(s_n.z(), -0.70711));
}

TEST(chapter06, sphere_normal_transformed2) {
  Sphere s;
  auto t = math_constants::ScaleMatrix(1, 0.5, 1) *
           math_constants::RotationMatrixZ(M_PI / 5);
  s.Transform(t);
  auto s_n = SphereNormal(s, Point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));
  EXPECT_TRUE(equal(s_n.x(), 0));
  EXPECT_TRUE(equal(s_n.y(), 0.97014));
  EXPECT_TRUE(equal(s_n.z(), -0.24254));
}

TEST(chapter06, reflect1) {
  auto v1 = Vector(1, -1, 0);
  auto n1 = Vector(0, 1, 0);
  EXPECT_EQ(v1.Reflect(n1), Vector(1, 1, 0));
}

TEST(chapter06, reflect2) {
  auto v1 = Vector(0, -1, 0);
  auto n1 = Vector(std::sqrt(2) / 2, std::sqrt(2) / 2, 0);
  auto reflected = v1.Reflect(n1);
  EXPECT_TRUE(equalv(reflected, Vector(1, 0, 0)));
}

TEST(chapter06, eye_between_light_and_surface) {
  Point position(0, 0, 0);
  Vector eye(0, 0, -1);
  Vector normal(0, 0, -1);
  Material m;
  PhongReflectionModel model;
  auto light = std::make_shared<PointLight>(Point(0, 0, -10), Color(1, 1, 1));
  auto lights = std::vector<std::shared_ptr<Light>>();
  lights.push_back(light);
  auto cc = model.GetLightingColor(m, lights, position, eye, normal, 0.0);
  EXPECT_TRUE(equalc(model.GetLightingColor(m, lights, position, eye, normal, 0.0),
                     Color(1.9, 1.9, 1.9)));
}

TEST(chapter06, eye_45_degrees) {
  Point position(0, 0, 0);
  Vector eye(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
  Vector normal(0, 0, -1);
  Material m;
  auto light = std::make_shared<PointLight>(Point(0, 0, -10), Color(1, 1, 1));
  auto lights = std::vector<std::shared_ptr<Light>>();
  lights.push_back(light);
  PhongReflectionModel model;
  EXPECT_TRUE(equalc(model.GetLightingColor(m, lights, position, eye, normal, 0.0),
                     Color(1, 1, 1)));
}

TEST(chapter06, eye_45_degrees2) {
  Point position(0, 0, 0);
  Vector eye(0, 0, -1);
  Vector normal(0, 0, -1);
  Material m;
  PhongReflectionModel model;
  auto light = std::make_shared<PointLight>(Point(0, 10, -10), Color(1, 1, 1));
  auto lights = std::vector<std::shared_ptr<Light>>();
  lights.push_back(light);
  EXPECT_TRUE(equalc(model.GetLightingColor(m, lights, position, eye, normal, 0.0),
                     Color(0.7364, 0.7364, 0.7364)));
}

TEST(chapter06, eye_reflection_vector) {
  Point position(0, 0, 0);
  Vector eye(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
  Vector normal(0, 0, -1);
  Material m;
  PhongReflectionModel model;
  auto light = std::make_shared<PointLight>(Point(0, 10, -10), Color(1, 1, 1));
  auto lights = std::vector<std::shared_ptr<Light>>();
  lights.push_back(light);
  auto cc = model.GetLightingColor(m, lights, position, eye, normal, 0.0);
  EXPECT_TRUE(equalc(model.GetLightingColor(m, lights, position, eye, normal, 0.0),
                     Color(1.6364, 1.6364, 1.6364)));
}

TEST(chapter06, eye_behind_surface) {
  Point position(0, 0, 0);
  Vector eye(0, 0, -1);
  Vector normal(0, 0, -1);
  Material m;
  PhongReflectionModel model;
  auto light = std::make_shared<PointLight>(Point(0, 0, 10), Color(1, 1, 1));
  auto lights = std::vector<std::shared_ptr<Light>>();
  lights.push_back(light);
  EXPECT_TRUE(equalc(model.GetLightingColor(m, lights, position, eye, normal, 0.0),
                     Color(0.1, 0.1, 0.1)));
}
