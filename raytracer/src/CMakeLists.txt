# Define the main application target
add_executable(raytracer main.cpp)

# Link the main application with libraries (assuming libraytracer_lib as an example library name)
target_link_libraries(raytracer PRIVATE 
    eigen 
    # raytracer_lib
    # sdl_lib
    ui
)
