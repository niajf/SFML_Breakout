#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <Breakout/Entities/Block.h>
#include <Breakout/Entities/Ball.h> // 衝突判定のためにBallを知る必要がある

class BlockManager
{
private:
    std::vector<Block> blocks; // ブロックの実体を格納する動的配列

public:
    // レベル生成（行数、列数、開始位置などを指定）
    void createLevel(int rows, int cols);

    // 更新処理（ボールとの当たり判定を行う）
    void update(Ball &ball);

    // 描画処理
    void draw(sf::RenderWindow &window);

    std::vector<Block> &getBlocks();
};