// library
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include <chrono>

// window constant
constexpr unsigned int WINDOW_W = 800;
constexpr unsigned int WINDOW_H = 600;
constexpr sf::Color WINDOW_COLOR = sf::Color(64, 64, 64);

// block constant
constexpr float BLOCK_HEIGHT_COEF = 0.15f;
constexpr float BLOCK_OUTLINE = -5.f;
constexpr float RESISTANT = 0.f;
constexpr int COLS = 4;
constexpr int ROWS = 7;
constexpr float BLOCK_WIDTH = 80.f;
constexpr float BLOCK_HEIGHT = 40.f;

// time coefficient
constexpr float TIME_COEF = 100.f;

// ball constant
constexpr int COLLITION_CONST = 0;
constexpr float RADIUS = 10.f;
constexpr float VELOCITY_UP = 15.f;
constexpr float VECOCITY_LOW = 7.f;
constexpr float VELOCITY_PER_STAGE = 1.f;
constexpr float ACCEL = 0.05f;
constexpr float NORM_COEF = 5.f;
constexpr sf::Color BALL_COLOR = sf::Color(0, 170, 255);

// bar constant
constexpr float EXTEND = RADIUS * 1.2f;
constexpr float BAR_HEIGHT_COEF = 0.9;
constexpr float DX_COEF = 0.1;
constexpr float DY = -2.f;
constexpr float BAR_WIDTH = 200.f;
constexpr float BAR_HEIGHT = 25.f;

// text constant
constexpr float TEXT_OUTLINE = 10.f;

class Bar;
class Block;
class Blocks;
class Ball;

enum class GameState
{
    Title,
    Game,
    GameOver,
    End
};

float iou1d(float a1, float a2, float b1, float b2)
{

    float i, u;
    i = std::min(std::max(a2 - b1, 0.f), std::max(b2 - a1, 0.f));
    u = (a2 - a1) + (b2 - b1) - i;

    return i / u;
}

float sign(float x)
{
    if (x > 0)
        return 1.f;
    else if (x < 0)
        return -1.f;
    else
        return 0.f;
}

class Bar
{
public:
    sf::Vector2f position = sf::Vector2f({WINDOW_W / 2.f, WINDOW_H / 2.f});
    sf::Vector2f position_prev;
    sf::Vector2f vector = sf::Vector2f(0.f, 1.f);

    float w, h;

    Bar(float w, float h)
    {
        this->w = w;
        this->h = h;
    }

    void Update(sf::RenderWindow &window)
    {
        auto mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));
        position_prev = position;
        position = sf::Vector2f({mouse_position.x, window.getSize().y * BAR_HEIGHT_COEF});

        if (position.x < w / 2.f)
            position.x = w / 2.f;

        else if (position.x > window.getSize().x - w / 2.f)
            position.x = window.getSize().x - w / 2.f;

        float dx = (position.x - position_prev.x) * DX_COEF;
        vector = sf::Vector2f(dx, DY);
    }

    void Draw(sf::RenderWindow &window, sf::RectangleShape &shape)
    {
        shape.setSize({w, h});
        shape.setOutlineThickness(-5.f);
        shape.setOutlineColor(sf::Color(200, 200, 200));
        shape.setOrigin({w / 2.f, h / 2.f});
        shape.setPosition(position);
        window.draw(shape);
    }

    void upStage()
    {
        this->position = sf::Vector2f({WINDOW_W / 2.f, this->position.y});
        this->vector = sf::Vector2f(0.f, 1.f);
    }
};

class Block
{
public:
    bool isExist = true;
    float width, height;
    float x1, y1, x2, y2;

    Block(float width, float height, float x1, float y1)
    {
        this->width = width;
        this->height = height;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x1 + width;
        this->y2 = y1 + height;
    }
};

class Ball
{
public:
    // position
    sf::Vector2f position = sf::Vector2f(WINDOW_W / 2.f, WINDOW_H * 0.8f);
    sf::Vector2f vector = sf::Vector2f(0.f, 1.f);
    float radius;
    float velocity = VECOCITY_LOW;
    float velocity_low = VECOCITY_LOW;
    float velocity_up = VELOCITY_UP;

    bool collision = false;

    Ball(float radius)
    {
        this->radius = radius;
    }

