#pragma once
#include "Score.h"

class Score
{
private:
	sf::Texture sc;
	sf::Sprite score[3];
	double fs[3] = {};

public:

	void loadFile();                            // �������� �������
	void ScoreObjStart();                       // ������ ���������� ��������� ��� ������ �����
	bool ScoreObjRun(int, int&, bool& scoreX10);
	void draw(sf::RenderWindow& window);        //������� �� ����� ��������
};