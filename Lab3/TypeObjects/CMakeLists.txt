add_library(TypeObjects INTERFACE)

target_include_directories(TypeObjects INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(TypeObjects INTERFACE Components Core Enums Utilities)
