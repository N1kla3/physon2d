add_executable(physonTests test.cpp)
target_link_libraries(physonTests Physon2d GTest::gtest GTest::gtest_main)
add_test(NAME tests COMMAND physonTests)
