#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Score
{
private:
    int value;
    const int BASE_POINT = 10; // 1ブロックあたりの基本点

    sf::Text scoreText;

public:
    Score(sf::Font &font);
    ~Score() = default;

    void updateText();

    // スコアを加算する（壊したブロック数を渡す）
    void add(int destroyedBlocks, int stage);

    void setScore(int score);

    // ステージクリア時の処理
    void upStage();

    // ゲームオーバー時などのリセット
    void reset();

    int getValue();

    void draw(sf::RenderWindow &window);
};