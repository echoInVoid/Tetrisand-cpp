#pragma once

namespace statistics
{
	extern unsigned int score;
	extern unsigned int highScore[3];

    void loadHighScore();
    void updateScore(unsigned int delta);
    void saveHighScore();
}

namespace status
{
	enum GameStat
	{
		START,   // 开始界面（尚待实现）
		IN_GAME, // 游戏中
		FAILED   // 失败界面
	};

	// 关于游戏模式的内容尚待实现
	enum GameMode
	{
		INFINITE, // 无限模式
		SPEEDRUN, // 竞速模式
		SURVIVAL  // 生存模式
	};

    extern GameStat curStatus;
    extern GameMode curMode;
    extern float fps, tps;
}