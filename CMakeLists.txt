cmake_minimum_required(VERSION 4.3.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_FLAGS "-g -pedantic -Wall -Wextra")
set(CMAKE_CXX_FLAGS "-g -pedantic -Wall -Wextra -O3")
set(CMAKE_CXX_STANDARD 26)

project (aoc)
file(GLOB aoc
    "*.h"
    "*.cpp"
)
add_executable(${PROJECT_NAME} ${aoc})

# 26.05
find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL)
