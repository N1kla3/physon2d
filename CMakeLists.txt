cmake_minimum_required(VERSION 3.30)
project(Physon2d)

set(CMAKE_CXX_STANDARD 20)

set(PHYSON_EXAMPLES)
set(PHYSON_TESTS)

add_library(Physon2d
        src/Particle.cpp
        src/Particle.h)

if (PHYSON_EXAMPLES)
    add_executable(physonExample examples/main.cpp)
    target_link_libraries(physonExample Physon2d)
endif ()

if (PHYSON_TESTS)
    add_executable(physonTests tests/test.cpp)
    target_link_libraries(physonExample Physon2d)
endif ()
