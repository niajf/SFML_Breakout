#pragma once
#include "Breakout/Scene.h"

class GameScene : public Scene {
    // シーン遷移リクエスト用のコールバック関数
    std::function<void(SceneType)> requestSceneChange;

public:
    GameScene(SharedContext* ctx, std::function<void(SceneType)> changeCb);
    
    void processInput() override;
    void update(float dt) override;
    void draw() override;
};