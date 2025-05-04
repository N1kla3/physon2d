cmake_minimum_required(VERSION 3.30)
project(Physon2d)

set(CMAKE_CXX_STANDARD 20)

set(PHYSON_EXAMPLES)
set(PHYSON_TESTS)

add_subdirectory(glm)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(Physon2d
        src/Types.h
        src/Particle.cpp
        src/Particle.h
        src/ForceGenerators.h
        src/ForceGenerators.cpp
        src/PhysScene.h
        src/PhysScene.cpp
)
target_link_libraries(Physon2d PUBLIC glm::glm)

if (PHYSON_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (PHYSON_TESTS)
    enable_testing()
    add_subdirectory(googletest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    add_subdirectory(tests)
endif ()
