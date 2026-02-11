#include "Breakout/Entities/Paddle.h"

Paddle::Paddle(float startX, float startY) {
    shape.setSize({PADDLE_WIDTH, PADDLE_HEIGHT});
    shape.setFillColor(sf::Color::White);
    
    // 原点を長方形の中心に設定（重要！）
    shape.setOrigin({PADDLE_WIDTH / 2.f, PADDLE_HEIGHT / 2.f});
    shape.setPosition(sf::Vector2f(startX, startY));

    speed = PADDLE_SPEED;
    direction = {0.f, 0.f};
}

void Paddle::update(float dt) {
    // 移動処理
    // shape.move(direction * speed * dt);

    sf::Vector2f pos = shape.getPosition();
    pos += direction * speed * dt;
    shape.setPosition(pos);

    // 画面外に出ないように制限（ハードコーディング避けのため本来はウィンドウサイズを渡すべき）
    // ここでは簡易的に 800幅 と仮定していま
    float halfWidth = PADDLE_WIDTH / 2.f;

    // 左側の壁チェック
    if (pos.x - halfWidth < 0.f) {
        shape.setPosition(sf::Vector2f(halfWidth, pos.y));
    }
    // 右側の壁チェック
    else if (pos.x + halfWidth > 800.f) { // 800.f はウィンドウ幅
        shape.setPosition(sf::Vector2f(800.f - halfWidth, pos.y));
    }
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Paddle::setDirection(float dirX) {
    // 入力された方向(-1, 0, 1) にスピードを掛ける
    direction.x = dirX;
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}