    void Update(sf::RenderWindow &window, Bar &bar)
    {
        if (this->velocity < this->velocity_low)
            this->velocity = this->velocity_low;

        else if (this->velocity > this->velocity_up)
            this->velocity = velocity_up;

        else
            this->velocity -= ACCEL;

        position = position + velocity * vector;
    }

    void Draw(sf::RenderWindow &window, sf::CircleShape shape)
    {
        shape.setRadius(radius);
        shape.setOrigin({radius, radius});
        shape.setPosition(position);
        shape.setFillColor(sf::Color(200, 200, 200));
        window.draw(shape);
    }

    std::vector<float> bbox()
    {
        std::vector<float> box(4, 0);
        box.at(0) = position.x - radius * 1.1f;
        box.at(1) = position.y - radius * 1.1f;
        box.at(2) = position.x + radius * 1.1f;
        box.at(3) = position.y + radius * 1.1f;

        return box;
    }

    void reflectX(float pos)
    {
        this->vector.x = this->vector.x * -1.f;
        position.x = pos + this->radius * sign(this->vector.x);
    }

    void reflectY(float pos)
    {
        this->vector.y = this->vector.y * -1.f;
        position.y = pos + this->radius * sign(this->vector.y);
    }

    void reflectBar(float vec_x)
    {
        if (vector.y > 0)
            vector.y = vector.y * -1.f;

        vector.x += vec_x;

        float norm = std::sqrt(this->vector.x * this->vector.x + this->vector.y * this->vector.y);
        this->vector = sf::Vector2f({this->vector.x / norm, this->vector.y / norm});
        this->velocity = norm * NORM_COEF;
    }

    void addVector(sf::Vector2f vec)
    {
        this->vector = this->vector + vec;

        float norm = std::sqrt(this->vector.x * this->vector.x + this->vector.y * this->vector.y);
        this->vector = sf::Vector2f({this->vector.x / norm, this->vector.y / norm});
    }

    bool outOfScreen(sf::RenderWindow &window)
    {
        if (position.y > window.getSize().y)
            return true;
        else
            return false;
    }

    void upStage()
    {
        this->velocity_low += VELOCITY_PER_STAGE;
        this->velocity_up += VELOCITY_PER_STAGE;
        this->position = sf::Vector2f(WINDOW_W / 2.f, WINDOW_H * 0.8f);
        this->vector = sf::Vector2f(0.f, 1.f);
    }
};

class Blocks
{
public:
    float width, height;
    sf::Vector2f offset;
    std::vector<std::vector<Block>> array;
    sf::Color color;

    Blocks(int col, int row, float width, float height, sf::RenderWindow &window)
    {

        this->width = width;
        this->height = height;

        for (int i = 0; i < col; i++)
        {
            float y = height * i;
            std::vector<Block> row_block;

            for (int j = 0; j < row; j++)
            {
                float x = width * j;
                Block block(width, height, x, y);
                row_block.push_back(block);
            }

            array.push_back(row_block);
        }

        float offset_x = (window.getSize().x / 2.f) - width * ((array.at(0).size() - 1) / 2) - width / 2.f;
        float offset_y = window.getSize().y * BLOCK_HEIGHT_COEF;
        this->offset = sf::Vector2f({offset_x, offset_y});

        this->color = BALL_COLOR;
    }

    void Update(sf::RenderWindow &window, Ball &ball)
    {
        float offset_x = (window.getSize().x / 2.f) - width * ((array.at(0).size() - 1) / 2) - width / 2.f;
        float offset_y = window.getSize().y * BLOCK_HEIGHT_COEF;

        this->offset = sf::Vector2f({offset_x, offset_y});
    }

    void Draw(sf::RenderWindow &window, sf::RectangleShape &shape)
    {
        shape.setSize({width, height});
        shape.setOrigin({0, 0});
        shape.setOutlineThickness(BLOCK_OUTLINE);
        shape.setOutlineColor(WINDOW_COLOR);
        shape.setFillColor(this->color);

        for (int i = 0; i < array.size(); i++)
        {
            for (int j = 0; j < array.at(i).size(); j++)
            {
                Block block = array.at(i).at(j);
                if (block.isExist)
                {
                    shape.setPosition({block.x1 + this->offset.x, block.y1 + this->offset.y});
                    window.draw(shape);
                }
            }
        }
    }

