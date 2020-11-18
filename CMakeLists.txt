cmake_minimum_required(VERSION 3.15)
project(learn_OpenGL)

set(CMAKE_CXX_STANDARD 14)
aux_source_directory(./src proj_src)

include_directories(include)
link_directories(lib)
add_executable(learn_OpenGL ${proj_src})
target_link_libraries(learn_OpenGL glfw3dll opengl32)
