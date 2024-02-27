# Enable testing with CTest
enable_testing()

# Define test executable
add_executable(misc misc.cpp) 

# Link the test executable with GoogleTest and your libraries
target_link_libraries(misc gtest gtest_main utility world_loader)

# Register the executable as a test
add_test(NAME misc COMMAND misc)


# Define test executable
add_executable(chapter01 chapter01.cpp) 

# Link the test executable with GoogleTest and your libraries
target_link_libraries(chapter01 gtest gtest_main raytracer_lib)

# Register the executable as a test
add_test(NAME chapter01 COMMAND chapter01)

# Define test executable
add_executable(chapter02 chapter02.cpp) 

# Link the test executable with GoogleTest and your libraries
target_link_libraries(chapter02 gtest gtest_main ui)

# Register the executable as a test
add_test(NAME chapter02 COMMAND chapter02)

# Define test executable
add_executable(chapter03 chapter03.cpp) 

# Link the test executable with GoogleTest and your libraries
target_link_libraries(chapter03 gtest gtest_main raytracer_lib)

# Register the executable as a test
add_test(NAME chapter03 COMMAND chapter03)

# Define test executable
add_executable(chapter04 chapter04.cpp) 

# Link the test executable with GoogleTest and your libraries
target_link_libraries(chapter04 gtest gtest_main raytracer_lib)

# Register the executable as a test
add_test(NAME chapter04 COMMAND chapter04)

# Define test executable
add_executable(chapter05 chapter05.cpp) 

# Link the test executable with GoogleTest and your libraries
target_link_libraries(chapter05 gtest gtest_main raytracer_lib image_buffer)

# Register the executable as a test
add_test(NAME chapter05 COMMAND chapter05)

# Define test executable
add_executable(chapter06 chapter06.cpp) 

# Link the test executable with GoogleTest and your libraries
target_link_libraries(chapter06 gtest gtest_main raytracer_lib image_buffer lighting)

# Register the executable as a test
add_test(NAME chapter06 COMMAND chapter06)

# Define test executable
add_executable(chapter07 chapter07.cpp) 

# Link the test executable with GoogleTest and your libraries
target_link_libraries(chapter07 gtest gtest_main raytracer_lib image_buffer lighting utility world_loader)

# Register the executable as a test
add_test(NAME chapter07 COMMAND chapter07)

