cmake_minimum_required(VERSION 3.12)

project(mesydaq2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Create binaries in the root of the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH FALSE)

# Enable $ORIGIN in the rpath if supported by the target platform.
SET(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
SET(CMAKE_INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/")

add_subdirectory(src)
