# math
add_library(raytracer_lib STATIC 
    math/vector2d.cpp
    math/mat.cpp
    )
target_link_libraries(raytracer_lib PRIVATE eigen)
target_include_directories(raytracer_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# utility
add_library(utility STATIC
    utility/logger.cpp
)
target_include_directories(utility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# imgui
add_library(ui STATIC 
    imgui/imgui_wrapper.cpp
    imgui/image_buffer.cpp
    imgui/color.cpp
)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ui PUBLIC 
    imgui
    glfw
    ${OPENGL_LIBRARIES} 
    dl
    utility
)

