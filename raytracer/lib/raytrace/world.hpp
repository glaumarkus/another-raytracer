#pragma once

#include "camera.hpp"
#include "light.hpp"
#include "math/intersections.hpp"
#include "math/prepare_computations.hpp"
#include "raytrace/lighting_model.hpp"
#include <memory>
#include <vector>

class World {
public:
  World() = default;

  const std::shared_ptr<Camera> &GetCamera() const;
  const std::vector<std::shared_ptr<Light>> &GetLights() const;
  const std::vector<std::shared_ptr<Object>> &GetObjects() const;
  std::shared_ptr<Camera> &GetCamera();
  std::vector<std::shared_ptr<Light>> &GetLights();
  std::vector<std::shared_ptr<Object>> &GetObjects();
  // needs to be pointer as its abstract type
  void Add(std::shared_ptr<Camera> camera);
  void Add(std::shared_ptr<Light> light);
  void Add(std::shared_ptr<Object> object);
  Intersections Intersect(Ray r) const;
  Color ShadeHit(const PrepareComputations &comps, LightingModel *model,
                 int iteration = 0) const;
  Color ReflectedColor(const PrepareComputations &comps, LightingModel *model,
                       int iteration = 0) const;
  double IsShadow(Point p) const;
  Color ColorAt(Ray r, LightingModel *model, int iteration = 0) const;
  void Render(LightingModel *model) const;
  void SetReflectionIterations(int iterations);
  int GetReflectionIterations() const;

protected:
  std::shared_ptr<Camera> camera_;
  std::vector<std::shared_ptr<Light>> lights_;
  std::vector<std::shared_ptr<Object>> objects_;
  int iterations_{0};
};