    int RemainBlocks()
    {
        int cnt = 0;
        for (int i = 0; i < array.size(); i++)
        {
            for (int j = 0; j < array.at(i).size(); j++)
            {
                if (array.at(i).at(j).isExist)
                    cnt++;
            }
        }

        return cnt;
    }

    void Reset()
    {
        for (int i = 0; i < array.size(); i++)
        {
            for (int j = 0; j < array[i].size(); j++)
            {
                this->array[i][j].isExist = true;
            }
        }
    }

    void chageColor()
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> dis(0, 255);
        int red = dis(gen);
        int green = dis(gen);
        int blue = dis(gen);
        this->color = sf::Color(red, green, blue);
    }
};

class Button
{
public:
    sf::RectangleShape shape;
    sf::Font font;
    std::string str;

    sf::Vector2f position;

    bool isButtonPressed = false;
    bool isButtonReleased = false;

    Button(sf::Font &font, const std::string &str, sf::RenderWindow &window)
    {
        this->position = sf::Vector2f({window.getSize().x / 2.f, window.getSize().y / 2.f});

        this->shape = sf::RectangleShape({window.getSize().x / 4.f, window.getSize().y / 6.f});
        this->shape.setOrigin(this->shape.getGeometricCenter());
        this->shape.setPosition(this->position);

        this->font = font;
        this->str = str;
    }

    bool Update(sf::RenderWindow &window)
    {
        auto mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));
        if (shape.getGlobalBounds().contains(mouse_position))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                shape.setFillColor(sf::Color::Red);
                this->isButtonPressed = true;
            }

            else
            {
                if (this->isButtonPressed)
                    this->isButtonReleased = true;

                shape.setFillColor(BALL_COLOR);
                this->isButtonPressed = false;
            }
        }
        else
        {
            shape.setFillColor(sf::Color::White);
            this->isButtonPressed = false;
            this->isButtonReleased = false;
        }

        return this->isButtonReleased;
    }

    void Draw(sf::RenderWindow &window)
    {

        sf::Text text(this->font, this->str);
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x / 2,
                        static_cast<float>(text.getCharacterSize()) * 0.5f});
        text.setPosition(this->position);
        text.setOutlineThickness(TEXT_OUTLINE);
        text.setOutlineColor(BALL_COLOR);

        window.draw(this->shape);
        window.draw(text);
    }

    void setPosition(sf::Vector2f pos)
    {
        this->position = pos;
        this->shape.setPosition(this->position);
    }
};

class Score
{
private:
    int stage = 1;
    int value;
    int base = 5;

public:
    Score(int value)
    {
        this->value = value;
    }

    std::string getValue()
    {
        std::string str;
        str = std::to_string(this->value);
        str.insert(0, 8 - str.length(), '0');
        return str;
    }

    void addValue()
    {
        this->value += (base * this->stage) * stage;
    }

    void upStage()
    {
        this->stage++;
    }

    void reset()
    {
        this->value = 0;
        this->stage = 1;
    }
};

