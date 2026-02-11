#include "Breakout/Scenes/GameScene.h"

GameScene::GameScene(SharedContext* ctx, std::function<void(SceneType)> changeCb)
    : Scene(ctx), requestSceneChange(changeCb) 
    {
        // 画面中央にボールを生成
        float centerX = ctx->window->getSize().x / 2.f;
        float centerY = ctx->window->getSize().y / 2.f;
        
        // make_unique でインスタンス化
        ball = std::make_unique<Ball>(centerX, centerY);
    }

void GameScene::processInput() {
    while (auto event = context->window->pollEvent()) {
        
        if (event->is<sf::Event::Closed>()) {
            context->window->close();
        }

        if (auto key = event->getIf<sf::Event::KeyPressed>()) {
             if (key->scancode == sf::Keyboard::Scan::Enter) {
                requestSceneChange(SceneType::GameOver);

                // メモリを開放済みのため、メソッドを抜け出さないとエラーが発生する
                return;
             }
        }
    }
}

void GameScene::update(float dt) {
    if (ball)
    {
        ball->update(dt);
        ball->checkWindowCollision(*(context->window));
    }
}

void GameScene::draw() {
    sf::Text text(*(context->font), "THIS IS GAME SCENE", 30);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    text.setPosition(sf::Vector2f(context->window->getSize()) / 2.f);

    if(ball)
    {
        ball->draw(*(context->window));
    }
    
    context->window->draw(text);
}