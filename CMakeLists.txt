cmake_minimum_required(VERSION 3.10.0)
project(01_Breakout)

# C++の標準を指定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.0 COMPONENTS Graphics Window System Audio REQUIRED)

add_executable(01_Breakout src/main.cpp)

target_link_libraries(01_Breakout 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio
)

