cmake_minimum_required(VERSION 3.24.2)
project(testproj CXX)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
    main.cpp
    candle.cpp
)

set(HEADERS
    candle.h
)

add_executable(testproj ${SOURCES} ${HEADERS})