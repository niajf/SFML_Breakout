#include "Breakout/Scenes/TitleScene.h"
#include "Breakout/Constants.h"

TitleScene::TitleScene(SharedContext *ctx, std::function<void(SceneType, int, int)> changeCb)
    : Scene(ctx),
      requestSceneChange(changeCb),
      elapsedTime(0.f),
      titleText(*(ctx->font), "BREAKOUT", Config::FONT_SIZE_TITLE),
      promptText(*(ctx->font), "PRESS ENTER TO START", Config::FONT_SIZE_BODY),
      creditText(*(ctx->font), "2026 PORTFOLIO", Config::FONT_SIZE_SMALL)
{
    // 1. タイトルロゴの設
    titleBaseY = Config::WINDOW_HEIGHT * 0.35f; // 基準となる高さを保存定
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setOutlineThickness(Config::FONT_SIZE_OUTLINE_TITLE);
    titleText.setOutlineColor(sf::Color::Black);
    centerTextOrigin(titleText);
    titleText.setPosition(sf::Vector2f(Config::WINDOW_WIDTH / 2.f, titleBaseY));

    // 2. スタート案内の設定
    promptText.setFillColor(sf::Color::White);
    centerTextOrigin(promptText);
    promptText.setPosition(sf::Vector2f(Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT * 0.65f));

    // 3. クレジット表記（画面下部）の設定
    creditText.setFillColor(sf::Color(150, 150, 150));
    centerTextOrigin(creditText);
    creditText.setPosition(sf::Vector2f(Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT * 0.9f));
}

void TitleScene::processInput()
{
    while (auto event = context->window->pollEvent())
    {

        if (event->is<sf::Event::Closed>())
        {
            context->window->close();
        }

        if (auto key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->scancode == sf::Keyboard::Scan::Enter)
            {
                requestSceneChange(SceneType::Game, 0, 0);

                // メモリを開放済みのため、メソッドを抜け出さないとエラーが発生する
                return;
            }
        }
    }
}

void TitleScene::update(float dt)
{
    elapsedTime += dt;

    // --- 演出 1: タイトルロゴの浮遊アニメーション ---
    // sin波を使って、基準となる高さ(titleBaseY)から上下に10ピクセルゆっくり揺らす
    float offsetY = std::sin(elapsedTime * 2.f) * 10.f;
    titleText.setPosition({titleText.getPosition().x, titleBaseY + offsetY});

    // --- 演出 2: スタート案内のフワフワ点滅 ---
    float alpha = (std::sin(elapsedTime * 5.f) * 0.5f + 0.5f) * 255.f;
    sf::Color color = promptText.getFillColor();
    color.a = static_cast<std::uint8_t>(alpha);
    promptText.setFillColor(color);
}

void TitleScene::draw()
{
    context->window->draw(titleText);
    context->window->draw(promptText);
    context->window->draw(creditText);
}

void TitleScene::centerTextOrigin(sf::Text &text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});
}