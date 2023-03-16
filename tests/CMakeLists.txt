project(Google_tests)

add_subdirectory(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/bin)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run main_test.cpp  ${src} test_suit1.cpp test_suit2.cpp test_suit3.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)