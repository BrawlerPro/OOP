# Подключаем SFML
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
find_package(nlohmann_json REQUIRED)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g -O0")

add_executable(MyGameProject main.cpp)
target_link_libraries(MyGameProject PUBLIC Components Core Enums TypeObjects Utilities sfml-graphics sfml-window sfml-system)