void collision(sf::RenderWindow &window, Bar &bar, Blocks &blocks, Ball &ball, Score &score)
{

    // block conflict
    std::pair<int, int> max_iou_block = {-1, -1};
    float max_iou = 0;

    for (int i = 0; i < blocks.array.size(); i++)
    {
        for (int j = 0; j < blocks.array.at(i).size(); j++)
        {
            auto *block = &blocks.array.at(i).at(j);
            if (block->isExist)
            {
                float x_iou = iou1d(block->x1 + blocks.offset.x, block->x2 + blocks.offset.x, ball.bbox().at(0), ball.bbox().at(2));
                float y_iou = iou1d(block->y1 + blocks.offset.y, block->y2 + blocks.offset.y, ball.bbox().at(1), ball.bbox().at(3));

                if ((x_iou > 0.f) && (y_iou > 0.f))
                {
                    if (x_iou + y_iou > max_iou)
                    {
                        max_iou = x_iou + y_iou;
                        max_iou_block = {j, i};
                    }
                }
            }
        }
    }

    if ((max_iou_block.first > -1) && (max_iou_block.second > -1))
    {
        int i = max_iou_block.second;
        int j = max_iou_block.first;

        bool x_conflict = false;
        bool y_conflict = false;

        auto *block = &blocks.array.at(i).at(j);

        std::pair<int, int> hit_block = {-1, -1};

        // y
        if (ball.vector.y >= 0)
            hit_block.second = static_cast<int>((ball.bbox().at(3) - blocks.offset.y) / blocks.height);

        else if (ball.vector.y < 0)
            hit_block.second = static_cast<int>((ball.bbox().at(1) - blocks.offset.y) / blocks.height);

        // x
        if (ball.vector.x >= 0)
            hit_block.first = static_cast<int>((ball.bbox().at(2) - blocks.offset.x) / blocks.width);

        else if (ball.vector.x < 0)
            hit_block.first = static_cast<int>((ball.bbox().at(0) - blocks.offset.x) / blocks.width);

        if (max_iou_block.first == hit_block.first)
            x_conflict = true;

        if (max_iou_block.second == hit_block.second)
            y_conflict = true;

        if (x_conflict && y_conflict)
        {
            float x_iou = iou1d(block->x1 + blocks.offset.x, block->x2 + blocks.offset.x, ball.bbox().at(0), ball.bbox().at(2));
            float y_iou = iou1d(block->y1 + blocks.offset.y, block->y2 + blocks.offset.y, ball.bbox().at(1), ball.bbox().at(3));

            if (x_iou < y_iou)
                y_conflict = false;
            else if (x_iou > y_iou)
                x_conflict = false;
        }

        if (block->isExist)
        {
            if (ball.velocity > RESISTANT)
                block->isExist = false;

            if (x_conflict && y_conflict)
            {
                float pos_x;
                if (std::abs(block->x1 + blocks.offset.x - ball.position.x) < std::abs(block->x2 + blocks.offset.x - ball.position.x))
                    pos_x = block->x1 + blocks.offset.x;
                else
                    pos_x = block->x2 + blocks.offset.x;
                ball.reflectX(pos_x);
                score.addValue();

                float pos_y;
                if (std::abs(block->y1 + blocks.offset.y - ball.position.y) < std::abs(block->y2 + blocks.offset.y - ball.position.y))
                    pos_y = block->y1 + blocks.offset.y;
                else
                    pos_y = block->y2 + blocks.offset.y;
                ball.reflectY(pos_y);
                score.addValue();
            }
            else if (x_conflict)
            {
                float pos;
                if (std::abs(block->x1 + blocks.offset.x - ball.position.x) < std::abs(block->x2 + blocks.offset.x - ball.position.x))
                    pos = block->x1 + blocks.offset.x;
                else
                    pos = block->x2 + blocks.offset.x;
                ball.reflectX(pos);
                score.addValue();
            }
            else if (y_conflict)
            {
                float pos;
                if (std::abs(block->y1 + blocks.offset.y - ball.position.y) < std::abs(block->y2 + blocks.offset.y - ball.position.y))
                    pos = block->y1 + blocks.offset.y;
                else
                    pos = block->y2 + blocks.offset.y;
                ball.reflectY(pos);
                score.addValue();
            }
        }
    }

    // bar conflict
    if ((bar.position.x - (bar.w + EXTEND) / 2.f < ball.position.x && ball.position.x < bar.position.x + (bar.w + EXTEND) / 2.f) &&
        (bar.position.y - bar.h / 2.f < ball.position.y && ball.position.y < bar.position.y + bar.h / 2.f))
    {

        ball.collision = true;
        ball.addVector(bar.vector);

        return;
    }

    // wall condition
    else if ((ball.position.x > window.getSize().x))
    {
        ball.position.x = window.getSize().x - ball.radius * 1.5f;
        if (ball.collision)
            return;
        else
            ball.collision = true;

        ball.reflectX(window.getSize().x);

        return;
    }

    else if ((ball.position.x < 0))
    {
        ball.position.x = ball.radius * 1.5f;
        if (ball.collision)
            return;
        else
            ball.collision = true;

        ball.reflectX(0.f);

        return;
    }

    else if ((ball.position.y < 0))
    {
        ball.position.y = ball.radius * 1.5f;
        if (ball.collision)
            return;
        else
            ball.collision = true;

        ball.reflectY(0.f);

        return;
    }

    else
        ball.collision = false;
}

