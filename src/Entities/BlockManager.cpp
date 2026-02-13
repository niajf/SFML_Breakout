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
}

void BlockManager::draw(sf::RenderWindow &window)
{
    for (auto &block : blocks)
    {
        block.draw(window);
    }
}

std::vector<Block> &BlockManager::getBlocks()
{
    return blocks;
}