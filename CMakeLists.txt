cmake_minimum_required(VERSION 3.15)

# project name.
project(learn_OpenGL)

# C++ standard version.
set(CMAKE_CXX_STANDARD 14)

# set source directory to variable. (no recursive)
aux_source_directory(./src proj_src)
#aux_source_directory(./src/imgui imgui_src)
aux_source_directory(./include/imgui imgui_src)

# compile imgui as static library.
add_library(imgui STATIC ${imgui_src})

# set include search path.
include_directories(include)

# set link search path.
link_directories(lib)

add_executable(learn_OpenGL ${proj_src})

target_link_libraries(learn_OpenGL glfw3 opengl32 imgui)