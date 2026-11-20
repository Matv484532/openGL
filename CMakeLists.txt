cmake_minimum_required(VERSION 3.10)
project(LearnOpenGLProject)

set(CMAKE_CXX_STANDARD 17)

# 1. Automatically find all source files
file (GLOB_RECURSE SOURCES 
    CONFIGURE_DEPENDS
    "*.cpp"
    "*.c"
    "*.h"
    "*.hpp"
    "*.vs"
    "*.fs"
)

# 2. Filter out the build and .vscode folders immediately
list(FILTER SOURCES EXCLUDE REGEX "(/build/|/\\.vscode/)")

# 3. Create the executable target FIRST
add_executable(main ${SOURCES})

# 4. Generate root_directory.h from the template into the build folder
configure_file(configuration/root_directory.h.in configuration/root_directory.h)

# 5. Tell the compiler where to find generated files and dependencies
target_include_directories(main PRIVATE 
    ${CMAKE_BINARY_DIR}/configuration
    ${CMAKE_SOURCE_DIR}/Dependencies
    ${CMAKE_SOURCE_DIR}
)

# 6. Link OpenGL libraries for Windows
target_link_libraries(main PRIVATE glfw3 opengl32 gdi32)