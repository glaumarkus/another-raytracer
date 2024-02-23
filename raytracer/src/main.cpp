#include "imgui/image_buffer.hpp"
#include "imgui/imgui_wrapper.hpp"

int main() {
  UI ui;
  if (ui.Init()) {
    for (int y = 0; y < ImageData::getInstance().getHeight(); ++y) {
      for (int x = 0; x < ImageData::getInstance().getWidth(); ++x) {
        ImageData::getInstance().SetPixel(x, y, 255, 255, 255, 255);
      }
    }

    while (ui.Render()) {
    }
  }
  return 0;
}