#include "Breakout/System/CollisionManager.h"
#include <cmath>

void CollisionManager::update(Ball &ball, Paddle &paddle, BlockManager &blockManager, const sf::RenderWindow &window)
{
    checkWallCollision(ball, window);
    checkPaddleCollision(ball, paddle);
    checkBlockCollision(ball, blockManager);
}

bool CollisionManager::checkAABB(const sf::FloatRect &a, const sf::FloatRect &b)
{
    return (a.position.x < b.position.x + b.size.x &&
            a.position.x + a.size.x > b.position.x &&
            a.position.y < b.position.y + b.size.y &&
            a.position.y + a.size.y > b.position.y);
}

bool CollisionManager::resolveCollision(Ball &ball, const sf::FloatRect &targetBounds)
{
    sf::FloatRect ballBounds = ball.getBounds();

    if (!checkAABB(ballBounds, targetBounds))
    {
        return false;
    }

    // 各方向からの「めり込み量 (Overlap)」を計算
    float overlapLeft = (ballBounds.position.x + ballBounds.size.x) - targetBounds.position.x;
    float overlapRight = (targetBounds.position.x + targetBounds.size.x) - ballBounds.position.x;
    float overlapTop = (ballBounds.position.y + ballBounds.size.y) - targetBounds.position.y;
    float overlapBottom = (targetBounds.position.y + targetBounds.size.y) - ballBounds.position.y;

    // 4つのめり込み量のうち、最小のものを見つける
    float minOverlapX = std::min(overlapLeft, overlapRight);
    float minOverlapY = std::min(overlapTop, overlapBottom);

    // X方向のめり込みの方が小さい場合 ＝ 横からの衝突
    if (minOverlapX < minOverlapY)
    {
        // 左側からの衝突か、右側からの衝突か？
        if (overlapLeft < overlapRight)
        {
            // 左からぶつかった -> ボールを左に押し出す
            ball.setPosition(sf::Vector2f(ball.getPosition().x - overlapLeft, ball.getPosition().y));
        }
        else
        {
            // 右からぶつかった -> ボールを右に押し出す
            ball.setPosition(sf::Vector2f(ball.getPosition().x + overlapRight, ball.getPosition().y));
        }
        ball.bounceX();
    }
    // Y方向のめり込みの方が小さい場合 ＝ 上下からの衝突
    else
    {
        // 上からか、下からか？
        if (overlapTop < overlapBottom)
        {
            // 上からぶつかった -> ボールを上に押し出す
            ball.setPosition(sf::Vector2f(ball.getPosition().x, ball.getPosition().y - overlapTop));
        }
        else
        {
            // 下からぶつかった -> ボールを下に押し出す
            ball.setPosition(sf::Vector2f(ball.getPosition().x, ball.getPosition().y + overlapBottom));
        }
        ball.bounceY();
    }

    return true;
}

void CollisionManager::checkWallCollision(Ball &ball, const sf::RenderWindow &window)
{
    sf::Vector2f pos = ball.getPosition();
    float radius = ball.getBounds().size.x / 2.f; // 円の半径
    sf::Vector2u winSize = window.getSize();

    // 左壁
    if (pos.x - radius < 0)
    {
        ball.setPosition(sf::Vector2f(radius, pos.y)); // めり込み補正
        ball.bounceFromLeftWall();
    }
    // 右壁
    else if (pos.x + radius > winSize.x)
    {
        ball.setPosition(sf::Vector2f(winSize.x - radius, pos.y)); // めり込み補正
        ball.bounceFromRightWall();
    }
    // 天井
    if (pos.y - radius < 0)
    {
        ball.setPosition(sf::Vector2f(pos.x, radius)); // めり込み補正
        ball.bounceFromTopWall();
    }

    // 床（ゲームオーバー）の判定はここで行うか、GameSceneで行うか選択できます。
    // 今回は「物理的な反射」はせず、素通りさせる（GameSceneでY座標を見てGameOverにするため）
}

void CollisionManager::checkPaddleCollision(Ball &ball, const Paddle &paddle)
{
    if (checkAABB(ball.getBounds(), paddle.getBounds()))
    {
        // パドルの中心座標
        float paddleCenter = paddle.getPosition().x;
        // ボールの中心座標
        float ballCenter = ball.getPosition().x;

        // 中心からの距離を正規化 (-1.0 〜 1.0 の範囲にする)
        float offset = std::abs(ballCenter - paddleCenter);
        float width = paddle.getBounds().size.x;
        float hitFactor = (offset / (width / 2.f));

        // Ballクラスに追加したメソッドを呼ぶ
        ball.bounceFromPaddle(hitFactor);
        ball.setPosition({ball.getPosition().x, paddle.getPosition().y - ball.getBounds().size.x - 1.f});
    }
}

void CollisionManager::checkBlockCollision(Ball &ball, BlockManager &blockManager)
{
    auto &blocks = blockManager.getBlocks();

    for (auto &block : blocks)
    {
        if (block.isDestroyed())
            continue;

        // trueが返ってきたら「衝突して跳ね返った」ということ
        if (resolveCollision(ball, block.getBounds()))
        {
            block.destroy();
            break; // 1フレームに1つだけ壊す
        }
    }
}