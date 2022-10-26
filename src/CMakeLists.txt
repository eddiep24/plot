cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(fick VERSION 1.0)

add_definitions(-std=c++17)
# set(CXX_FLAGS "-Wall" "-Werror" "-Wextra" "-fsanitize=undefined,address")
# set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
# set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} math_utils.cpp shader_utils.cpp utils.cpp main.cpp)

find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})


target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
target_link_libraries(${PROJECT_NAME} "-framework IOKit")
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_gl_LIBRARY})