# Core/CMakeLists.txt


add_library(Core
        source/Game.cpp
        source/Cell.cpp
        source/Entity.cpp
        source/EntityManager.cpp
        source/GameMap.cpp
)
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Core PUBLIC Components Enums TypeObjects Utilities)
#add_library(Core INTERFACE)
#target_include_directories(Core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
