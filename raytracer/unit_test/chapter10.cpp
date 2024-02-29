#include "imgui/image_data.hpp"
#include "math/constants.hpp"
#include "math/intersections.hpp"
#include "math/mat.hpp"
#include "math/material.hpp"
#include "math/pattern.hpp"
#include "primitives/sphere.hpp"
#include "raytrace/camera.hpp"
#include "raytrace/lighting_model.hpp"
#include <gtest/gtest.h>
#include <memory>

auto equalc = [](Color lhs, Color rhs) {
  bool result = false;
  if (std::abs(lhs.r() - rhs.r()) < kEpsilon &&
      std::abs(lhs.g() - rhs.g()) < kEpsilon &&
      std::abs(lhs.b() - rhs.b()) < kEpsilon) {
    result = true;
  }
  return result;
};

TEST(chapter10, stripe_pattern_1) {
  auto white = Color(1);
  auto black = Color(0);
  auto pattern = StripePattern(white, black);
  EXPECT_TRUE(equalc(pattern.GetColor(Point(0, 0, 0)), white));
  EXPECT_TRUE(equalc(pattern.GetColor(Point(0, 1, 0)), white));
  EXPECT_TRUE(equalc(pattern.GetColor(Point(0, 2, 0)), white));
  EXPECT_TRUE(equalc(pattern.GetColor(Point(0, 0, 0)), white));
  EXPECT_TRUE(equalc(pattern.GetColor(Point(0, 0, 1)), white));
  EXPECT_TRUE(equalc(pattern.GetColor(Point(0, 0, 2)), white));
  EXPECT_TRUE(equalc(pattern.GetColor(Point(0.9, 0, 0)), white));
  EXPECT_TRUE(equalc(pattern.GetColor(Point(1, 0, 0)), black));
  EXPECT_TRUE(equalc(pattern.GetColor(Point(-0.1, 0, 0)), black));
  EXPECT_TRUE(equalc(pattern.GetColor(Point(-1.1, 0, 0)), white));
  EXPECT_TRUE(equalc(pattern.GetColor(Point(-1, 0, 0)), black));
}

TEST(chapter10, stripe_pattern_2) {
  auto white = Color(1);
  auto black = Color(0);
  auto pattern = std::make_shared<StripePattern>(white, black);
  auto cast_pattern = std::shared_ptr<Pattern>(std::move(pattern));
  Material m;
  m.SetAmbient(1.0);
  m.SetDiffuse(0.0);
  m.SetSpecular(0.0);
  m.SetPattern(cast_pattern);
  auto eye = Vector(0, 0, -1);
  auto normal = Vector(0, 0, -1);
  auto light = std::make_shared<PointLight>(Point(0, 0, -10), Color(1, 1, 1));
  auto lights = std::vector<std::shared_ptr<Light>>();
  lights.push_back(light);
  PhongReflectionModel model;
  auto c1 =
      model.GetLightingColor(m, lights, Point(0.9, 0, 0), eye, normal, 0.0);
  auto c2 =
      model.GetLightingColor(m, lights, Point(1.1, 0, 0), eye, normal, 0.0);

  EXPECT_TRUE(equalc(c1, white));
  EXPECT_TRUE(equalc(c2, black));
}

TEST(chapter10, assign_transformation_1) {
  auto transform = math_constants::m4_identity;
  auto white = Color(1);
  auto black = Color(0);
  auto pattern = std::make_shared<StripePattern>(white, black);
  auto cast_pattern = std::shared_ptr<Pattern>(std::move(pattern));
  cast_pattern->SetTransform(transform);
  EXPECT_EQ(cast_pattern->GetTransform().Eigen(), transform.Eigen());
}

TEST(chapter10, assign_transformation_2) {
  auto transform = math_constants::TranslationMatrix(1, 2, 3);
  auto white = Color(1);
  auto black = Color(0);
  auto pattern = std::make_shared<StripePattern>(white, black);
  auto cast_pattern = std::shared_ptr<Pattern>(std::move(pattern));
  cast_pattern->SetTransform(transform);
  EXPECT_EQ(cast_pattern->GetTransform().Eigen(), transform.Eigen());
}