// ★修正: 引数に window と font を追加
GameState drawTitle(sf::RenderWindow &window, sf::Font &font)
{
    GameState state = GameState::Title;

    sf::Text text(font, "PRESS START BUTTOM");
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.position.x + bounds.size.x / 2,
                    static_cast<float>(text.getCharacterSize()) * 0.75f});
    text.setPosition({WINDOW_W / 2.f, WINDOW_H * 0.3f});
    text.setOutlineThickness(TEXT_OUTLINE);
    text.setOutlineColor(BALL_COLOR);

    Button start_button(font, "START", window);

    // window loop
    while (state == GameState::Title)
    {

        // handle events
        while (auto event = window.pollEvent())
        {
            // on close button release
            if (event->is<sf::Event::Closed>())
            {
                state = GameState::End;
            }

            // on window resize
            else if (auto resized = event->getIf<sf::Event::Resized>())
            {
                // update view
                window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(resized->size))));
            }

            if (start_button.Update(window))
            {
                state = GameState::Game;
            }

            // fill window with color
            window.clear(WINDOW_COLOR);
            // window.draw(bg_sp);

            window.draw(text);
            start_button.Draw(window);

            // update display
            window.display();
        }
    }
    return state;
}

// ★修正: 引数に window と font を追加
GameState drawGame(sf::RenderWindow &window, sf::Font &font, Score &score)
{
    GameState state = GameState::Game;

    sf::Text text(font, "", 35);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.position.x + bounds.size.x / 2,
                    static_cast<float>(text.getCharacterSize()) * 0.75f});
    text.setPosition({window.getSize().x * 0.5f, window.getSize().y * 0.1f});
    text.setOutlineThickness(TEXT_OUTLINE);
    text.setOutlineColor(BALL_COLOR);

    sf::RectangleShape bar_shape;
    sf::RectangleShape block_shape;
    sf::CircleShape ball_shape;

    Bar bar(BAR_WIDTH, BAR_HEIGHT);
    Blocks blocks(COLS, ROWS, BLOCK_WIDTH, BLOCK_HEIGHT, window);
    Ball ball(RADIUS);
    score.reset();

    // disable key repeat
    window.setKeyRepeatEnabled(false);

    // start clock
    sf::Clock clock;
    sf::Clock startClock;

    // window loop
    while (state == GameState::Game)
    {
        // delta time
        float dt = clock.getElapsedTime().asSeconds();
        if (dt < 1.f / 60.f)
            continue;

        clock.restart();

        // handle events
        while (auto event = window.pollEvent())
        {
            // on close button release
            if (event->is<sf::Event::Closed>())
            {
                state = GameState::End;
            }

            // on window resize
            else if (auto resized = event->getIf<sf::Event::Resized>())
            {
                // update view
                window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(resized->size))));
            }
        }
        collision(window, bar, blocks, ball, score);
        bar.Update(window);
        ball.Update(window, bar);
        blocks.Update(window, ball);

        text.setString(score.getValue());
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x / 2,
                        static_cast<float>(text.getCharacterSize()) * 0.75f});
        text.setPosition({window.getSize().x * 0.5f, window.getSize().y * 0.1f});
        text.setOutlineThickness(0.f);
        text.setOutlineColor(sf::Color(200, 200, 200));

        if (ball.outOfScreen(window))
        {
            state = GameState::GameOver;
            break;
        }

        if (blocks.RemainBlocks() == 0)
        {
            blocks.Reset();
            blocks.chageColor();
            score.upStage();
            ball.upStage();

            sf::Text timer(font, "", 40);
            timer.setOutlineThickness(0.f);

            clock.restart();
            float time = 0.f;
            while (time < 3.f)
            {
                auto event = window.pollEvent();
                timer.setString("Stage Clear!\nNext stage in " + std::to_string(3 - static_cast<int>(time)));
                sf::FloatRect bounds = timer.getLocalBounds();
                timer.setOrigin({bounds.position.x + bounds.size.x / 2, static_cast<float>(timer.getCharacterSize()) * 0.75f});
                timer.setPosition({window.getSize().x * 0.5f, window.getSize().y * 0.6f});

                bar.Update(window);

                window.clear(WINDOW_COLOR);
                ball.Draw(window, ball_shape);
                bar.Draw(window, bar_shape);
                blocks.Draw(window, block_shape);
                window.draw(text);
                window.draw(timer);

                window.display();
                time = clock.getElapsedTime().asSeconds();
            }
        }

        if (startClock.getElapsedTime().asSeconds() < 3.f)
        {
            sf::Text timer(font, "", 40);
            timer.setOutlineThickness(0.f);

            int time = startClock.getElapsedTime().asSeconds();
            while (time < 3.f)
            {
                auto event = window.pollEvent();
                timer.setString(std::to_string(3 - time));
                sf::FloatRect bounds = timer.getLocalBounds();
                timer.setOrigin({bounds.position.x + bounds.size.x / 2, static_cast<float>(timer.getCharacterSize()) * 0.75f});
                timer.setPosition({window.getSize().x * 0.5f, window.getSize().y * 0.5f});

                bar.Update(window);

                window.clear(WINDOW_COLOR);
                ball.Draw(window, ball_shape);
                bar.Draw(window, bar_shape);
                blocks.Draw(window, block_shape);
                window.draw(text);
                window.draw(timer);

                window.display();

                time = startClock.getElapsedTime().asSeconds();
            }
        }

        // fill window with color
        window.clear(WINDOW_COLOR);
        // window.draw(bg_sp);

        bar.Draw(window, bar_shape);
        blocks.Draw(window, block_shape);
        ball.Draw(window, ball_shape);
        window.draw(text);

        // update display
        window.display();
    }

    return state;
}

