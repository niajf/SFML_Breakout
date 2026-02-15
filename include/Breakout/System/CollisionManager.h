#pragma once
#include <SFML/Graphics.hpp>
#include "Breakout/Entities/Ball.h"
#include "Breakout/Entities/Paddle.h"
#include "Breakout/Entities/BlockManager.h"

class CollisionManager
{
private:
    // 衝突判定関数
    bool checkAABB(const sf::FloatRect &a, const sf::FloatRect &b);
    bool resolveCollision(Ball &ball, const sf::FloatRect &targetBounds);

public:
    // 毎フレーム呼び出すメイン関数
    void update(Ball &ball, Paddle &paddle, BlockManager &blockManager);

    // 内部処理用のヘルパー関数
    void checkWallCollision(Ball &ball);
    void checkPaddleCollision(Ball &ball, const Paddle &paddle);
    int checkBlockCollision(Ball &ball, BlockManager &blockManager);
};