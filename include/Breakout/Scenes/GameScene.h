#pragma once
#include "Breakout/Scenes/Scene.h"
#include "Breakout/Entities/Ball.h"
#include "Breakout/Entities/Paddle.h"
#include "Breakout/Entities/BlockManager.h"
#include "Breakout/System/CollisionManager.h"
#include "Breakout/UI/Score.h"

enum class PlayState
{
    Ready,
    Playing
};

class GameScene : public Scene
{
private:
    // シーン遷移リクエスト用のコールバック関数
    std::function<void(SceneType, int, int)> requestSceneChange;

    // エンティティとマネージャー
    std::unique_ptr<Ball> ball;
    std::unique_ptr<Paddle> paddle;
    BlockManager blockManager;
    CollisionManager collisionManager;
    Score score;
    int currentStage;

    // 状態管理用
    PlayState playState;
    float readyTimer;

    // UI
    sf::Text readyText;
    sf::Text controlsText;

    // 補助関数
    void centerTextOrigin(sf::Text &text);

public:
    GameScene(SharedContext *ctx, std::function<void(SceneType, int, int)> changeCb, int s, int st);

    void processInput() override;
    void update(float dt) override;
    void draw() override;
};