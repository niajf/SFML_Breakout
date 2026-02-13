#pragma once
#include "Breakout/Scenes/Scene.h"

class GameClearScene : public Scene
{
    // シーン遷移リクエスト用のコールバック関数
    std::function<void(SceneType, int)> requestSceneChange;

    int finalScore;
    float elapsedTime;

    sf::Text clearText;
    sf::Text scoreText;
    sf::Text promptText;
    sf::RectangleShape overlay; // 背景を少し暗くする用

    // テキストの中央揃えを簡単にするヘルパー関数
    void centerTextOrigin(sf::Text &text);

public:
    GameClearScene(SharedContext *ctx, std::function<void(SceneType, int)> changeCb, int score);

    void processInput() override;
    void update(float dt) override;
    void draw() override;
};