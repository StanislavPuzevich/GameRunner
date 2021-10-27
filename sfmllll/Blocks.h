#pragma once
#include <SFML/Graphics.hpp>

class Blocks
{
private:
	sf::Texture b;
	sf::Texture c;
	sf::Texture sm;
	sf::Sprite cactus[5];
	sf::Sprite block[5];
	sf::Sprite SnowMan[5];
	int bx[5] = {}, by[5] = {}, bty[5] = {};      // �� ��� ����������� ������

public:

	void loadFile();                              // �������� �������
	void randBlockObj();                          // ������ ���������� ��������� ��� ������ �����
	void randCactusObj();
	void randSnowManObj();
	int randMoveBlockObj(sf::Sprite man);         // ������ ���������� �������� "�����" � ���� ����
	int randMoveCactusObj(sf::Sprite man);
	int randMoveSnowManObj(sf::Sprite man);
	void draw(sf::RenderWindow& window);          // ���������� �� ������ ��������
	void drawCactus(sf::RenderWindow& window);
	void drawSnowMan(sf::RenderWindow& window);
};