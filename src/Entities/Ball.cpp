#include <Breakout/Entities/Ball.h>

const float MIN_Y_DIRECTION = 0.2f;

Ball::Ball(float x, float y) : speed(300.f)
{
    float radius = 10.f;
    shape.setRadius(radius);
    shape.setOrigin({radius, radius}); // 中心を原点に
    shape.setPosition(sf::Vector2(x, y));
    shape.setFillColor(sf::Color::Cyan);

    // 初期速度（斜めに飛ばすなど）
    direction = {1.f, -1.f};
}

void Ball::update(float dt)
{
    // 速度 * 時間 = 移動距離
    // shape.move(velocity * speed * dt);

    // moveメソッドを用いない記法
    sf::Vector2f pos = shape.getPosition();
    pos += direction * speed * dt;
    shape.setPosition(pos);
}

void Ball::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

sf::FloatRect Ball::getBounds() const
{
    return shape.getGlobalBounds();
}

sf::Vector2f Ball::getPosition() const
{
    return shape.getPosition();
}

void Ball::setPosition(sf::Vector2f pos)
{
    shape.setPosition(pos);
}

void Ball::bounceX()
{
    direction.x = -direction.x;
}

void Ball::bounceY()
{
    direction.y = -direction.y;

    if (std::abs(direction.y) < MIN_Y_DIRECTION)
    {
        float signY = (direction.y > 0.0) ? 1.f : -1.f;
        direction.y = signY * direction.y;

        float signX = (direction.x > 0.0) ? 1.f : -1.f;
        direction.x = signX * std::sqrt(1 - direction.y * direction.y);
    }
}

void Ball::bounceFromRightWall()
{
    direction.x = -std::abs(direction.x);
}

void Ball::bounceFromLeftWall()
{
    direction.x = std::abs(direction.x);
}

void Ball::bounceFromTopWall()
{
    direction.y = std::abs(direction.x);
}

void Ball::bounceFromPaddle(float hitFactor)
{
    direction.y = -std::abs(direction.y);
    direction.x = hitFactor * 1.5f;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.f)
    {
        direction /= length;
    }
}