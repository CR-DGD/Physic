cmake_minimum_required(VERSION 3.20)
project(PhysicsEngine CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(raylib)

# Every .cpp under src/ gets built, so new physics files need no CMake edits.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(physics ${SOURCES})
target_include_directories(physics PRIVATE src)
target_link_libraries(physics PRIVATE raylib)

if(MSVC)
    target_compile_options(physics PRIVATE /W4 /permissive-)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT physics)
else()
    target_compile_options(physics PRIVATE -Wall -Wextra)
endif()
