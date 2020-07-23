find_package(GTest REQUIRED)

add_executable(mediacopier-unittest
    "${CMAKE_CURRENT_SOURCE_DIR}/test_example.cpp"
    )

target_link_libraries(mediacopier-unittest PRIVATE
    gtest gtest_main
    )

gtest_discover_tests(mediacopier-unittest)

enable_testing()