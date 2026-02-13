#pragma once
#include "Breakout/SharedContext.h"
#include <functional>
#include <iostream>

// シーンの種類を定義
enum class SceneType
{
    Title,
    Game,
    GameClear
};

// シーンの基底クラス（インターフェース）
class Scene
{
protected:
    SharedContext *context;

public:
    explicit Scene(SharedContext *ctx) : context(ctx) {}
    virtual ~Scene() = default;

    virtual void processInput() = 0;
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
};