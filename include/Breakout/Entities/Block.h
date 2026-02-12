#pragma once
#include "Breakout/Entities/GameObject.h"

// GameObjectを継承
class Block : public GameObject
{
private:
    sf::RectangleShape shape;
    bool destroyed;

public:
    Block(float x, float y, float width, float height, sf::Color color);

    // --- GameObjectの必須機能を実装 ---
    void update(float dt) override; // ブロックは動かないが定義は必要
    void draw(sf::RenderWindow &window) override;
    sf::FloatRect getBounds() const override;

    // GameObjectにはない独自機能
    bool isDestroyed() const;
    void destroy();
};