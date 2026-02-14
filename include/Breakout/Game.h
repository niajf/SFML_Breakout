#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "SharedContext.h"
#include "Breakout/Scenes/Scene.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Font font;
    SharedContext context;
    std::unique_ptr<Scene> currentScene;

    // 内部で使用するシーン切り替えメソッド
    void switchTo(SceneType type, int score, int stage);

public:
    Game();
    void run();
};