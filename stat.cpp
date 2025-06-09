#include "stat.h"

#include <exception>
#include <iostream>
#include <fstream>

namespace statistics
{
	unsigned int score=0, highScore=0;

	void loadHighScore()
	{
		std::ifstream file;
		try
		{
			file.open("./score.txt");
			file >> highScore;
			file.close();
		}
		catch (std::exception& e)
		{
			highScore = 0;
			std::cerr << "Cannot load highscore: " << e.what() << '\n';
		}
	}

	void updateScore(unsigned int delta)
	{
		score += delta;
		if (score > highScore)
			highScore = score;
	}

	void saveHighScore()
	{
		std::ofstream file;
		try
		{
			file.open("./score.txt");
			file << highScore;
			file.close();
		}
		catch (std::exception& e)
		{
			std::cerr << "Cannot save highscore: " << e.what() << '\n';
		}
	}

}

namespace status
{
	GameMode curMode = INFINITE;
	GameStat curStatus = START;
	float fps = 0.0f, tps = 0.0f;
}