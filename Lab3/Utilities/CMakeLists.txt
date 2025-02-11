add_library(Utilities INTERFACE)
target_include_directories(Utilities INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Utilities INTERFACE Components Core Enums TypeObjects)
