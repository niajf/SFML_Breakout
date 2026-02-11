#pragma once
#include "Breakout/Scene.h"
#include "Breakout/Entities/Ball.h"
#include "Breakout/Entities/Paddle.h"

class GameScene : public Scene {
    // シーン遷移リクエスト用のコールバック関数
    std::function<void(SceneType)> requestSceneChange;

    // ボールをスマートポインタで管理
    std::unique_ptr<Ball> ball;
    std::unique_ptr<Paddle> paddle;

public:
    GameScene(SharedContext* ctx, std::function<void(SceneType)> changeCb);
    
    void processInput() override;
    void update(float dt) override;
    void draw() override;
};