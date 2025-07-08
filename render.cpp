#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <cmath>
#include <boost/format.hpp>

#include "render.h"
#include "source.h"
#include "setting.h"
#include "layout.h"
#include "sandData.h"
#include "placement.h"
#include "stat.h"

namespace render
{
    // @brief 渲染器基类，无实际功能
    // @warning 子类必须实现 void render(sf::RenderWindow* window)
    class Renderer
    {
    protected:
        sf::IntRect getTextureRect(sf::Sprite& s, int y)
        {
            int top = std::max(-y, 0);
            int bottom = std::min(-y + (int)layout::inGame::color.getSize().y, (int)s.getTexture()->getSize().y);
            if (top >= bottom)
                return sf::IntRect(0, 0, 0, 0);
            return sf::IntRect(
                0,
                top,
                s.getTexture()->getSize().x,
                bottom - top
            );
        }

        void renderFPS(sf::RenderWindow* window)
        {
            using boost::format;

            sf::Text fps(
                (format("FPS: %.1f TPS: %.1f") % status::fps % status::tps).str(),
                source::renderFont,
                15U
            );
            fps.setFillColor(sf::Color(0x222222FF));
            fps.setOrigin({ 0.0f, fps.getLocalBounds().height });
            fps.setPosition(10, windowH-10);
            window->draw(fps);
        }

        void renderBackground(sf::RenderWindow* window)
        {
            static float offset;
            offset += 0.25;
            offset = offset > 25 ? offset - 25 : offset;
            window->draw(source::bg);
            source::bg.setPosition({ -offset, -offset });
        }

    public:
        // @brief 在给定窗口上进行渲染
        // @note 子类自行实现
        virtual void render(sf::RenderWindow* window) {}
    };

    // @brief 用于渲染标题界面
    class StartRenderer : public Renderer
    {
        sf::Sprite scaledLogo;
        sf::Text optionMark;
        std::vector<sf::Text> modeTexts;

        void renderTitle(sf::RenderWindow* window)
        {
            window->draw(scaledLogo);
        }

        void renderModeOptions(sf::RenderWindow* window)
        {
            for (int i = 0; i < modeTexts.size(); i++)
            {
                //float x = i == status::curMode ? optionMark.getGlobalBounds().getSize().x / 2 : 0;
                float x = 0;
                float y = i * modeTexts[0].getLocalBounds().getSize().y * 2.5f;
                if (i == status::curMode)
                {
                    const float markWidth = optionMark.getGlobalBounds().getSize().x;
                    x = markWidth * 1.5f / 2;
                    optionMark.setPosition(layout::start::mode.getAbsPos({ x - markWidth * 1.5f, y }));
                    window->draw(optionMark);
                }
                modeTexts[i].setPosition(layout::start::mode.getAbsPos({ x, y }));
                window->draw(modeTexts[i]);
            }
        }

        void renderHighScore(sf::RenderWindow* window)
        {
            using boost::format;

            std::string score = (format("HIGH: %08d") % statistics::highScore[status::curMode]).str();
            sf::Text text(score, source::renderFont, 50U);
            text.setFillColor(sf::Color::Black);
            text.move(layout::start::score.getAbsPos({ 0,0 }));
            window->draw(text);
        }

    public:
        StartRenderer()
        {
            scaledLogo = source::logo;
            scaledLogo.setScale({
                layout::start::title.getSize().x / (float)source::logo.getTexture()->getSize().x,
                layout::start::title.getSize().y / (float)source::logo.getTexture()->getSize().y
                });
            scaledLogo.setPosition(layout::start::title.getAbsPos({ 0,0 }));

            optionMark = sf::Text(">", source::renderFont, 50U);
            optionMark.setFillColor(sf::Color::Black);

            for (auto op : { "INFINITE", "SPEEDRUN", "SURVIVAL" })
            {
                sf::Text tmp = sf::Text(op, source::renderFont, 50U);
                tmp.setFillColor(sf::Color::Black);
                auto tmp2 = tmp.getGlobalBounds().getSize();
                modeTexts.push_back(tmp);
            }
        }

        void render(sf::RenderWindow* window)
        {
            renderBackground(window);
            renderFPS(window);

            renderTitle(window);
            renderModeOptions(window);
            renderHighScore(window);
        }
    };

