#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "SharedContext.h"
#include "Scene.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    SharedContext context;
    std::unique_ptr<Scene> currentScene;

    // 内部で使用するシーン切り替えメソッド
    void switchTo(SceneType type);

public:
    Game();
    void run();
};