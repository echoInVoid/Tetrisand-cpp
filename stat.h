#pragma once

namespace statistics
{
    extern unsigned int score, highScore;

    void loadHighScore();
    void updateScore(unsigned int delta);
    void saveHighScore();
}

namespace status
{
	enum GameStat
	{
		START,   // ��ʼ����
		IN_GAME, // ��Ϸ��
		FAILED   // ʧ�ܽ���
	};

	enum GameMode
	{
		INFINITE, // ����ģʽ
		SPEEDRUN, // ����ģʽ
		SURVIVAL  // ����ģʽ
	};

    extern GameStat curStatus;
    extern GameMode curMode;
    extern float fps, tps;
}