#include "imgui/image_data.hpp"
#include "math/constants.hpp"
#include "math/intersections.hpp"
#include "math/mat.hpp"
#include "math/material.hpp"
#include "math/pattern.hpp"
#include "math/prepare_computations.hpp"
#include "primitives/plane.hpp"
#include "primitives/primitives.hpp"
#include "primitives/sphere.hpp"
#include "raytrace/camera.hpp"
#include "raytrace/lighting_model.hpp"
#include "utility/logger.hpp"
#include "utility/world_parser.hpp"
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

TEST(chapter11, reflect_vector) {
  auto p = Plane();
  auto r = Ray(Point(0, 1, -1), Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
  Intersections i;
  i.Add(std::sqrt(2), &p);
  auto comps = PrepareComputations(i, r);
  EXPECT_TRUE(equalv(comps.GetReflect(),
                     Vector(0, std::sqrt(2) / 2, std::sqrt(2) / 2)));
}

TEST(chapter11, reflected_color_non_reflective_material) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
  world->GetObjects()[1]->GetMaterial().SetAmbient(1.0);
  Intersections i;
  i.Add(1, world->GetObjects()[1].get());
  auto comps = PrepareComputations(i, r);
  PhongReflectionCompleteModel model;
  auto reflected_color = world->ReflectedColor(comps, &model);
  EXPECT_TRUE(equalc(reflected_color, Color(0)));
}

TEST(chapter11, reflected_color_reflective_material) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  world->SetReflectionIterations(5);
  auto r = Ray(Point(0, 0, -3), Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
  auto plane = std::make_shared<Plane>();
  plane->GetMaterial().SetReflective(0.5);
  plane->Transform(math_constants::TranslationMatrix(0, -1, 0));
  world->Add(plane);
  Intersections i;
  i.Add(std::sqrt(2), plane.get());
  auto intersections = world->Intersect(r);
  auto comps = PrepareComputations(i, r);
  PhongReflectionCompleteModel model;
  auto reflected_color = world->ReflectedColor(comps, &model);
  EXPECT_TRUE(equalc(reflected_color, Color(0.19033, 0.23791, 0.14274)));
}

TEST(chapter11, shade_hit_reflective) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  world->SetReflectionIterations(5);
  auto r = Ray(Point(0, 0, -3), Vector(0, -std::sqrt(2) / 2, std::sqrt(2) / 2));
  auto plane = std::make_shared<Plane>();
  plane->GetMaterial().SetReflective(0.5);
  plane->Transform(math_constants::TranslationMatrix(0, -1, 0));
  world->Add(plane);
  // Intersections i;
  // i.Add(std::sqrt(2), plane.get());
  auto intersections = world->Intersect(r);
  auto comps = PrepareComputations(intersections, r);
  PhongReflectionCompleteModel model;
  auto reflected_color = world->ShadeHit(comps, &model);
  EXPECT_TRUE(
      equalc(reflected_color, Color(0.87675770936103614, 0.9243407894559198,
                                    0.82917462926615237)));
}

TEST(chapter11, terminate_recursion) {

  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter11_infinite_recursion.yaml");
  world->SetReflectionIterations(5);
  auto r = Ray(Point(0, 0, 0), Vector(0, 1, 0));
  PhongReflectionCompleteModel model;
  auto color = world->ColorAt(r, &model);
}

TEST(chapter11, material_adjustments) {
  Material m;
  EXPECT_EQ(m.Transparent(), 0.0);
  EXPECT_EQ(m.RefractiveIdx(), 1.0);
}

TEST(chapter11, refraction_test) {

  auto r = Ray(Point(0, 0, -4), Vector(0, 0, 1));

  auto s1 = GlassSphere();
  auto s2 = GlassSphere();
  auto s3 = GlassSphere();
  s1.Transform(math_constants::ScaleMatrix(2, 2, 2));
  s2.Transform(math_constants::TranslationMatrix(0, 0, 0.25));
  s2.GetMaterial().SetRefractiveIdx(2.0);
  s3.Transform(math_constants::TranslationMatrix(0, 0, 0.25));
  s3.GetMaterial().SetRefractiveIdx(2.5);
  auto i = Intersections();
  i.Add(2, &s1);
  i.Add(2.75, &s2);
  i.Add(3.25, &s3);
  i.Add(4.75, &s2);
  i.Add(5.25, &s3);
  i.Add(6, &s1);

  // check all n1 / n2
  // auto comps1 = PrepareComputations(i.Get()[0], r);
  // auto comps2 = PrepareComputations(i.Get()[1], r);
  // auto comps3 = PrepareComputations(i.Get()[2], r);
  // auto comps4 = PrepareComputations(i.Get()[3], r);
  // auto comps5 = PrepareComputations(i.Get()[4], r);
  // auto comps6 = PrepareComputations(i.Get()[5], r);

  // EXPECT_EQ(comps1.N1(), 1.0);
  // EXPECT_EQ(comps1.N2(), 1.5);

  // EXPECT_EQ(comps2.N1(), 1.5);
  // EXPECT_EQ(comps2.N2(), 2.0);

  // EXPECT_EQ(comps3.N1(), 2.0);
  // EXPECT_EQ(comps3.N2(), 2.5);

  // EXPECT_EQ(comps4.N1(), 2.5);
  // EXPECT_EQ(comps4.N2(), 2.5);

  // EXPECT_EQ(comps5.N1(), 2.5);
  // EXPECT_EQ(comps5.N2(), 1.5);

  // EXPECT_EQ(comps6.N1(), 1.5);
  // EXPECT_EQ(comps6.N2(), 1.0);
}