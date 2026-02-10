#include "Breakout/Scenes/GameOverScene.h"

GameOverScene::GameOverScene(SharedContext* ctx, std::function<void(SceneType)> changeCb)
    : Scene(ctx), requestSceneChange(changeCb) {}

void GameOverScene::processInput() {
    while (auto event = context->window->pollEvent()) {

        if (event->is<sf::Event::Closed>()) {
            context->window->close();
        }

        if (auto key = event->getIf<sf::Event::KeyPressed>()) {
             if (key->scancode == sf::Keyboard::Scan::Enter) {
                requestSceneChange(SceneType::Title);

                // メモリを開放済みのため、メソッドを抜け出さないとエラーが発生する
                return;
             }
        }
    }
}

void GameOverScene::update(float dt) {
    // タイトルアニメーションなど
}

void GameOverScene::draw() {
    sf::Text text(*(context->font), "THIS IS GAMEOVER SCENE", 30);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    text.setPosition(sf::Vector2f(context->window->getSize()) / 2.f);
    
    context->window->draw(text);
}