#include "world_parser.hpp"
#include "math/mat.hpp"

Material WorldParser::GetMaterial(const std::string &tag) const {
  Material mat;
  for (const auto &material : materials_) {
    if (tag == material.tag) {
      mat = material.t;
    }
  }
  return mat;
}

Matrix<4> WorldParser::GetTransform(const std::string &tag) const {
  Matrix<4> result;
  for (const auto &transform : transforms_) {
    if (tag == transform.tag) {
      result = transform.t;
    }
  }
  return result;
}

std::unique_ptr<World> WorldParser::ParseWorldFile(std::string yaml_file) {
  world_ = std::make_unique<World>();
  YAML::Node content = YAML::LoadFile(yaml_file);
  for (const auto &item : content) {
    if (item["add"]) {
      Add(item);
    } else if (item["material"]) {
      DefineMaterial(item);
    } else if (item["transform"]) {
      DefineTransformation(item);
    }
  }
  return std::move(world_);
}

void WorldParser::Add(const YAML::Node &node) {
  std::string type = node["add"].as<std::string>();
  if (type == "Pointcamera") {
    // create camera
    auto height_result = ParseDouble(node, "height");
    auto width_result = ParseDouble(node, "width");
    auto fov_result = ParseDouble(node, "fov");
    auto from_result = ParsePoint(node, "from");
    auto to_result = ParsePoint(node, "to");
    auto up_result = ParseVector(node, "up");

    if (height_result && width_result && fov_result) {
      // set camera
      auto camera = std::make_shared<Camera>(
          width_result.value(), height_result.value(), fov_result.value());

      // parse transformation
      auto transformation = math_constants::m4_identity;

      if (from_result && to_result && up_result) {
        transformation = CalculateTransform(
            from_result.value(), to_result.value(), up_result.value());
      }
      camera->SetTransform(transformation);
      world_->Add(camera);
    }
  } else if (type == "Pointlight") {
    auto position = Point();
    auto position_result = ParsePoint(node, "at");
    if (position_result)
      position = position_result.value();
    auto intensity = Color(1);
    auto intensity_result = ParseColor(node, "intensity");
    if (intensity_result)
      intensity = intensity_result.value();

    auto light = std::make_shared<PointLight>(position, intensity);
    world_->Add(std::shared_ptr<Light>(std::move(light)));
  } else if (type == "sphere") {

    auto material = Material();
    auto material_result = ParseString(node, "material");
    if (material_result)
      material = GetMaterial(material_result.value());

    auto transformation = math_constants::m4_identity;
    auto transformation_result = ParseString(node, "transform");
    if (transformation_result)
      transformation = GetTransform(transformation_result.value());

    auto sphere = std::make_shared<Sphere>(transformation, material);
    world_->Add(std::shared_ptr<Object>(std::move(sphere)));
  } else if (type == "plane") {

    auto material = Material();
    auto material_result = ParseString(node, "material");
    if (material_result)
      material = GetMaterial(material_result.value());

    auto transformation = math_constants::m4_identity;
    auto transformation_result = ParseString(node, "transform");
    if (transformation_result)
      transformation = GetTransform(transformation_result.value());

    auto plane = std::make_shared<Plane>(transformation, material);
    world_->Add(std::shared_ptr<Object>(std::move(plane)));
  }
}

