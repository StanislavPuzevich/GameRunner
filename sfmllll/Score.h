#pragma once
#include "Score.h"

class Score
{
private:
	sf::Texture sc;
	sf::Sprite score[3];
	double fs[3] = {};

public:

	void loadFile();                            // загрузка текстур
	void ScoreObjStart();                       // задает координаты элементов при первом цикле
	bool ScoreObjRun(int, int&, bool& scoreX10);
	void draw(sf::RenderWindow& window);        //выводит на экран элементы
};