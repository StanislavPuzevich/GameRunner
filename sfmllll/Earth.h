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

	void loadFile();                        // загрузка текстур
	void randEarthObj();                    // задает координаты элементов при первом цикле
	void randDesertObj();
	void randSnowObj();
	void randMoveEsarthObj();               // задает координаты объектов "почвы" в движении
	void randMoveDeserthObj();
	void randMoveSnowObj();
	void draw(sf::RenderWindow& window);    // выводит на экран элементы
	void drawDesert(sf::RenderWindow& window);
	void drawSnow(sf::RenderWindow& window);
};