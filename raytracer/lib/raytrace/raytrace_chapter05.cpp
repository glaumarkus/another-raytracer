#include "raytrace.hpp"


#include "imgui/color.hpp"
#include "imgui/image_data.hpp"
#include "primitives/object.hpp"

void Raytrace() {
  auto h = ImageData::getInstance().getHeight();
  auto w = ImageData::getInstance().getWidth();
  auto c = Color(1, 0, 0);
  auto b = Color(1, 1, 1);

  Sphere s;
  s.Transform(math_constants::ScaleMatrix(2, 2, 2));
  auto wall_z = 10;
  auto wall_size = 7.0;
  auto half = h / 2;

  auto origin = Point(0, 0, -5);
  for (int hh = 0; hh < h; hh++) {
    auto world_y = -half + hh;
    for (int ww = 0; ww < w; ww++) {
      auto world_x = -half + ww;
      auto position = Point(world_x, world_y, wall_z);
      Ray r(origin, (position - origin).Normalized());
      auto intersections = s.GetIntersections(r);
      if (!intersections.Empty()) {
        ImageData::getInstance().SetPixel(hh, ww, 255, 0, 0, 255);
      } else {
        ImageData::getInstance().SetPixel(hh, ww, 255, 255, 255, 255);
      }
    }
  }
}