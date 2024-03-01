#include "imgui/image_data.hpp"
#include "math/constants.hpp"
#include "math/intersections.hpp"
#include "raytrace/camera.hpp"
#include "utility/logger.hpp"
#include "utility/world_parser.hpp"
#include <gtest/gtest.h>
#include <iostream>

auto equalc = [](Color lhs, Color rhs) {
  bool result = false;
  if (std::abs(lhs.r() - rhs.r()) < kEpsilon &&
      std::abs(lhs.g() - rhs.g()) < kEpsilon &&
      std::abs(lhs.b() - rhs.b()) < kEpsilon) {
    result = true;
  }
  return result;
};

TEST(chapter07, load_world_file) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  EXPECT_NE(world, nullptr);
  EXPECT_EQ(world->GetLights().size(), 1);
  EXPECT_EQ(world->GetObjects().size(), 2);
  EXPECT_TRUE(equalc(world->GetObjects()[0]->GetMaterial().GetColor(),
                     Color(0.8, 1.0, 0.6)));
  EXPECT_EQ(world->GetObjects()[0]->GetMaterial().Ambient(), 0.1);
  EXPECT_EQ(world->GetObjects()[0]->GetMaterial().Diffuse(), 0.7);
  EXPECT_EQ(world->GetObjects()[0]->GetMaterial().Specular(), 0.2);
  EXPECT_EQ(world->GetObjects()[0]->GetMaterial().Shininess(), 200.0);
  EXPECT_TRUE(
      equalc(world->GetObjects()[1]->GetMaterial().GetColor(), Color(1.0)));
  EXPECT_EQ(world->GetObjects()[1]->GetMaterial().Ambient(), 0.1);
  EXPECT_EQ(world->GetObjects()[1]->GetMaterial().Diffuse(), 0.9);
  EXPECT_EQ(world->GetObjects()[1]->GetMaterial().Specular(), 0.9);
  EXPECT_EQ(world->GetObjects()[1]->GetMaterial().Shininess(), 200.0);
}

TEST(chapter07, intersect_world) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  auto intersections = world->Intersect(r);
  EXPECT_EQ(intersections.Get().size(), 4);
  EXPECT_EQ(intersections.Get()[0].t, 4.0);
  EXPECT_EQ(intersections.Get()[1].t, 4.5);
  EXPECT_EQ(intersections.Get()[2].t, 5.5);
  EXPECT_EQ(intersections.Get()[3].t, 6);
}

TEST(chapter07, prepare_computations) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  auto intersections = s.GetIntersections(r);
  auto hit = intersections.Hit();
  if (!hit)
    FAIL();
  PrepareComputations p(intersections, r);
  EXPECT_EQ(p.GetObject(), &s);
  EXPECT_EQ(p.GetPoint(), Point(0, 0, -1));
  EXPECT_FALSE(p.IsInside());
  EXPECT_EQ(p.GetNormal(), Vector(0, 0, -1));
  EXPECT_EQ(p.GetEye(), Vector(0, 0, -1));
}

TEST(chapter07, prepare_computations_inside) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  Sphere s;
  auto intersections = s.GetIntersections(r);
  auto hit = intersections.Hit();
  if (!hit)
    FAIL();
  PrepareComputations p(intersections, r);
  EXPECT_EQ(p.GetObject(), &s);
  EXPECT_TRUE(equalv(p.GetPoint(), Point(0, 0, 1)));
  EXPECT_TRUE(p.IsInside());
  EXPECT_TRUE(equalv(p.GetNormal(), Vector(0, 0, -1)));
  EXPECT_TRUE(equalv(p.GetEye(), Vector(0, 0, -1)));
}

TEST(chapter07, shade_hit_1) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
  Intersections i;
  i.Add(4, world->GetObjects()[0].get());
  PhongReflectionModel model;
  auto comps = PrepareComputations(i, r);
  auto color = world->ShadeHit(comps, &model);
  EXPECT_TRUE(equalc(color, Color(0.38066, 0.47583, 0.2855)));
}

