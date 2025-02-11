cmake_minimum_required(VERSION 3.10)
project(MyGameProject)

set(CMAKE_CXX_STANDARD 17)


# Рекурсивно добавляем все поддиректории с исходными файлами
add_subdirectory(Components)
add_subdirectory(Core)
add_subdirectory(TypeObjects)
add_subdirectory(Enums)
add_subdirectory(Utilities)
add_subdirectory(Tests)
add_subdirectory(Game)
