#include <Breakout/UI/Score.h>
#include <sstream>
#include <iomanip> // std::setw, std::setfill 用

Score::Score(sf::Font &font) : value(0), stage(1), scoreText(font, "SCORE: 00000000", 20)
{
    // コンストラクタで1回だけフォントや色、位置を設定する
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(20.f, 20.f));
    scoreText.setOutlineThickness(2.f);
    scoreText.setOutlineColor(sf::Color::Black);

    // 初期の文字列をセット
    updateText();
}

void Score::updateText()
{
    // C++標準のストリーム操作でゼロ埋め（8桁）を行う
    std::stringstream ss;
    ss << "SCORE: " << std::setw(8) << std::setfill('0') << value;
    scoreText.setString(ss.str());
}

void Score::add(int destroyedBlocks)
{
    // ステージが進むほど獲得スコアが増えるような計算式
    value += (BASE_POINT * stage) * destroyedBlocks;
}

void Score::upStage()
{
    stage++;
}

void Score::reset()
{
    value = 0;
    stage = 1;
}

int Score::getValue()
{
    return value;
}

void Score::draw(sf::RenderWindow &window)
{
    window.draw(scoreText);
}