cmake_minimum_required(VERSION 3.13.4)

include_directories(shaders)

project(fickMain)
# OpenGL Policy
set(OpenGl_GL_PREFERENCE "GLVND")

add_subdirectory(src)


