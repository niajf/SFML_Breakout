#include <cmath>
#include "Breakout/Entities/BlockManager.h"
#include "Breakout/Constants.h"

void BlockManager::createLevel(int rows, int cols)
{
    blocks.clear();

    float blockWidth = Config::BLOCK_WIDTH;
    float blockHeight = Config::BLOCK_HEIGHT;
    float padding = Config::BLOCK_PADDING;

    float startX = (Config::WINDOW_WIDTH / 2) - (cols / 2) * (blockWidth + padding);
    float startY = Config::BLOCK_Y_OFFSET;

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