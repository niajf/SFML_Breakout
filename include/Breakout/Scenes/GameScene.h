#pragma once
#include "Breakout/Scenes/Scene.h"
#include "Breakout/Entities/Ball.h"
#include "Breakout/Entities/Paddle.h"
#include "Breakout/Entities/BlockManager.h"
#include "Breakout/System/CollisionManager.h"
#include "Breakout/UI/Score.h"

class GameScene : public Scene
{
    // シーン遷移リクエスト用のコールバック関数
    std::function<void(SceneType, int)> requestSceneChange;

    // ボールをスマートポインタで管理
    std::unique_ptr<Ball> ball;
    std::unique_ptr<Paddle> paddle;
    BlockManager blockManager;

    CollisionManager collisionManager;

    Score score;

public:
    GameScene(SharedContext *ctx, std::function<void(SceneType, int)> changeCb);

    void processInput() override;
    void update(float dt) override;
    void draw() override;
};