cmake_minimum_required(VERSION 3.10)
project(LearnOpenGLProject)

set(CMAKE_CXX_STANDARD 17)

#Automatically find all source files in your project folders
file (GLOB SOURCES
    "main.cpp"
    "Classes/*.cpp"
    "Dependencies/*.c"
    "Dependencies/*.cpp"
)

add_executable(main ${SOURCES})

#Link OpenGL libraries for windows

target_link_libraries(main PRIVATE glfw3 opengl32 gdi32)