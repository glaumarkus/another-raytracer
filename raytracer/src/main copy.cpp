#include "imgui/imgui_wrapper.hpp"

int main() {
  UI ui;
  if (ui.Init()) {
    while (ui.Render()) {
    }
  }
  return 0;
}