    // @brief 用于在游戏时进行渲染
    class InGameRenderer : public Renderer
    {
    protected:
        void renderGhost(sf::RenderWindow* window)
        {
            shape::Shape& curShape = placement::curShape;
            const int blockSize = placement::blockSize * render::sandSize;
            int ghostX = placement::getPlacementX(window) * render::sandSize;

            sf::Color ghostC = sand::constants::LIGHT[placement::curType]->renderShape.getFillColor();
            ghostC.a = (int)std::min(
                placement::sinceLastPlacement() / placement::placeCD * 200,
                200.0f
            ); // 让提示虚影随cd恢复逐渐变得不透明

            auto s = sf::RectangleShape({ blockSize,  blockSize });
            s.setFillColor(ghostC);

            for (int i = 0; i < curShape.w; i++)
                for (int j = 0; j < curShape.h; j++)
                    if (curShape.data[i][j])
                    {
                        s.setPosition(layout::inGame::sand.getAbsPos({ (float)ghostX + blockSize * i, (float)blockSize * j }));
                        window->draw(s);
                    }
        }

        void renderSand(sf::RenderWindow* window)
        {
            sf::Lock lock(sand::sandsLock);
            for (int i = 0; i < sand::sandListW; i++)
                for (int j = 0; j < sand::sandListH; j++)
                {
                    sf::RectangleShape shape = sand::sands[i][j]->renderShape;
                    const sf::Vector2f pos = layout::inGame::sand.getAbsPos({ (float)i * render::sandSize , (float)j * render::sandSize });
                    shape.setPosition(pos);
                    window->draw(shape);
                }
        }

        void renderLogo(sf::RenderWindow* window)
        {
            const sf::Vector2f pos = layout::inGame::info.getAbsPos({ 0,0 });
            source::logo.setPosition(pos);
            window->draw(source::logo);
        }

        void renderCover(sf::RenderWindow* window)
        {
            window->draw(source::cover);
        }

        void renderColorHint(sf::RenderWindow* window)
        {
            constexpr float PI = 3.1415926f;
            static float hintY = -20.0f;

            using namespace source::colorHint;
            if (placement::sinceLastPlacement() <= 1 && placement::placed)
            {
                float moveSpeed = cos(placement::sinceLastPlacement() * PI) + 1.1f;
                hintY -= 108.0f / render::fps * moveSpeed * 1.05;

                prev.setTextureRect(getTextureRect(prev, hintY));
                cur.setTextureRect(getTextureRect(cur, hintY + 108));
                next.setTextureRect(getTextureRect(next, hintY + 108 + 108));

                auto getY = [](float y) { return y < 0 ? 0 : y; };

                prev.setPosition(layout::inGame::color.getAbsPos({ 0, getY(hintY) }));
                cur.setPosition(layout::inGame::color.getAbsPos({ 0, getY(hintY + 108) }));
                next.setPosition(layout::inGame::color.getAbsPos({ 0, getY(hintY + 108 + 108) }));

                window->draw(next);
                window->draw(cur);
                window->draw(prev);
            }
            else
            {
                hintY = -20.0f;

                cur.setTextureRect(sf::IntRect(0, 20, cur.getTexture()->getSize().x, cur.getTexture()->getSize().y - 20));
                next.setTextureRect(sf::IntRect(0, 0, next.getTexture()->getSize().x, 20));

                cur.setPosition(layout::inGame::color.getAbsPos({ 0, 0 }));
                next.setPosition(layout::inGame::color.getAbsPos({ 0, 88 }));

                window->draw(next);
                window->draw(cur);
            }
        }

        void renderShapeHint(sf::RenderWindow* window)
        {
            shape::Shape& curShape = placement::curShape;
            const int w = curShape.w * render::hintBlockSize;
            const int h = curShape.h * render::hintBlockSize;
            const float x = layout::inGame::shape.getSize().x / 2 - w / 2.0f;
            const float y = layout::inGame::shape.getSize().y / 2 - h / 2.0f;

            auto s = sf::RectangleShape({ render::hintBlockSize, render::hintBlockSize });
            s.setFillColor(sf::Color(0xFFFFFFFF));
            for (int i = 0; i < curShape.w; i++)
                for (int j = 0; j < curShape.h; j++)
                    if (curShape.data[i][j])
                    {
                        s.setPosition(
                            layout::inGame::shape.getAbsPos({
                                x + i * render::hintBlockSize,
                                y + j * render::hintBlockSize
                                })
                        );
                        window->draw(s);
                    }
        }

        void renderFailLine(sf::RenderWindow* window)
        {
            sf::RectangleShape line({ layout::inGame::sand.getSize().x, render::sandSize });
            line.setFillColor(sf::Color(0xBB0000FF));
            line.setPosition(layout::inGame::sand.getAbsPos({ 0.0f, (float)sand::failLine * render::sandSize }));
            window->draw(line);
        }

