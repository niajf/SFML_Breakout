#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
public:
    virtual ~GameObject() = default;

    // 自身の状態を更新する（dt: 経過時間）
    virtual void update(float dt) = 0;

    // 自身を描画する
    virtual void draw(sf::RenderWindow& window) = 0;

    // 当たり判定用の矩形（バウンディングボックス）を取得する
    virtual sf::FloatRect getBounds() const = 0;
    
    // 位置を取得・設定（必要に応じて）
    // virtual sf::Vector2f getPosition() const = 0;
    // virtual void setPosition(const sf::Vector2f& pos) = 0;
};