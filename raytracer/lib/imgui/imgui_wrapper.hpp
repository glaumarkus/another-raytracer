#pragma once

#include "backends/imgui_impl_opengl3.h"
#include "config.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "utility/logger.hpp"
#include <GLFW/glfw3.h>

constexpr const char *kGlslVersion = "#version 130";
constexpr const char *kWindowName = "Raytracer";
constexpr const char *kRenderFrame = "Output";
constexpr const char *kOptionFrame = "Options";

constexpr int kHeight = 720;
constexpr int kWidth = 1280;

class UI {
public:
  UI();
  ~UI() = default;
  bool Init();
  void Close();
  bool Render();
  void RenderUI();

private:
  static void ErrorCallbackWrapper(int error, const char *description);
  void internal_glfw_error_callback(int error, const char *description);
  void UpdateButtonCallback();
  void ApplyChanges();

private:
  static UI *instance_;
  Logger logger_;
  GLFWwindow *window_{nullptr};
  UiParameters last_params_;
  UiParameters params_;
};
