#include "Breakout/Game.h"
#include "Breakout/Scenes/TitleScene.h"
#include "Breakout/Scenes/GameScene.h"
#include "Breakout/Scenes/GameOverScene.h"
#include "Breakout/Scenes/GameClearScene.h"
#include <iostream>

Game::Game() : window(sf::VideoMode({800, 600}), "Breakout Refactored")
{
    // フォント読み込み（相対パス）
    // ※実行ファイルからのパスに注意
    if (!font.openFromFile("assets/fonts/PressStart2P-Regular.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        // フォントがない場合の対策などをここに書く
    }

    context.window = &window;
    context.font = &font;

    switchTo(SceneType::Title, 0);
}

void Game::switchTo(SceneType type, int score = 0)
{
    // 次のシーンへの切り替え用コールバック
    auto changeCb = [this](SceneType newType, int s = 0)
    { switchTo(newType, s); };

    switch (type)
    {
    case SceneType::Title:
        currentScene = std::make_unique<TitleScene>(&context, changeCb);
        break;

    case SceneType::Game:
        currentScene = std::make_unique<GameScene>(&context, changeCb);
        break;

    case SceneType::GameOver:
        currentScene = std::make_unique<GameOverScene>(&context, changeCb);
        break;

    case SceneType::GameClear:
        currentScene = std::make_unique<GameClearScene>(&context, changeCb, score);
        break;
    }
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if (currentScene)
        {
            currentScene->processInput();
            currentScene->update(dt);

            window.clear(sf::Color(64, 64, 64));
            currentScene->draw();
            window.display();
        }
    }
}