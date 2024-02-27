#include "image_buffer.hpp"

GLuint ImageData::LoadTexture() {
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, pixels_copy.data());
  return textureID;
}

std::vector<unsigned char> ImageData::GetPixel(int h, int w) const
{
  std::vector<unsigned char> pixel;
  std::lock_guard<std::mutex> lock(mutexp);
  int index = (w * width + h) * 4;
  pixel.push_back(pixels[index]);
  pixel.push_back(pixels[index + 1]);
  pixel.push_back(pixels[index + 2]);
  return pixel;
}

ImageData &ImageData::getInstance() {
  static ImageData instance;
  return instance;
}

void ImageData::SetPixel(int x, int y, unsigned char r, unsigned char g,
                         unsigned char b, unsigned char a) {
  std::lock_guard<std::mutex> lock(mutexp);
  if (x < 0 || y < 0 || x >= width || y >= height)
    return;
  int index = (y * width + x) * 4;
  pixels[index] = r;
  pixels[index + 1] = g;
  pixels[index + 2] = b;
  pixels[index + 3] = a;
}

void ImageData::Update() {
  std::lock_guard<std::mutex> lock(mutexp);
  std::lock_guard<std::mutex> lock2(mutexp2);
  pixels_copy = pixels;
}

void ImageData::Initialize(int w, int h) {
  std::lock_guard<std::mutex> lock(mutexp);
  std::lock_guard<std::mutex> lock2(mutexp2);
  width = w;
  height = h;
  pixels.clear();
  pixels.resize(width * height * 4);
  pixels_copy.clear();
  pixels_copy.resize(pixels.size());
}

int ImageData::getWidth() const { return width; }
int ImageData::getHeight() const { return height; }
