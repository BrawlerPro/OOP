add_library(WeatherReport
        source/ComplexForecast.cpp
        source/SimpleForecast.cpp
)
add_compile_options(--coverage)
add_link_options(--coverage)
target_include_directories(WeatherReport PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