TEST(chapter10, test_pattern_transformation_1) {
  auto transform = math_constants::ScaleMatrix(2, 2, 2);
  Sphere s;
  s.Transform(transform);
  auto pattern = std::make_shared<TestPattern>();
  auto cast_pattern = std::shared_ptr<Pattern>(std::move(pattern));
  EXPECT_TRUE(equalc(cast_pattern->ColorOnObject(Point(2, 3, 4), &s),
                     Color(1, 1.5, 2)));
}

TEST(chapter10, test_pattern_transformation_2) {
  auto transform = math_constants::ScaleMatrix(2, 2, 2);
  Sphere s;
  auto pattern = std::make_shared<TestPattern>();
  auto cast_pattern = std::shared_ptr<Pattern>(std::move(pattern));
  cast_pattern->SetTransform(transform);
  EXPECT_TRUE(equalc(cast_pattern->ColorOnObject(Point(2, 3, 4), &s),
                     Color(1, 1.5, 2)));
}

TEST(chapter10, test_pattern_transformation_3) {
  auto transform = math_constants::ScaleMatrix(2, 2, 2);
  auto transform2 = math_constants::TranslationMatrix(0.5, 1, 1.5);
  Sphere s;
  s.Transform(transform);
  auto pattern = std::make_shared<TestPattern>();
  auto cast_pattern = std::shared_ptr<Pattern>(std::move(pattern));
  cast_pattern->SetTransform(transform2);
  EXPECT_TRUE(equalc(cast_pattern->ColorOnObject(Point(2.5, 3, 3.5), &s),
                     Color(0.75, 0.5, 0.25)));
}

TEST(chapter10, test_gradient_pattern) {
  auto white = Color(1);
  auto black = Color(0);
  auto pattern = std::make_shared<Gradient>(white, black);
  EXPECT_TRUE(
      equalc(pattern->GetColor(Point(0.25, 0, 0)), Color(0.75, 0.75, 0.75)));
  EXPECT_TRUE(
      equalc(pattern->GetColor(Point(0.5, 0, 0)), Color(0.5, 0.5, 0.5)));
  EXPECT_TRUE(
      equalc(pattern->GetColor(Point(0.75, 0, 0)), Color(0.25, 0.25, 0.25)));
}

TEST(chapter10, test_ring_pattern) {
  auto white = Color(1);
  auto black = Color(0);
  auto pattern = std::make_shared<Ring>(white, black);
  EXPECT_TRUE(equalc(pattern->GetColor(Point(0, 0, 0)), white));
  EXPECT_TRUE(equalc(pattern->GetColor(Point(1, 0, 0)), black));
  EXPECT_TRUE(equalc(pattern->GetColor(Point(0, 0, 1)), black));
  EXPECT_TRUE(equalc(pattern->GetColor(Point(0.708, 0, 0.708)), black));
}

TEST(chapter10, test_3dchecker_pattern) {
  auto white = Color(1);
  auto black = Color(0);
  auto pattern = std::make_shared<Checker>(white, black);
  EXPECT_TRUE(equalc(pattern->GetColor(Point(0, 0, 0)), white));
  EXPECT_TRUE(equalc(pattern->GetColor(Point(0.99, 0, 0)), white));
  EXPECT_TRUE(equalc(pattern->GetColor(Point(1.01, 0, 0)), black));

  EXPECT_TRUE(equalc(pattern->GetColor(Point(0, 0, 0)), white));
  EXPECT_TRUE(equalc(pattern->GetColor(Point(0, 0.99, 0)), white));
  EXPECT_TRUE(equalc(pattern->GetColor(Point(0, 1.01, 0)), black));

  EXPECT_TRUE(equalc(pattern->GetColor(Point(0, 0, 0)), white));
  EXPECT_TRUE(equalc(pattern->GetColor(Point(0, 0, 0.99)), white));
  EXPECT_TRUE(equalc(pattern->GetColor(Point(0, 0, 1.01)), black));
}