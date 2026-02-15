#include "Breakout/Entities/Paddle.h"
#include "Breakout/Constants.h"

Paddle::Paddle(float startX, float startY)
{
    shape.setSize({Config::PADDLE_WIDTH, Config::PADDLE_HEIGHT});
    shape.setFillColor(sf::Color::White);

    // 原点を長方形の中心に設定（重要！）
    shape.setOrigin({Config::PADDLE_WIDTH / 2.f, Config::PADDLE_HEIGHT / 2.f});
    shape.setPosition(sf::Vector2f(startX, startY));

    speed = Config::PADDLE_SPEED;
    direction = {0.f, 0.f};
}

void Paddle::update(float dt)
{
    sf::Vector2f pos = shape.getPosition();
    pos += direction * speed * dt;
    shape.setPosition(pos);

    float halfWidth = Config::PADDLE_WIDTH / 2.f;

    // 左側の壁チェック
    if (pos.x - halfWidth < 0.f)
    {
        shape.setPosition(sf::Vector2f(halfWidth, pos.y));
    }

    // 右側の壁チェック
    else if (pos.x + halfWidth > Config::WINDOW_WIDTH)
    {
        shape.setPosition(sf::Vector2f(Config::WINDOW_WIDTH - halfWidth, pos.y));
    }
}

void Paddle::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

sf::FloatRect Paddle::getBounds() const
{
    return shape.getGlobalBounds();
}

sf::Vector2f Paddle::getPosition() const
{
    return shape.getPosition();
}

void Paddle::setPosition(sf::Vector2f pos)
{
    shape.setPosition(pos);
}

void Paddle::setDirection(float dirX)
{
    // 入力された方向(-1, 0, 1) にスピードを掛ける
    direction.x = dirX;
}
