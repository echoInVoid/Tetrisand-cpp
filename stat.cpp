#include "stat.h"

#include <exception>
#include <iostream>
#include <fstream>

namespace statistics
{
	unsigned int score=0;
	unsigned int highScore[3];

	void loadHighScore()
	{
		std::ifstream file;
		try
		{
			file.open("./score.txt");
			for (int i = 0; i < 3; i++)
				file >> highScore[i];
			file.close();
		}
		catch (std::exception& e)
		{
			std::fill(highScore, highScore + 3, 0);
			std::cerr << "Cannot load highscore: " << e.what() << '\n';
		}
	}

	void updateScore(unsigned int delta)
	{
		score += delta;
		if (score > highScore[status::curMode])
			highScore[status::curMode] = score;
	}

	void saveHighScore()
	{
		std::ofstream file;
		try
		{
			file.open("./score.txt");
			for (int i = 0; i < 3; i++)
				file << highScore[i] << "\n";
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