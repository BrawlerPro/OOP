# Components/CMakeLists.txt

add_library(Components
        source/AttackComponent.cpp
        source/DefenseComponent.cpp
        source/EnergyComponent.cpp
        source/HealthComponent.cpp
        source/MoraleComponent.cpp
        source/MovementComponent.cpp
        source/OwnerComponent.cpp
        source/PositionComponent.cpp
        source/QuantityComponent.cpp
        source/ResurrectionComponent.cpp
        source/SummonerComponent.cpp
)
target_include_directories(Components PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Components PUBLIC Core Enums TypeObjects Utilities)