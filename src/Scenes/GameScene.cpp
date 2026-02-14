#include "Breakout/Scenes/GameScene.h"

GameScene::GameScene(SharedContext *ctx, std::function<void(SceneType, int)> changeCb)
    : Scene(ctx),
      requestSceneChange(changeCb),
      score(*(ctx->font)),
      playState(PlayState::Ready),
      readyTimer(2.0f), // 2秒間待機する
      readyText(*(ctx->font), "READY...", 40),
      controlsText(*(ctx->font), "MOVE A / D", 12)
{
    sf::Vector2f windowSize = sf::Vector2f(ctx->window->getSize());

    // 画面中央にボールを生成
    float centerX = ctx->window->getSize().x / 2.f;
    float centerY = ctx->window->getSize().y / 2.f;

    // エンティティの初期化
    ball = std::make_unique<Ball>(centerX, centerY);
    paddle = std::make_unique<Paddle>(centerX, 0.8 * (ctx->window->getSize().y));

    // ブロックを配置
    blockManager.createLevel(5, 10);
    readyText.setFillColor(sf::Color::Yellow);
    readyText.setOutlineThickness(3.f);
    readyText.setOutlineColor(sf::Color::Black);
    centerTextOrigin(readyText);
    readyText.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

    controlsText.setFillColor(sf::Color(180, 180, 180, 150));
    controlsText.setPosition({15.f, windowSize.y - 25.f});
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
            collisionManager.checkWallCollision(*ball, *context->window);
            collisionManager.checkPaddleCollision(*ball, *paddle);
            int destroyed = collisionManager.checkBlockCollision(*ball, blockManager);

            if (destroyed > 0)
            {
                score.add(destroyed);
            }

            score.updateText();
        }

        // ---ゲームオーバーに遷移---
        if (ball && ball->getPosition().y > context->window->getSize().y)
        {
            requestSceneChange(SceneType::GameClear, score.getValue());

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
            requestSceneChange(SceneType::GameClear, score.getValue());

            // メモリを開放済みのため、メソッドを抜け出さないとエラーが発生する
            return;
        }
    }
}

void GameScene::draw()
{
    sf::Text text(*(context->font), "THIS IS GAME SCENE", 30);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    text.setPosition(sf::Vector2f(context->window->getSize()) / 2.f);

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
        readyText.setPosition({context->window->getSize().x / 2.f, (context->window->getSize().y * 0.6f) + offsetY});

        context->window->draw(readyText);
    }
}

void GameScene::centerTextOrigin(sf::Text &text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});
}