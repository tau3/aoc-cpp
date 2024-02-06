cmake_minimum_required(VERSION 3.18.4)

set(CMAKE_CXX_FLAGS "-g -pedantic -Wall -Wextra")
set(CMAKE_CXX_STANDARD 17)

project (aoc2023)
file(GLOB aoc2023_src
    "*.h"
    "*.cpp"
)
add_executable(${PROJECT_NAME} ${aoc2023_src})

