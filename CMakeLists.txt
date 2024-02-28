cmake_minimum_required(VERSION 3.15.0)
project(raytracer VERSION 0.1.0 LANGUAGES C CXX)

# set(CUDA_SUPPORT OFF
#         CACHE BOOL "ON to build with CUDA, OFF to do standard")

set(CMAKE_CXX_STANDARD "23")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")

include(CTest)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

# add EIGEN
add_library(eigen INTERFACE)
target_include_directories(eigen INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/external/eigen-3.4.0)

# add GTest
add_subdirectory(external/googletest-release-1.11.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# add imgui
find_package(glfw3 REQUIRED)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

file(GLOB IMGUI_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui-1.90.3/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui-1.90.3/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui-1.90.3/backends/imgui_impl_glfw.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui-1.90.3
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui-1.90.3/backends  
)

target_include_directories(imgui PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(imgui PRIVATE ${GLFW_LIBRARIES})


# add subdirectories
add_subdirectory(raytracer/lib)
add_subdirectory(raytracer/src)
add_subdirectory(raytracer/unit_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# copy scene files
configure_file(scenes/parsing_example.yaml ${CMAKE_CURRENT_BINARY_DIR}/raytracer/unit_test/parsing_example.yaml COPYONLY)
configure_file(scenes/chapter07.yaml ${CMAKE_CURRENT_BINARY_DIR}/raytracer/unit_test/chapter07.yaml COPYONLY)
configure_file(scenes/chapter07_2.yaml ${CMAKE_CURRENT_BINARY_DIR}/raytracer/unit_test/chapter07_2.yaml COPYONLY)
configure_file(scenes/chapter07_3.yaml ${CMAKE_CURRENT_BINARY_DIR}/raytracer/unit_test/chapter07_3.yaml COPYONLY)
configure_file(scenes/chapter07_4.yaml ${CMAKE_CURRENT_BINARY_DIR}/raytracer/unit_test/chapter07_4.yaml COPYONLY)
configure_file(scenes/chapter07_5.yaml ${CMAKE_CURRENT_BINARY_DIR}/raytracer/unit_test/chapter07_5.yaml COPYONLY)
configure_file(scenes/chapter08.yaml ${CMAKE_CURRENT_BINARY_DIR}/raytracer/unit_test/chapter08.yaml COPYONLY)