// ★修正: 引数に window と font を追加
GameState drawGameOver(sf::RenderWindow &window, sf::Font &font, Score &score)
{
    GameState state = GameState::GameOver;

    Button retry_button(font, "RETRY", window);
    retry_button.setPosition(sf::Vector2f({WINDOW_W * 0.3f, WINDOW_H * 0.5f}));

    Button quit_button(font, "QUIT", window);
    quit_button.setPosition(sf::Vector2f({WINDOW_W * 0.7f, WINDOW_H * 0.5f}));

    // window loop
    while (state == GameState::GameOver)
    {
        // handle events
        while (auto event = window.pollEvent())
        {
            // on close button release
            if (event->is<sf::Event::Closed>())
            {
                state = GameState::End;
            }

            // on window resize
            else if (auto resized = event->getIf<sf::Event::Resized>())
            {
                // update view
                window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(resized->size))));
            }
        }

        if (retry_button.Update(window))
        {
            state = GameState::Game;
        }

        if (quit_button.Update(window))
        {
            state = GameState::End;
        }

        // fill window with color
        window.clear(WINDOW_COLOR);
        // window.draw(bg_sp);

        sf::Text text(font);
        text.setString("Game Over");
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x / 2,
                        static_cast<float>(text.getCharacterSize()) * 0.75f});
        text.setPosition({WINDOW_W / 2.f, WINDOW_H * 0.2f});
        text.setOutlineThickness(TEXT_OUTLINE);
        text.setOutlineColor(BALL_COLOR);
        window.draw(text);

        text.setString("Score : " + score.getValue());
        bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x / 2,
                        static_cast<float>(text.getCharacterSize()) * 0.75f});
        text.setPosition({WINDOW_W / 2.f, WINDOW_H * 0.3f});
        text.setOutlineThickness(TEXT_OUTLINE);
        text.setOutlineColor(BALL_COLOR);
        window.draw(text);

        retry_button.Draw(window);
        quit_button.Draw(window);

        // update display
        window.display();
    }

    return state;
}

// main program
int main()
{
    // ★修正: main関数内で宣言（寿命管理をmainスコープ内にする）
    sf::Font font("/Users/taiga/Library/Fonts/PressStart2P-Regular.ttf");
    sf::RenderWindow window(sf::VideoMode({WINDOW_W, WINDOW_H}), "BREAKOUT");

    GameState state = GameState::Title;
    Score score(0);

    while (true)
    {
        if (state == GameState::Title)
            state = drawTitle(window, font);

        else if (state == GameState::Game)
            state = drawGame(window, font, score);

        else if (state == GameState::GameOver)
            state = drawGameOver(window, font, score);

        else if (state == GameState::End)
            break;
    }

    window.close();
    return 0;
}