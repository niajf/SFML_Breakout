#include "Breakout/Scenes/GameClearScene.h"
#include <sstream>
#include <iomanip>
#include <cstdint>

GameClearScene::GameClearScene(SharedContext *ctx, std::function<void(SceneType, int)> changeCb, int score)
    : Scene(ctx),
      requestSceneChange(changeCb),
      finalScore(score),
      elapsedTime(0.f),
      clearText(*(ctx->font), "GAME OVER!", 50),
      scoreText(*(ctx->font), "", 30),
      promptText(*(ctx->font), "PRESS ENTER TO NEXT GAME", 20)
{
    sf::Vector2f windowSize = sf::Vector2f(ctx->window->getSize());

    // 1. 背景の半透明オーバーレイ設定
    overlay.setSize(windowSize);
    overlay.setFillColor(sf::Color(0, 0, 0, 150)); // R, G, B, Alpha(透明度)

    // 2. 「STAGE CLEAR!」の設定
    clearText.setFillColor(sf::Color::Yellow);
    clearText.setOutlineThickness(3.f);
    clearText.setOutlineColor(sf::Color::Black);
    centerTextOrigin(clearText);
    clearText.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y * 0.3f)); // 画面上部寄り

    // 3. スコアテキストの設定
    std::stringstream ss;
    ss << "SCORE: " << std::setw(8) << std::setfill('0') << finalScore;
    scoreText.setString(ss.str());
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineThickness(2.f);
    scoreText.setOutlineColor(sf::Color::Black);
    centerTextOrigin(scoreText);
    scoreText.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y * 0.5f)); // 画面中央

    // 4. 操作案内テキストの設定
    promptText.setFillColor(sf::Color::White);
    centerTextOrigin(promptText);
    promptText.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y * 0.7f)); // 画面下部寄り
}

void GameClearScene::processInput()
{
    while (auto event = context->window->pollEvent())
    {

        if (event->is<sf::Event::Closed>())
        {
            context->window->close();
        }

        if (elapsedTime > 2.5f)
        {
            if (auto key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->scancode == sf::Keyboard::Scan::Enter)
                {
                    requestSceneChange(SceneType::Game, 0);

                    // メモリを開放済みのため、メソッドを抜け出さないとエラーが発生する
                    return;
                }
            }
        }
    }
}

void GameClearScene::update(float dt)
{
    elapsedTime += dt; // タイマーを進める

    // 2.5秒以降、案内テキストをフワフワ点滅させる（サイン波を使用）
    if (elapsedTime > 2.5f)
    {
        // sin関数は -1.0 〜 1.0 の値になるため、調整して 0.0 〜 1.0 にする
        // 時間に掛ける値（ここでは 5.f）を大きくすると点滅が速くなる
        float alpha = (std::sin(elapsedTime * 5.f) * 0.5f + 0.5f) * 255.f;

        // 透明度だけを更新
        sf::Color color = promptText.getFillColor();
        color.a = static_cast<std::uint8_t>(alpha);
        promptText.setFillColor(color);
    }
}

void GameClearScene::draw()
{
    // 1. まず背景を半透明の黒で覆う
    context->window->draw(overlay);

    // 2. 0.5秒以降なら「STAGE CLEAR」を描画
    if (elapsedTime > 0.5f)
    {
        context->window->draw(clearText);
    }

    // 3. 1.5秒以降ならスコアを描画
    if (elapsedTime > 1.5f)
    {
        context->window->draw(scoreText);
    }

    // 4. 2.5秒以降なら「NEXT / TITLE」の操作案内を描画
    if (elapsedTime > 2.5f)
    {
        context->window->draw(promptText);
    }
}

// 文字列の中心を基準点（Origin）に設定する便利関数
void GameClearScene::centerTextOrigin(sf::Text &text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    // フォントの余白を考慮した正確な中心をセットする
    text.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});
}