        void renderScore(sf::RenderWindow* window)
        {
            using boost::format;

            sf::Text text;
            text.setFont(source::renderFont);
            text.setCharacterSize(40);
            text.setFillColor(sf::Color::Black);

            text.setString((format("%08d") % statistics::highScore[status::curMode]).str());
            const float textX = layout::inGame::info.getSize().x - text.getLocalBounds().width - 5;
            const float textY = layout::inGame::info.getSize().y / 2 - text.getLocalBounds().height - 6;
            sf::Vector2f pos = layout::inGame::info.getAbsPos({ textX, textY });
            text.setPosition(pos);
            window->draw(text);
            pos.y += text.getLocalBounds().height + 8;
            text.setString((format("%08d") % statistics::score).str());
            text.setPosition(pos);
            window->draw(text);
        }

    public:
        void render(sf::RenderWindow* window)
        {
            renderBackground(window);
            renderFPS(window);
            renderCover(window);
            renderLogo(window);
            renderSand(window);
            renderGhost(window);
            renderShapeHint(window);
            renderColorHint(window);
            renderScore(window);
            renderFailLine(window);
        }

    };

    // @brief 用于渲染游戏结束屏幕
    class FailRenderer : public Renderer
    {
    protected:
        void renderHint(sf::RenderWindow* window)
        {
            sf::Text hint("Press any key to restart.", source::renderFont, 30U);
            hint.setFillColor(sf::Color::Black);
            hint.setOrigin({ hint.getLocalBounds().width / 2, hint.getLocalBounds().height / 2 });
            hint.setPosition(windowW / 2.0f, windowH / 2.5f * 1.7f);
            window->draw(hint);
        }

        void renderFinalScore(sf::RenderWindow* window)
        {
            using boost::format;

            const float x = windowW / 2.0f;
            const float y = windowH / 2.5f;

            sf::Text score(
                (format("SCORE: %08d") % statistics::score).str(),
                source::renderFont,
                40U
            );
            score.setFillColor(sf::Color::Black);
            score.setOrigin({ score.getLocalBounds().width / 2, score.getLocalBounds().height / 2 });
            score.setPosition(x, y);
            window->draw(score);

            sf::Text highScore(
                (format("HIGH:  %08d") % statistics::highScore[status::curMode]).str(),
                source::renderFont,
                40U
            );
            highScore.setFillColor(sf::Color::Black);
            highScore.setOrigin({ highScore.getLocalBounds().width / 2, highScore.getLocalBounds().height / 2 });
            highScore.setPosition(x, y + highScore.getLocalBounds().height + 10);
            window->draw(highScore);

            if (statistics::score == statistics::highScore[status::curMode])
            {
                sf::Text newRecord("New Record!", source::renderFont, 40);
                newRecord.setFillColor(sf::Color::Black);
                newRecord.setPosition(
                    score.getGlobalBounds().left,
                    highScore.getGlobalBounds().top + highScore.getGlobalBounds().height + 5
                );
                window->draw(newRecord);
            }
        }

        void renderBanner(sf::RenderWindow* window)
        {
            sf::Text banner("Game Over", source::renderFont, 72U);
            banner.setFillColor(sf::Color::Black);
            banner.setOrigin({ banner.getLocalBounds().width / 2, banner.getLocalBounds().height / 2 });
            banner.setPosition({ windowW / 2, windowH / 4 });
            window->draw(banner);
        }

    public:
        void render(sf::RenderWindow* window)
        {
            renderBackground(window);
            renderFPS(window);
            renderBanner(window);
            renderFinalScore(window);
            renderHint(window);
        }
    };

    static Renderer& chooseRenderer(status::GameStat stat)
    {
        static StartRenderer start;
        static InGameRenderer inGame;
        static FailRenderer fail;

        switch (stat)
        {
        case status::START:
            return start;
        case status::IN_GAME:
            return inGame;
        case status::FAILED:
            return fail;
        }
    }

    void renderThread(sf::RenderWindow* window)
    {
        sf::Clock clock; // 用于监控FPS

        window->setFramerateLimit(render::fps);
        window->setActive(true);
        source::loadSource();

        while (window->isOpen())
        {
            chooseRenderer(status::curStatus).render(window);
            window->display();
            status::fps = 1.0f / clock.restart().asSeconds();
        }
    }
};