TEST(chapter07, shade_hit_2) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07_2.yaml");
  auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
  Intersections i;
  i.Add(0.5, world->GetObjects()[1].get());
  PhongReflectionModel model;
  auto comps = PrepareComputations(i, r);
  auto color = world->ShadeHit(comps, &model);
  EXPECT_TRUE(equalc(color, Color(0.90498)));
}

TEST(chapter07, color_at_1) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  Ray r(Point(0, 0, -5), Vector(0, 1, 0));
  PhongReflectionModel model;
  auto color = world->ColorAt(r, &model);
  EXPECT_TRUE(equalc(color, Color(0.0)));
}

TEST(chapter07, color_at_2) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07.yaml");
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  PhongReflectionModel model;
  auto color = world->ColorAt(r, &model);
  EXPECT_TRUE(equalc(color, Color(0.38066, 0.47583, 0.2855)));
}

TEST(chapter07, color_at_3) {
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07_3.yaml");
  Ray r(Point(0, 0, 0.75), Vector(0, 0, -1));
  PhongReflectionModel model;
  auto color = world->ColorAt(r, &model);
  EXPECT_TRUE(equalc(color, Color(1)));
}

TEST(chapter07, camera_instance_1) {
  auto transform =
      CalculateTransform(Point(0, 0, 0), Point(0, 0, -1), Vector(0, 1, 0));
  EXPECT_EQ(transform.Eigen(), math_constants::m4_identity.Eigen());
}
TEST(chapter07, camera_instance_2) {
  auto transform =
      CalculateTransform(Point(0, 0, 0), Point(0, 0, 1), Vector(0, 1, 0));
  EXPECT_EQ(transform.Eigen(), math_constants::ScaleMatrix(-1, 1, -1).Eigen());
}
TEST(chapter07, camera_instance_3) {
  auto transform =
      CalculateTransform(Point(0, 0, 8), Point(0, 0, 0), Vector(0, 1, 0));
  EXPECT_EQ(transform.Eigen(),
            math_constants::TranslationMatrix(0, 0, -8).Eigen());
}

TEST(chapter07, camera_ray_1) {
  Camera c(201, 101, M_PI_2);
  auto ray = c.RayForPixel(100, 50);
  EXPECT_TRUE(equalv(ray.GetOrigin(), Point(0, 0, 0)));
  EXPECT_TRUE(equalv(ray.GetDirection(), Point(0, 0, -1)));
}

TEST(chapter07, camera_ray_2) {
  Camera c(201, 101, M_PI_2);
  auto ray = c.RayForPixel(100, 50);
  EXPECT_TRUE(equalv(ray.GetOrigin(), Point(0, 0, 0)));
  EXPECT_TRUE(equalv(ray.GetDirection(), Point(0, 0, -1)));
}

TEST(chapter07, camera_ray_3) {
  Camera c(201, 101, M_PI_2);
  auto ray = c.RayForPixel(100, 50);
  EXPECT_TRUE(equalv(ray.GetOrigin(), Point(0, 0, 0)));
  EXPECT_TRUE(equalv(ray.GetDirection(), Point(0, 0, -1)));
}

TEST(chapter07, render_world) {
  ImageData::getInstance().Initialize(11, 11);
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07_4.yaml");
  PhongReflectionModel model;
  world->Render(&model);
  Color expected(0.38066, 0.47583, 0.2855);
  auto pixels = ImageData::getInstance().GetPixel(5, 5);
  EXPECT_EQ(pixels[0], expected.ru());
}

// just to see how long it takes
TEST(chapter07, render_world2) {
  ImageData::getInstance().Initialize(800, 600);
  WorldParser parser;
  auto world = parser.ParseWorldFile("chapter07_5.yaml");
  PhongReflectionModel model;
  world->Render(&model);
}