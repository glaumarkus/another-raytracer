# math
add_library(raytracer_lib STATIC 
    math/vector2d.cpp
    math/mat.cpp
    math/ray.cpp
    math/object.cpp
    math/intersections.cpp
    math/material.cpp
    )
target_link_libraries(raytracer_lib PRIVATE eigen)
target_include_directories(raytracer_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# utility
add_library(utility STATIC
    utility/logger.cpp
    utility/timer.cpp
)
target_include_directories(utility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# image buffer
add_library(image_buffer STATIC 
    imgui/image_buffer.cpp
    imgui/color.cpp
)

target_include_directories(image_buffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(image_buffer PUBLIC 
    imgui
    glfw
    ${OPENGL_LIBRARIES} 
    dl
)

# raytrace chapter 05
add_library(raytrace05 STATIC 
    raytrace/raytrace_chapter05.cpp
)

target_include_directories(raytrace05 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(raytrace05 PUBLIC 
    image_buffer
    raytracer_lib
)

# raytrace lighting lib
add_library(lighting STATIC 
    raytrace/light.cpp
    raytrace/lighting_model.cpp
)

target_include_directories(lighting PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lighting PUBLIC 
    image_buffer
    raytracer_lib
)

# camera lib
add_library(camera STATIC 
    raytrace/camera.cpp
)

target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(camera PUBLIC 
    image_buffer
    raytracer_lib
)

# raytrace chapter 05
add_library(raytrace06 STATIC 
    raytrace/raytrace_chapter06.cpp
)

target_include_directories(raytrace06 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(raytrace06 PUBLIC 
    image_buffer
    raytracer_lib
    lighting
)

# world
find_package(yaml-cpp REQUIRED)
add_library(world_loader STATIC
    utility/world_parser.cpp
)
target_include_directories(world_loader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(world_loader PUBLIC 
    image_buffer
    raytracer_lib
    lighting
    yaml-cpp
    camera
)

# imgui
add_library(ui STATIC 
    imgui/imgui_wrapper.cpp
)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ui PUBLIC 
    image_buffer
    utility
    raytrace06
)

