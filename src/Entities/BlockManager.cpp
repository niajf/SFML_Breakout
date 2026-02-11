#include "Breakout/Entities/BlockManager.h"
#include <cmath>

void BlockManager::createLevel(int rows, int cols)
{
    blocks.clear();

    float blockWidth = 60.f;
    float blockHeight = 20.f;
    float padding = 10.f; // ブロック間の隙間

    float startX = 400.f - (cols / 2) * (blockWidth + padding);
    float startY = 50.f;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            float x = startX + j * (blockWidth + padding);
            float y = startY + i * (blockHeight + padding);

            // 色を少し変えてみる（行ごとに変化）
            sf::Color color = sf::Color(255 - i * 20, 100 + i * 20, 150);

            // vectorに追加（emplace_backはコピーが発生せず高速）
            blocks.emplace_back(x, y, blockWidth, blockHeight, color);
        }
    }
}

void BlockManager::update(Ball &ball)
{
    for (auto &block : blocks)
    {
        // すでに壊れているブロックは無視
        if (block.isDestroyed())
            continue;

        // AABB衝突判定（重なっているか？）
        // if (block.getBounds().intersects(ball.getBounds()))
        // {

        //     // 1. ブロックを破壊
        //     block.destroy();

        //     // 2. 反射処理（簡易版）
        //     // 本来は「どこに当たったか」を計算して反射方向を変えるべきですが、
        //     // まずは「当たったらY方向を反転」で実装します。
        //     // ※余裕があれば後述の「高度な反射」を実装してください

        //     // Ball側に bounceY() や reverseVelocityY() のようなメソッドが必要です
        //     // ここでは Ball.h に bounceY() がある前提とします
        //     // ball.bounceY();

        //     // ★Ballクラスの実装に合わせて以下のように調整してください
        //     sf::Vector2f pos = ball.getPosition();
        //     sf::FloatRect blockRect = block.getBounds();

        //     // ボールの中心とブロックの中心の差分を取る
        //     float overlapLeft = pos.x - blockRect.left;
        //     float overlapRight = (blockRect.left + blockRect.width) - pos.x;
        //     float overlapTop = pos.y - blockRect.top;
        //     float overlapBottom = (blockRect.top + blockRect.height) - pos.y;

        //     // 最も重なりが小さい方向＝衝突した面とみなす
        //     float minOverlapX = std::min(overlapLeft, overlapRight);
        //     float minOverlapY = std::min(overlapTop, overlapBottom);

        //     if (minOverlapX < minOverlapY)
        //     {
        //         ball.bounceX(); // 横から当たった
        //     }
        //     else
        //     {
        //         ball.bounceY(); // 上下から当たった
        //     }

        //     // 1フレームに複数のブロックと衝突しないよう、1つ当たったらループを抜けるのが無難
        //     break;
        // }
    }
}

void BlockManager::draw(sf::RenderWindow &window)
{
    for (auto &block : blocks)
    {
        block.draw(window);
    }
}