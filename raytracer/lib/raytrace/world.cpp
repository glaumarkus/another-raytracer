#include "world.hpp"
#include "imgui/image_data.hpp"
#include "math/constants.hpp"
#include "primitives/object.hpp"

void World::Render(LightingModel *model) const {
  for (int h = 0; h < ImageData::getInstance().getHeight(); h++) {
    for (int w = 0; w < ImageData::getInstance().getWidth(); w++) {
      auto ray = camera_->RayForPixel(w, h);
      auto color = ColorAt(ray, model);
      ImageData::getInstance().SetPixel(h, w, color.ru(), color.gu(),
                                        color.bu(), 255);
    }
  }
}

void World::SetReflectionIterations(int iterations) {
  iterations_ = iterations;
}

Color World::ReflectedColor(const PrepareComputations &comps,
                            LightingModel *model, int iterations) const {
  if (!model->CalculateReflection()) {
    return Color(0);
  }
  if (iterations == iterations_) {
    return Color(0);
  }
  if (equal(comps.GetObject()->GetMaterial().Reflective(), 0.0)) {
    return Color(0);
  }
  Ray reflect_ray(comps.GetOverPoint(), comps.GetReflect());
  auto color = ColorAt(reflect_ray, model, iterations + 1);
  return color * comps.GetObject()->GetMaterial().Reflective();
}

Intersections World::Intersect(Ray r) const {
  Intersections world_intersections;
  for (const auto &obj : objects_) {
    if (obj->IsIntersectable()) {
      world_intersections.Add(obj->GetIntersections(r).Get());
    }
  }
  world_intersections.Sort();
  return world_intersections;
}

void World::Add(std::shared_ptr<Camera> camera) { camera_ = camera; }

void World::Add(std::shared_ptr<Light> light) {
  lights_.emplace_back(std::move(light));
}
void World::Add(std::shared_ptr<Object> object) {
  objects_.emplace_back(std::move(object));
}

const std::shared_ptr<Camera> &World::GetCamera() const { return camera_; }

const std::vector<std::shared_ptr<Light>> &World::GetLights() const {
  return lights_;
}

const std::vector<std::shared_ptr<Object>> &World::GetObjects() const {
  return objects_;
}

std::shared_ptr<Camera> &World::GetCamera() { return camera_; }

std::vector<std::shared_ptr<Light>> &World::GetLights() { return lights_; }

std::vector<std::shared_ptr<Object>> &World::GetObjects() { return objects_; }

double World::IsShadow(Point p) const {
  double shadow = 0.0;
  for (const auto &light : lights_) {
    auto v = light->GetPoint() - p;
    auto distance = v.Magnitude();
    auto direction = v.Normalized();
    auto ray = Ray(p, direction);
    auto intersections = Intersect(ray);
    if (intersections.Hit() && intersections.Hit().value().t < distance) {
      shadow += 1.0;
    }
  }
  return shadow / lights_.size();
}

Color World::ShadeHit(const PrepareComputations &comps, LightingModel *model,
                      int iterations) const {
  double in_shadow = 0.0;
  if (model->CalculateShadow()) {
    in_shadow = IsShadow(comps.GetOverPoint());
  }
  // convert light ptr
  auto surface_color = model->GetLightingColor(
      comps.GetObject()->GetMaterial(), lights_, comps.GetPoint(),
      comps.GetEye(), comps.GetNormal(), in_shadow);
  auto reflected_color = ReflectedColor(comps, model, iterations);

  return surface_color + reflected_color;
}

Color World::ColorAt(Ray r, LightingModel *model, int iterations) const {
  auto intersections = Intersect(r);
  auto hit_result = intersections.Hit();
  if (hit_result) {
    auto comps = PrepareComputations(intersections, r);
    return ShadeHit(comps, model, iterations);
  }
  return Color(0);
}

int World::GetReflectionIterations() const { return iterations_; }