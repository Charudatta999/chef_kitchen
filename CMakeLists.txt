cmake_minimum_required(VERSION 3.14)
project(chef_kitchen LANGUAGES CXX)

# Set policy to handle FetchContent timestamp warning
cmake_policy(SET CMP0135 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler-specific flags
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-g -fprofile-arcs -ftest-coverage -std=c++17 -Wall -O0 --coverage)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()


# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/inc/structures
    ${PROJECT_SOURCE_DIR}/inc/restaurant
    ${PROJECT_SOURCE_DIR}/inc/utils
)
# Add inc/windows and deps-lib if building on Windows (OS check, not compiler)
if(WIN32)
    message(STATUS "Including inc/windows and deps-lib for Windows build.")
    include_directories(${PROJECT_SOURCE_DIR}/deps-inc/windows)
    link_directories(${PROJECT_SOURCE_DIR}/deps-lib/windows/lib)
else()
    message(STATUS "Including deps-inc/linux and deps-lib for Linux build.")
    include_directories(${PROJECT_SOURCE_DIR}/deps-inc/linux)
    link_directories(${PROJECT_SOURCE_DIR}/deps-lib/linux/lib)
    link_directories(${PROJECT_SOURCE_DIR}/deps-lib/linux/lib64)
endif()
# Source files
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/structures/DoubleLL.cpp
    ${PROJECT_SOURCE_DIR}/src/structures/DoublelyLinkedList.cpp
    ${PROJECT_SOURCE_DIR}/src/structures/HelperStructs.cpp
    ${PROJECT_SOURCE_DIR}/src/structures/Lru.cpp
    ${PROJECT_SOURCE_DIR}/src/restaurant/Inventory.cpp
    ${PROJECT_SOURCE_DIR}/src/restaurant/Order.cpp
    ${PROJECT_SOURCE_DIR}/src/restaurant/Recipes.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/StringUtils.cpp
)

# Create the main library
add_library(chef_kitchen_lib ${SOURCES})

# GoogleTest
# Try to find GTest, or download it if not found
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test sources
file(GLOB TEST_SOURCES "test/*.cpp")

add_executable(chef_kitchen_tests ${TEST_SOURCES})
target_link_libraries(chef_kitchen_tests chef_kitchen_lib gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(chef_kitchen_tests)

add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/gcovr_output
    COMMAND gcovr --html --output ${PROJECT_SOURCE_DIR}/gcovr_output/coverage_report.html
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)