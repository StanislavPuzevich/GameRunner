#pragma once
#include <SFML/Graphics.hpp>

class Earth
{
private:
	sf::Texture e;
	sf::Texture des;
	sf::Texture sn;
	sf::Sprite earth[3];
	sf::Sprite desert[3];
	sf::Sprite snow[3];

public:

	void loadFile();                        // �������� �������
	void randEarthObj();                    // ������ ���������� ��������� ��� ������ �����
	void randDesertObj();
	void randSnowObj();
	void randMoveEsarthObj();               // ������ ���������� �������� "�����" � ��������
	void randMoveDeserthObj();
	void randMoveSnowObj();
	void draw(sf::RenderWindow& window);    // ������� �� ����� ��������
	void drawDesert(sf::RenderWindow& window);
	void drawSnow(sf::RenderWindow& window);
};