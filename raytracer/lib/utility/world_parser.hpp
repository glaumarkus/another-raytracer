#pragma once

#include "math/intersections.hpp"
#include "math/material.hpp"
#include "primitives/object.hpp"
#include "raytrace/camera.hpp"
#include "raytrace/light.hpp"
#include "raytrace/lighting_model.hpp"
#include "raytrace/world.hpp"
#include <expected>
#include <memory>
#include <string>
#include <vector>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

template <typename T> struct ParsedContent {
  T t;
  std::string tag;
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

  std::expected<double, Error> ParseDouble(const YAML::Node &it,
                                           std::string tag);
  std::expected<Vector, Error> ParseVector(const YAML::Node &it,
                                           std::string tag);
  std::expected<Point, Error> ParsePoint(const YAML::Node &it, std::string tag);
  std::expected<Color, Error> ParseColor(const YAML::Node &it, std::string tag);
  std::expected<std::string, Error> ParseString(const YAML::Node &it,
                                                std::string tag);

  Material GetMaterial(const std::string &tag) const;
  Matrix<4> GetTransform(const std::string &tag) const;

protected:
  std::unique_ptr<World> world_{nullptr};
  std::vector<ParsedContent<Material>> materials_;
  std::vector<ParsedContent<Matrix<4>>> transforms_;
};
