cmake_minimum_required(VERSION 3.31)
project(node_raylib)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

#message(STATUS "raylib_FOUND = ${raylib_FOUND}")

# Print variables set by raylib's config
message(STATUS "raylib_INCLUDE_DIRS = ${raylib_INCLUDE_DIRS}")
message(STATUS "raylib_LIBRARIES = ${raylib_LIBRARIES}")

add_library(node_raylib SHARED library.cpp library.h schema.cpp schema.h)

target_link_libraries(node_raylib PRIVATE ${raylib_LIBRARIES}) # dynamic
#target_link_libraries(node_raylib PRIVATE /usr/local/lib/libraylib.a) # static

target_include_directories(node_raylib PRIVATE /usr/local/include/node ${raylib_INCLUDE_DIRS})

set_target_properties(node_raylib PROPERTIES
        PREFIX ""                         # No 'lib' prefix
        SUFFIX ".node"                    # Node.js expects .node extension
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist
        MACOSX_RPATH ON
)

# Important: prevent undefined symbol errors on macOS by deferring symbol resolution
# Node will resolve them at runtime
target_link_options(node_raylib PRIVATE
        "-undefined" "dynamic_lookup"
)

find_library(APPKIT_FRAMEWORK AppKit)
find_library(COCOA_FRAMEWORK Cocoa)
find_library(OPENGL_FRAMEWORK OpenGL)
find_library(IOKIT_FRAMEWORK IOKit)
find_library(COREVIDEO_FRAMEWORK CoreVideo)

# Link raylib and required macOS frameworks
target_link_libraries(node_raylib
        PRIVATE
        ${APPKIT_FRAMEWORK}
        ${COCOA_FRAMEWORK}
        ${OPENGL_FRAMEWORK}
        ${IOKIT_FRAMEWORK}
        ${COREVIDEO_FRAMEWORK}
)

#g++ -std=c++23 \
#-I/usr/local/include/node \
#-Wall -Wextra \
#-fPIC \
#-shared \
#-undefined dynamic_lookup \
#library.cpp \
#-o library.node

#clang++ -std=c++23 \
#-I/usr/local/include/node \
#-Wall -Wextra \
#-fPIC \
#-shared \
#-undefined dynamic_lookup \
#library.cpp \
#-o library.node