cmake_minimum_required(VERSION 4.3.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_CXX_FLAGS "-g -pedantic -Wall -Wextra -std=c++23")
set(CMAKE_CXX_FLAGS "-g -pedantic -Wall -Wextra -std=c++23 -O3")

project (aoc)
file(GLOB aoc
    "*.h"
    "*.cpp"
)
add_executable(${PROJECT_NAME} ${aoc})
