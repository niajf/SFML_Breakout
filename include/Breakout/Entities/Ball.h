#pragma once
#include "Breakout/Entities/GameObject.h"

class Ball : public GameObject
{
private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    float speed;

public:
    Ball(float x, float y);

    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
    sf::FloatRect getBounds() const override;

    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);

    void bounceX();
    void bounceY();
    void bounceFromRightWall();
    void bounceFromLeftWall();
    void bounceFromTopWall();
    void bounceFromPaddle(float hitFactor);
};