#pragma once
#include "Breakout/GameObject.h"

class Ball : public GameObject {
private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    float speed;

public:
    Ball(float x, float y);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    sf::FloatRect getBounds() const override;
    // sf::Vector2f getPosition() const override;

    // void setPosition(const sf::Vector2f& pos) override;

    // // 具体的な挙動
    // void bounceX(); // 横の壁に当たった時の反射
    // void bounceY(); // 天井やパドルに当たった時の反射
    // void reset();   // ミスした時に初期位置に戻す
    
    // // 速度調整など
    // void setVelocity(const sf::Vector2f& vel);

    void checkWindowCollision(const sf::RenderWindow& window);
};