#include "raytrace.hpp"

#include "imgui/color.hpp"
#include "imgui/image_buffer.hpp"
#include "math/material.hpp"
#include "math/object.hpp"
#include "raytrace/light.hpp"
#include "raytrace/lighting_model.hpp"

void Raytrace() {

  PhongReflectionModel phong;

  auto h = ImageData::getInstance().getHeight();
  auto w = ImageData::getInstance().getWidth();
  auto c = Color(1, 0, 0);
  auto b = Color(1, 1, 1);

  Sphere s;
  s.Transform(math_constants::ScaleMatrix(40, 40, 40));
  s.SetMaterial(Material(Color(1, 0.2, 1), 0.1, 0.9, 0.9, 200));

  auto light =
      std::make_shared<PointLight>(Point(-100, -100, -100), Color(1, 1, 1));
  auto lights = std::vector<std::shared_ptr<Light>>();
  lights.push_back(light);

  auto wall_z = 10;
  auto wall_size = 7.0;
  auto half = h / 2;

  auto origin = Point(0, 0, -50);
  for (int hh = 0; hh < h; hh++) {
    auto world_y = -half + hh;
    for (int ww = 0; ww < w; ww++) {
      auto world_x = -half + ww;
      auto position = Point(world_x, world_y, wall_z);
      Ray r(origin, (position - origin).Normalized());
      auto intersections = s.GetIntersections(r);
      if (!intersections.Empty()) {
        const auto &hit = intersections.Get()[0];
        auto point = r.Position(hit.t);
        auto normal =
            SphereNormal(reinterpret_cast<const Sphere &>(*hit.obj), point);
        auto color = phong.GetLightingColor(hit.obj->GetMaterial(), lights,
                                            point, r.GetDirection(), normal);

        ImageData::getInstance().SetPixel(hh, ww, color.ru(), color.gu(),
                                          color.bu(), 255);
      } else {
        ImageData::getInstance().SetPixel(hh, ww, 0, 0, 0, 255);
      }
    }
  }
}