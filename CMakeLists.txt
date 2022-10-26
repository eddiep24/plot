cmake_minimum_required(VERSION 3.13.4)

# OpenGL Policy
set(OpenGl_GL_PREFERENCE "GLVND")

project(fick)
# Compiler Flags
list(APPEND CMAKE_CXX_FLAGS "-std=c++17 -Wno-narrowing")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

# set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/")

# Shader files made global for main

add_subdirectory(Source)