#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Score.h"

class Boost
{
private:
	sf::Texture bst;
	sf::Texture dr;
	sf::Texture fr;
	sf::Sprite boost[3];
	bool anim = true;
	double frame = 0;
	int bx[3] = {};                         // кф для определения расположении бустов на беговых уровнях

public:

	void loadFile();                        // загрузка текстур
	void randBoostObj();                    // задает координаты бустов при первом цикле
	void randBoostDropObj();
	void randBoostFireObj();
	void randMoveBoostObj(sf::Sprite man, bool& scoreX10, int& game, int& GameLocation, Score& sc, sf::Sound& zvon);  // задает координаты бустов в движении
	void AnimationCoin(float& frame);       // ф-ии анимации бустов
	void AnimationDrop(float& frame);
	void AnimationFire(float& frame);
	void draw(sf::RenderWindow& window);    //выводит на экран бусты
};