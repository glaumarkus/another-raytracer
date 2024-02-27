#pragma once

#include "math/material.hpp"
#include "math/object.hpp"
#include "raytrace/camera.hpp"
#include "raytrace/light.hpp"
#include "math/intersections.hpp"
#include "raytrace/lighting_model.hpp"
#include <memory>
#include <string>
#include <vector>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>
#include <expected>

template <typename T> struct ParsedContent {
  T t;
  std::string tag;
};

class World {
public:
  World() = default;

  const std::vector<std::shared_ptr<Light>> &GetLights() const;
  const std::vector<std::shared_ptr<Object>> &GetObjects() const;
  // needs to be pointer as its abstract type
  void Add(std::shared_ptr<Light> light);
  void Add(std::shared_ptr<Object> object);
  Intersections Intersect(Ray r) const;
  Color ShadeHit(const PrepareComputations& comps, LightingModel* model) const;

protected:
  std::vector<std::shared_ptr<Light>> lights_;
  std::vector<std::shared_ptr<Object>> objects_;
};

enum class Error {
  kFileNotExisting,
  kConversionError,
  kNotFoundError,
};


class WorldParser {
public:
  WorldParser() = default;
  std::unique_ptr<World> ParseWorldFile(std::string yaml_file);

protected:
  void Add(const YAML::Node &node);
  void DefineMaterial(const YAML::Node &node);
  void DefineTransformation(const YAML::Node &node);

  std::expected<double, Error> ParseDouble(const YAML::Node &it, std::string tag);
  std::expected<Vector, Error> ParseVector(const YAML::Node &it, std::string tag);
  std::expected<Point, Error> ParsePoint(const YAML::Node &it, std::string tag);
  std::expected<Color, Error> ParseColor(const YAML::Node &it, std::string tag);
  std::expected<std::string, Error> ParseString(const YAML::Node &it, std::string tag);

  Material GetMaterial(const std::string &tag) const;
  Matrix<4> GetTransform(const std::string &tag) const;

protected:
  std::unique_ptr<World> world_{nullptr};
  std::vector<ParsedContent<Material>> materials_;
  std::vector<ParsedContent<Matrix<4>>> transforms_;
};

