cmake_minimum_required(VERSION 3.10)
project(Dialogue)

set(CMAKE_CXX_STANDARD 20)
add_executable(Dialogue source/main.cpp)

# Линкуем приложение с библиотекой weather_report
target_link_libraries(Dialogue WeatherReport)
