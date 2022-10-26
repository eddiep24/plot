cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(fick)

add_executable(${PROJECT_NAME} main.cpp math_utils.cpp shader_utils.cpp)

find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)


target_link_libraries(fick "-framework Cocoa")
target_link_libraries(fick "-framework OpenGL")
target_link_libraries(fick "-framework IOKit")
target_link_libraries(fick glfw ${OPENGL_gl_LIBRARY})

