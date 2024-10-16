cmake_minimum_required(VERSION 3.10)
project(Tests)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)


FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)


add_compile_options(--coverage)
add_link_options(--coverage)
add_executable(Tests
        source/SimpleForecastTests.cpp
        source/ComplexForecastTests.cpp
)

target_link_libraries(
        Tests gtest_main
        WeatherReport)

include(GoogleTest)
gtest_discover_tests(Tests)

