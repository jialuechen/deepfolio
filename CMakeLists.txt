# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(ThunderFix)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# Source files
file(GLOB CORE_SRC ${CMAKE_SOURCE_DIR}/src/core/*.cpp)
file(GLOB EXTENSIONS_SRC ${CMAKE_SOURCE_DIR}/src/extensions/*.cpp)
file(GLOB UTIL_SRC ${CMAKE_SOURCE_DIR}/src/util/*.cpp)

# Library target
add_library(ThunderFix ${CORE_SRC} ${EXTENSIONS_SRC} ${UTIL_SRC})

# Tests
enable_testing()
add_subdirectory(tests)

# Examples
add_executable(BasicUsageExample examples/BasicUsageExample.cpp)
target_link_libraries(BasicUsageExample ThunderFix)

add_executable(AdvancedUsageExample examples/AdvancedUsageExample.cpp)
target_link_libraries(AdvancedUsageExample ThunderFix)
