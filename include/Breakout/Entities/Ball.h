#pragma once
#include "Breakout/GameObject.h"

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

    void bounceX();
    void bounceY();
    void bounceFromPaddle(float hitFactor);
    void checkWindowCollision(const sf::RenderWindow &window);
};