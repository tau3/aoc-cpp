cmake_minimum_required(VERSION 3.18.4)

include(FetchContent)
FetchContent_Declare(Z3
        GIT_REPOSITORY https://github.com/Z3Prover/z3
        GIT_TAG        z3-4.15.3
	GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(Z3)

# Add the C++ API include directory for z3++.h
if(TARGET libz3)
    target_include_directories(libz3 INTERFACE
        $<BUILD_INTERFACE:${z3_SOURCE_DIR}/src/api/c++>
    )
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-g -pedantic -Wall -Wextra -O2")
set(CMAKE_CXX_STANDARD 17)

project (aoc)
file(GLOB aoc
    "*.h"
    "*.cpp"
)
add_executable(${PROJECT_NAME} ${aoc})

target_link_libraries(aoc PRIVATE libz3)
