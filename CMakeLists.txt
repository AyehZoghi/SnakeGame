cmake_minimum_required(VERSION 3.21)
project(Snake)

set(CMAKE_CXX_STANDARD 20)

add_executable(Snake cmake-build-debug/source/main.cpp cmake-build-debug/source/Engine.cpp
        cmake-build-debug/headers/Engine.h cmake-build-debug/source/draw.cpp cmake-build-debug/source/input.cpp
        cmake-build-debug/source/SnakeSection.cpp cmake-build-debug/headers/SnakeSection.h
        cmake-build-debug/source/update.cpp cmake-build-debug/source/Apple.cpp
        cmake-build-debug/headers/Apple.h cmake-build-debug/source/Wall.cpp
        cmake-build-debug/headers/Wall.h cmake-build-debug/source/MainMenu.cpp
        cmake-build-debug/headers/MainMenu.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML-2.5.1/include)
target_link_libraries(Snake sfml-system sfml-window sfml-graphics sfml-audio sfml-network)