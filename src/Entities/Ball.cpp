#include <Breakout/Entities/Ball.h>

Ball::Ball(float x, float y) : speed(300.f) {
    float radius = 10.f;
    shape.setRadius(radius);
    shape.setOrigin({radius, radius}); // 中心を原点に   
    shape.setPosition(sf::Vector2(x, y));
    shape.setFillColor(sf::Color::Cyan);
    
    // 初期速度（斜めに飛ばすなど）
    direction = {1.f, -1.f}; 
}

void Ball::update(float dt) {
    // 速度 * 時間 = 移動距離
    // shape.move(velocity * speed * dt);

    // moveメソッドを用いない記法
    sf::Vector2f pos = shape.getPosition();
    pos += direction * speed * dt;
    shape.setPosition(pos);
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

// 画面外に出ないようにする簡易処理（テスト用）
void Ball::checkWindowCollision(const sf::RenderWindow& window) {
    sf::Vector2f pos = shape.getPosition();
    float radius = shape.getRadius();

    // 左壁
    if (pos.x - radius < 0) {
        shape.setPosition(sf::Vector2f(radius, pos.y));
        direction.x = std::abs(direction.x); // 右へ
    }
    // 右壁
    else if (pos.x + radius > window.getSize().x) {
        shape.setPosition(sf::Vector2f(window.getSize().x - radius, pos.y));
        direction.x = -std::abs(direction.x); // 左へ
    }
    // 天井
    if (pos.y - radius < 0) {
        shape.setPosition(sf::Vector2f(pos.x, radius));
        direction.y = std::abs(direction.y); // 下へ
    }
    // 底（ゲームオーバーだが今は反射させる）
    else if (pos.y + radius > window.getSize().y) {
        shape.setPosition(sf::Vector2f(pos.x, window.getSize().y - radius));
        direction.y = -std::abs(direction.y); // 上へ
    }
}

// ... 他の実装