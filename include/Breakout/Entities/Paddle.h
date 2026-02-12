#pragma once
#include <SFML/Graphics.hpp>
#include "Breakout/Entities/GameObject.h"

class Paddle : public GameObject
{
private:
    sf::RectangleShape shape;
    float speed;
    sf::Vector2f direction; // 現在の移動速度（方向 * speed）

    // パドルの定数（調整しやすいようにここに書くか、定数ファイルに分ける）
    const float PADDLE_WIDTH = 100.f;
    const float PADDLE_HEIGHT = 20.f;
    const float PADDLE_SPEED = 500.f;

public:
    Paddle(float startX, float startY);

    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;

    sf::FloatRect getBounds() const override;

    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);

    // 外部から移動方向を指示するメソッド
    // dir: -1(左), 0(停止), 1(右)
    void setDirection(float dirX);
};