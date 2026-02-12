cmake_minimum_required(VERSION 3.10.0)
project(01_Breakout)

# C++の標準を指定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.0 COMPONENTS Graphics Window System Audio REQUIRED)

add_executable(Breakout 
    src/main.cpp
    src/Game.cpp
    src/Scenes/TitleScene.cpp
    src/Scenes/GameScene.cpp
    src/Scenes/GameOverScene.cpp
    src/Entities/Ball.cpp
    src/Entities/Paddle.cpp
    src/Entities/Block.cpp
    src/Entities/BlockManager.cpp
    src/System/CollisionManager.cpp
)

target_include_directories(Breakout PRIVATE "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(Breakout 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio
)

# ビルド成果物（実行ファイル）のディレクトリを取得
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})

# ソースディレクトリにある assets フォルダを、ビルドディレクトリにコピーするコマンド
# "copy_directory" は中身が更新されていれば上書きコピーします
add_custom_command(TARGET Breakout POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${BUILD_DIR}/assets
    COMMENT "Copying assets to build directory..."
)
