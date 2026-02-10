#include "Breakout/Scenes/TitleScene.h"

TitleScene::TitleScene(SharedContext* ctx, std::function<void(SceneType)> changeCb)
    : Scene(ctx), requestSceneChange(changeCb) {}

void TitleScene::processInput() {
    while (auto event = context->window->pollEvent()) {

        if (event->is<sf::Event::Closed>()) {
            context->window->close();
        }

        if (auto key = event->getIf<sf::Event::KeyPressed>()) {
             if (key->scancode == sf::Keyboard::Scan::Enter) {
                requestSceneChange(SceneType::Game);

                // メモリを開放済みのため、メソッドを抜け出さないとエラーが発生する
                return;
             }
        }
    }
}

void TitleScene::update(float dt) {
    // タイトルアニメーションなど
}

void TitleScene::draw() {
    sf::Text text(*(context->font), "PRESS ENTER TO START", 30);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    text.setPosition(sf::Vector2f(context->window->getSize()) / 2.f);
    
    context->window->draw(text);
}