#pragma once
#include <SFML/Graphics.hpp>

namespace Config
{
    // --- ウィンドウ設定 ---
    constexpr unsigned int WINDOW_WIDTH = 800.f;
    constexpr unsigned int WINDOW_HEIGHT = 600.f;
    constexpr char WINDOW_TITLE[] = "Breakout Game";

    // --- ボール設定 ---
    constexpr float BALL_RADIUS = 10.f;
    constexpr float BALL_SPEED_BASE = 300.f;
    constexpr float BALL_SPEED_COEFFICIENT = 0.25f;
    constexpr float BALL_SPEED_INCREMENT = 50.f; // ステージごとの加速
    constexpr float BALL_MIN_Y_DIRECTION = 0.2f;

    // --- パドル設定 ---
    constexpr float PADDLE_WIDTH = 100.f;
    constexpr float PADDLE_HEIGHT = 20.f;
    constexpr float PADDLE_SPEED = 500.f;
    constexpr float PADDLE_Y_OFFSET = 50.f; // 下端からの距離

    // --- ブロック設定 ---
    constexpr float BLOCK_WIDTH = 80.f;
    constexpr float BLOCK_HEIGHT = 30.f;
    constexpr float BLOCK_PADDING = 10.f;
    constexpr float BLOCK_Y_OFFSET = 100.f;
    constexpr float BLOCK_OUTLINE_SIZE = 1.f;

    // --- スコア設定 ---
    constexpr int SCORE_BASE_POINT = 10;

    // --- シーン設定 ---
    constexpr int FONT_SIZE_TITLE = 70;
    constexpr float FONT_SIZE_OUTLINE_TITLE = 5.f;
    // constexpr sf::Color FONT_COLOR_TITLE = sf::Color::Cyan;
    // constexpr sf::Color FONT_OUTLINECOLOR_TITLE = sf::Color::Black;

    constexpr int FONT_SIZE_SUBTITLE = 50;
    constexpr float FONT_SIZE_OUTLINE_SUBTITLE = 3.f;
    // constexpr sf::Color FONT_COLOR_SUBTITLE = sf::Color::Yellow;
    // constexpr sf::Color FONT_OUTLINECOLOR_SUBTITLE = sf::Color::Black;

    constexpr int FONT_SIZE_BODY = 20;
    constexpr float FONT_SIZE_OUTLINE_BODY = 3.f;
    // constexpr sf::Color FONT_COLOR_BODY = sf::Color::White;

    constexpr int FONT_SIZE_SMALL = 12;
    // constexpr sf::Color FONT_COLOR_SMALL = sf::Color(150, 150, 150);

    // --- リソースパス設定 ---
    constexpr char FONT_PATH[] = "assets/fonts/PressStart2P-Regular.ttf";
}