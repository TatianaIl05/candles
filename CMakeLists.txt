cmake_minimum_required(VERSION 3.24.2)
project(testproj CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)

set(SOURCES
    main.cpp
    candle.cpp
)

set(HEADERS
    candle.h
)

add_executable(testproj ${SOURCES} ${HEADERS})

target_link_libraries(testproj GTest::GTest GTest::Main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(testproj)
