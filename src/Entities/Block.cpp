#include "Breakout/Entities/Block.h"
#include "Breakout/Constants.h"

Block::Block(float x, float y, float width, float height, sf::Color color)
    : destroyed(false)
{
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize({width, height});
    shape.setFillColor(color);

    // 枠線を少しつけて見やすくする（お好みで）
    shape.setOutlineThickness(Config::BLOCK_OUTLINE_SIZE);
    shape.setOutlineColor(sf::Color::Black);
}

void Block::update(float dt)
{
}

void Block::draw(sf::RenderWindow &window)
{
    if (!destroyed)
    {
        window.draw(shape);
    }
}

sf::FloatRect Block::getBounds() const
{
    return shape.getGlobalBounds();
}

bool Block::isDestroyed() const
{
    return destroyed;
}

void Block::destroy()
{
    destroyed = true;
}