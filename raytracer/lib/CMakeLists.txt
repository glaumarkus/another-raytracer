# math
add_library(raytracer_lib STATIC 
    math/vector2d.cpp
    math/mat.cpp
    math/ray.cpp
    math/object.cpp
    math/intersections.cpp
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


# imgui
add_library(ui STATIC 
    imgui/imgui_wrapper.cpp
)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ui PUBLIC 
    image_buffer
    utility
    raytrace05
)