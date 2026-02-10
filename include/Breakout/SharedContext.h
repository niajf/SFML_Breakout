#pragma once
#include <SFML/Graphics.hpp>

// ゲーム全体で共有するデータ
struct SharedContext {
    sf::RenderWindow* window;
    sf::Font* font;
};