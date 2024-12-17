cmake_minimum_required(VERSION 3.18.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-g -pedantic -Wall -Wextra")
set(CMAKE_CXX_STANDARD 17)

project (aoc)
file(GLOB aoc
    "*.h"
    "*.cpp"
)
add_executable(${PROJECT_NAME} ${aoc})

