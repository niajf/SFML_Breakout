#include <iostream>
#include "Breakout/Game.h"
#include "Breakout/Scenes/TitleScene.h"
#include "Breakout/Scenes/GameScene.h"
#include "Breakout/Scenes/GameClearScene.h"
#include "Breakout/Constants.h"

Game::Game() : window(sf::VideoMode({Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}), Config::WINDOW_TITLE)
{
    // フォント読み込み（相対パス）
    // ※実行ファイルからのパスに注意
    if (!font.openFromFile(Config::FONT_PATH))
    {
        std::cerr << "Failed to load font!" << std::endl;
        // フォントがない場合の対策などをここに書く
    }

    context.window = &window;
    context.font = &font;

    switchTo(SceneType::Title, 0, 0);
}

void Game::switchTo(SceneType type, int score, int stage)
{
    // 次のシーンへの切り替え用コールバック
    auto changeCb = [this](SceneType newType, int score, int stage)
    { switchTo(newType, score, stage); };

    switch (type)
    {
    case SceneType::Title:
        currentScene = std::make_unique<TitleScene>(&context, changeCb);
        break;

    case SceneType::Game:
        currentScene = std::make_unique<GameScene>(&context, changeCb, score, stage);
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