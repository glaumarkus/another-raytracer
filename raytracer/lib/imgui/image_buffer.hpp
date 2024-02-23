#pragma once

#include <mutex>
#include <vector>
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

class ImageData {
public:
  // Delete copy constructor and assignment operator to prevent copying
  ImageData(const ImageData &) = delete;
  ImageData &operator=(const ImageData &) = delete;

  // Static method to get the instance of the class
  static ImageData &getInstance();

  void SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b,
                unsigned char a);


  void Initialize(int w, int h);

  void Update();
    

  int getWidth() const;
  int getHeight() const;

  GLuint LoadTexture();

private:
  int width = 0;
  int height = 0;
  std::vector<unsigned char> pixels;
  std::vector<unsigned char> pixels_copy;
  std::mutex mutexp;
  std::mutex mutexp2;
  ImageData() = default;
};
