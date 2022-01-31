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
	int bx[5] = {}, by[5] = {}, bty[5] = {};      // кф для отображения блоков

public:

	void loadFile();                              // загрузка текстур
	void randBlockObj();                          // задает координаты элементов при первом цикле
	void randCactusObj();
	void randSnowManObj();
	int randMoveBlockObj(sf::Sprite man);         // задает координаты объектов "блоки" в ходе игры
	int randMoveCactusObj(sf::Sprite man);
	int randMoveSnowManObj(sf::Sprite man);
	void draw(sf::RenderWindow& window);          // отображает на экране элементы
	void drawCactus(sf::RenderWindow& window);
	void drawSnowMan(sf::RenderWindow& window);
};
