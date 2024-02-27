#include "lighting_model.hpp"
#include "imgui/color.hpp"

Color PhongReflectionModel::GetLightingColor(
    const Material &material, const std::vector<std::shared_ptr<Light>>& lights,
    const Point &point, const Vector &eye_vector,
    const Vector &normal_vector) const {
  Color result(0, 0, 0);
  for (const auto light : lights) {
    Color diffuse_color = Colors::black;
    Color specular_color = Colors::black;
    auto effective_color = material.GetColor() * light->GetIntensity();
    auto light_vector = (light->GetPoint() - point).Normalized();
    auto ambient_color = effective_color * material.Ambient();
    auto light_dot_normal = light_vector.Dot(normal_vector);
    if (light_dot_normal >= 0) {
      diffuse_color = effective_color * material.Diffuse() * light_dot_normal;
      auto reflectv = (light_vector * -1).Reflect(normal_vector);
      auto reflect_dot_eye = reflectv.Dot(eye_vector);
      if (reflect_dot_eye > 0) {
        auto factor = std::pow(reflect_dot_eye, material.Shininess());
        specular_color = light->GetIntensity() * material.Specular() * factor;
      }
    }
    result += ambient_color + diffuse_color + specular_color;
  }
  result *= 1.0 / lights.size();
  return result;
}