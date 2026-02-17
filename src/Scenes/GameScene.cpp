#include <cmath>
#include "Breakout/Constants.h"
#include "Breakout/Scenes/GameScene.h"

GameScene::GameScene(SharedContext *ctx, std::function<void(SceneType, int, int)> changeCb, int s, int st)
    : Scene(ctx),
      requestSceneChange(changeCb),
      score(*(ctx->font)),
      currentStage(st),
      playState(PlayState::Ready),
      readyTimer(2.0f), // 2秒間待機する
      readyText(*(ctx->font), "READY...", Config::FONT_SIZE_SUBTITLE),
      controlsText(*(ctx->font), "MOVE A / D", Config::FONT_SIZE_SMALL)
{
    // 画面中央にボールを生成
    float centerX = Config::WINDOW_WIDTH / 2.f;
    float centerY = Config::WINDOW_HEIGHT / 2.f;

    // エンティティの初期化
    ball = std::make_unique<Ball>(centerX, centerY, currentStage);
    paddle = std::make_unique<Paddle>(centerX, Config::WINDOW_HEIGHT - Config::PADDLE_Y_OFFSET);

    score.setScore(s);
    score.updateText();

    // ブロックを配置
    blockManager.createLevel(4, 6);
    readyText.setFillColor(sf::Color::Yellow);
    readyText.setOutlineThickness(Config::FONT_SIZE_OUTLINE_SUBTITLE);
    readyText.setOutlineColor(sf::Color::Black);
    centerTextOrigin(readyText);
    readyText.setPosition(sf::Vector2f(Config::WINDOW_WIDTH / 2.f, Config::WINDOW_HEIGHT / 2.f));

    controlsText.setFillColor(sf::Color(180, 180, 180, 150));
    controlsText.setPosition({15.f, Config::WINDOW_HEIGHT - 25.f});
}

void GameScene::processInput()
{
    while (auto event = context->window->pollEvent())
    {

        if (event->is<sf::Event::Closed>())
        {
            context->window->close();
        }

        // ---バドル操作---
        float moveDir = 0.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            moveDir = -1.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            moveDir = 1.f;
        }

        if (paddle)
        {
            paddle->setDirection(moveDir);
        }
    }
}

void GameScene::update(float dt)
{
    if (playState == PlayState::Ready)
    {
        readyTimer -= dt; // タイマーを減らす

        // プレイヤーが準備できるように、パドルだけは動かせるようにする（UXの向上）
        if (paddle)
            paddle->update(dt);

        // 2秒経過したらプレイ開始！
        if (readyTimer <= 0.f)
        {
            playState = PlayState::Playing;
        }
    }

    else if (playState == PlayState::Playing)
    {
        if (ball)
        {
            ball->update(dt);
        }

        if (paddle)
        {
            paddle->update(dt);
        }

        if (ball && paddle)
        {
            collisionManager.checkWallCollision(*ball);
            collisionManager.checkPaddleCollision(*ball, *paddle);
            int destroyed = collisionManager.checkBlockCollision(*ball, blockManager);

            if (destroyed > 0)
            {
                score.add(destroyed, currentStage);
            }

            score.updateText();
        }

        // ---ゲームオーバーに遷移---
        if (ball && ball->getPosition().y > Config::WINDOW_HEIGHT)
        {
            requestSceneChange(SceneType::GameClear, score.getValue(), currentStage);

            // メモリを開放済みのため、メソッドを抜け出さないとエラーが発生する
            return;
        }

        //---ゲームクリアに遷移（一時的）---
        bool cleared = true;
        for (auto const &block : blockManager.getBlocks())
        {
            if (!block.isDestroyed())
            {
                cleared = false;
                break;
            }
        }
        if (cleared)
        {
            requestSceneChange(SceneType::Game, score.getValue(), currentStage + 1);

            // メモリを開放済みのため、メソッドを抜け出さないとエラーが発生する
            return;
        }
    }
}

void GameScene::draw()
{
    if (ball)
        ball->draw(*(context->window));

    if (paddle)
        paddle->draw(*(context->window));

    blockManager.draw(*(context->window));
    score.draw(*(context->window));
    context->window->draw(controlsText);

    if (playState == PlayState::Ready)
    {
        // 少しフワフワさせる演出（TitleSceneの応用）
        float offsetY = std::sin(readyTimer * 10.f) * 5.f;
        readyText.setPosition({Config::WINDOW_WIDTH / 2.f, (context->window->getSize().y * 0.6f) + offsetY});

        context->window->draw(readyText);
    }
}

void GameScene::centerTextOrigin(sf::Text &text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});
}