#include "imgui_wrapper.hpp"
#include "image_data.hpp"
#include "raytrace/raytrace.hpp"

UI *UI::instance_ = nullptr;

void UI::UpdateButtonCallback() {
  bool has_changed = false;
  if (params_.height != last_params_.height) {
    last_params_.height = params_.height;
    logger_.LogVerbose("Update height: " + std::to_string(params_.height));
    has_changed = true;
  }
  if (params_.width != last_params_.width) {
    last_params_.width = params_.width;
    logger_.LogVerbose("Update width: " + std::to_string(params_.width));
    has_changed = true;
  }

  if (has_changed) {
    ApplyChanges();
  }
}

void UI::ApplyChanges() {
  // reinit the image data
  ImageData::getInstance().Initialize(last_params_.height, last_params_.width);
}

void UI::RenderUI() {

  ImGui::Begin(kWindowName);

  float totalWidth = ImGui::GetContentRegionAvail().x;
  float mainCanvasWidth = (totalWidth / 4) * 3;
  float sidebarWidth = totalWidth / 4;
  float sidebarHeight = ImGui::GetContentRegionAvail().y;
  float commandOutputHeight = sidebarHeight * 0.25f;

  // Main Canvas
  ImGui::BeginChild(kRenderFrame, ImVec2(mainCanvasWidth, 0), true);
  ImGui::Text("Image:");
  // Calculate the size for the main canvas based on the window's content region
  ImVec2 imageSize(static_cast<float>(ImageData::getInstance().getWidth()),
                   static_cast<float>(ImageData::getInstance().getHeight()));

  // Display the texture on the main canvas
  ImGui::Image((void *)(intptr_t)ImageData::getInstance().LoadTexture(),
               imageSize);

  // image here
  ImGui::EndChild();

  ImGui::SameLine(); // Ensure the sidebar is right next to the main canvas

  // Sidebar
  ImGui::BeginChild(kOptionFrame, ImVec2(sidebarWidth, 0), true);
  ImGui::Text(kOptionFrame);
  ImGui::InputInt("Height", &params_.height);
  ImGui::InputInt("Width", &params_.width);

  if (ImGui::Button("Update Settings")) {
    UpdateButtonCallback();
  }

  if (ImGui::Button("Render")) {
    Timer t;
    Raytrace();
    logger_.LogDebug("Generation:" + t.Measure());
    ImageData::getInstance().Update();
  }

  ImGui::Dummy(ImVec2(0.0f, 100));

  // Now, create the child window for the command output
  ImGui::BeginChild("CommandOutputArea", ImVec2(0, commandOutputHeight), true);

  ImGui::TextUnformatted(logger_.GetLog().c_str());
  if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
    ImGui::SetScrollHereY(1.0f); // Auto-scroll to the bottom
  }

  ImGui::EndChild(); // End of command output area
  ImGui::EndChild();

  ImGui::End();
}

void UI::Close() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window_);
  glfwTerminate();
}

void UI::ErrorCallbackWrapper(int error, const char *description) {
  if (instance_) {
    instance_->internal_glfw_error_callback(error, description);
  }
}

UI::UI() {
  if (!instance_) {
    instance_ = this;
  }
  glfwSetErrorCallback(ErrorCallbackWrapper);
}

bool UI::Render() {
  if (!glfwWindowShouldClose(window_)) {
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    RenderUI(); // Render our GUI

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window_, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window_);
    return true;
  }
  return false;
}

bool UI::Init() {
  if (!glfwInit())
    return false;
  window_ = glfwCreateWindow(1280, 720, "Raytracer", NULL, NULL);
  if (window_ == NULL)
    return false;
  glfwMakeContextCurrent(window_);
  glfwSwapInterval(1);

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window_, true);
  ImGui_ImplOpenGL3_Init(kGlslVersion);

  params_.width = 400;
  params_.height = 400;
  last_params_.width = 400;
  last_params_.height = 400;
  ImageData::getInstance().Initialize(last_params_.height, last_params_.width);

  return true;
}

void UI::internal_glfw_error_callback(int error, const char *description) {
  std::string error_msg{"GLFW error: "};
  error_msg += description;
  logger_.LogError(error_msg);
}