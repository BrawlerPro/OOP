add_library(WeatherReport
        source/ComplexForecast.cpp
        source/SimpleForecast.cpp
)

target_include_directories(WeatherReport PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
