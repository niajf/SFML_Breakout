#pragma once
#include "Breakout/Scenes/Scene.h"

class TitleScene : public Scene
{
    // シーン遷移リクエスト用のコールバック関数
    std::function<void(SceneType, int, int)> requestSceneChange;

    float elapsedTime;

    // UIパーツ
    sf::Text titleText;
    sf::Text promptText;
    sf::Text creditText;

    // タイトルロゴの初期Y座標（浮遊アニメーションの基準点）
    float titleBaseY;

    void centerTextOrigin(sf::Text &text);

public:
    TitleScene(SharedContext *ctx, std::function<void(SceneType, int, int)> changeCb);

    void processInput() override;
    void update(float dt) override;
    void draw() override;
};