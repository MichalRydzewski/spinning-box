cmake_minimum_required(VERSION 3.23)
project(spinning_box)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(spinning_box main.cpp)

target_sources(
    spinning_box
    PRIVATE 
      glad/src/glad.c
      helpers.cpp
    
    PUBLIC
      helpers.h
)

target_include_directories(spinning_box
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)

target_link_libraries(spinning_box
    PRIVATE
      glfw
      OpenGL::GL
)
