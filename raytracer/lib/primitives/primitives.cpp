#include "primitives.hpp"

Sphere GlassSphere() {
  Sphere s;
  Material m;
  m.SetRefractiveIdx(1.5);
  m.SetTransparent(1.0);
  s.SetMaterial(m);
  return s;
}