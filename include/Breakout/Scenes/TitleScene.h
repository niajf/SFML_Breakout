#pragma once
#include "Breakout/Scenes/Scene.h"

class TitleScene : public Scene
{
    // シーン遷移リクエスト用のコールバック関数
    std::function<void(SceneType, int)> requestSceneChange;

public:
    TitleScene(SharedContext *ctx, std::function<void(SceneType, int)> changeCb);

    void processInput() override;
    void update(float dt) override;
    void draw() override;
};