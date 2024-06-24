#pragma once

namespace statistics
{
    extern unsigned int score, highScore;

    void loadHighScore();
    void updateScore(unsigned int delta);
    void saveHighScore();
}