void WorldParser::DefineMaterial(const YAML::Node &node) {
  std::string name = node["material"].as<std::string>();
  Material material;
  auto value = node["value"];
  auto color = ParseColor(value, "color");
  auto diffuse = ParseDouble(value, "diffuse");
  auto ambient = ParseDouble(value, "ambient");
  auto specular = ParseDouble(value, "specular");
  auto reflective = ParseDouble(value, "reflective");
  auto refractive_idx = ParseDouble(value, "refractive");
  auto transparent = ParseDouble(value, "transparent");

  if (color) {
    material.SetColor(color.value());
  }

  if (diffuse) {
    material.SetDiffuse(diffuse.value());
  }

  if (ambient) {
    material.SetAmbient(ambient.value());
  }

  if (specular) {
    material.SetSpecular(specular.value());
  }

  if (reflective) {
    material.SetReflective(reflective.value());
  }

  if (refractive_idx) {
    material.SetRefractiveIdx(refractive_idx.value());
  }

  if (transparent) {
    material.SetTransparent(transparent.value());
  }

  materials_.emplace_back(ParsedContent<Material>{
      .t = material,
      .tag = name,
  });
}
void WorldParser::DefineTransformation(const YAML::Node &node) {
  std::string name = node["transform"].as<std::string>();
  auto transformation_matrix = math_constants::m4_identity;
  auto value = node["value"];
  // parse value
  for (const auto &transformation : value) {
    auto transform_type = transformation[0].as<std::string>();
    if (transform_type == "translate") {
      double x = transformation[1].as<double>();
      double y = transformation[2].as<double>();
      double z = transformation[3].as<double>();
      transformation_matrix *= math_constants::TranslationMatrix(x, y, z);
    } else if (transform_type == "scale") {
      double x = transformation[1].as<double>();
      double y = transformation[2].as<double>();
      double z = transformation[3].as<double>();
      transformation_matrix *= math_constants::ScaleMatrix(x, y, z);
    } else if (transform_type == "rotatex") {
      double degrees = transformation[1].as<double>();
      transformation_matrix *=
          math_constants::RotationMatrixX(math_constants::Radians(degrees));
    } else if (transform_type == "rotatey") {
      double degrees = transformation[1].as<double>();
      transformation_matrix *=
          math_constants::RotationMatrixY(math_constants::Radians(degrees));
    } else if (transform_type == "rotatez") {
      double degrees = transformation[1].as<double>();
      transformation_matrix *=
          math_constants::RotationMatrixZ(math_constants::Radians(degrees));
    } else if (transform_type == "shear") {
      double xy = transformation[1].as<double>();
      double xz = transformation[2].as<double>();
      double yx = transformation[3].as<double>();
      double yz = transformation[4].as<double>();
      double zx = transformation[5].as<double>();
      double zy = transformation[6].as<double>();
      transformation_matrix *=
          math_constants::ShearMatrix(xy, xz, yx, yz, zx, zy);
    }
  }
  transforms_.emplace_back(ParsedContent<Matrix<4>>{
      .t = transformation_matrix,
      .tag = name,
  });
}

std::expected<double, Error> WorldParser::ParseDouble(const YAML::Node &it,
                                                      std::string tag) {
  if (it[tag] && it[tag].IsDefined() && it[tag].IsScalar())
    return it[tag].as<double>();
  return std::unexpected(Error::kConversionError);
}
std::expected<Vector, Error> WorldParser::ParseVector(const YAML::Node &it,
                                                      std::string tag) {
  if (it[tag] && it[tag].IsDefined() && it[tag].IsSequence()) {
    auto v = it[tag].as<std::vector<double>>();
    return Vector(v[0], v[1], v[2]);
  }
  return std::unexpected(Error::kConversionError);
}
std::expected<Point, Error> WorldParser::ParsePoint(const YAML::Node &it,
                                                    std::string tag) {
  if (it[tag] && it[tag].IsDefined() && it[tag].IsSequence()) {
    auto v = it[tag].as<std::vector<double>>();
    return Point(v[0], v[1], v[2]);
  }
  return std::unexpected(Error::kConversionError);
}
std::expected<Color, Error> WorldParser::ParseColor(const YAML::Node &it,
                                                    std::string tag) {
  if (it[tag] && it[tag].IsDefined() && it[tag].IsSequence()) {
    auto v = it[tag].as<std::vector<double>>();
    return Color(v[0], v[1], v[2]);
  }
  return std::unexpected(Error::kConversionError);
}

std::expected<std::string, Error> WorldParser::ParseString(const YAML::Node &it,
                                                           std::string tag) {
  if (it[tag] && it[tag].IsDefined()) {
    return it[tag].as<std::string>();
  }
  return std::unexpected(Error::kConversionError);
}