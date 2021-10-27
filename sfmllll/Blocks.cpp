#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Blocks.h"

using namespace sf;

void Blocks::loadFile()                                          // подключение изображений       
{
	b.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Block.png");
	c.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Cactus.png");
	sm.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/SnowMan.png");
}

void Blocks::randBlockObj()                                     // случайная генерация БЛОКОВ на 1 уровне сразу после начала игры
{
	srand(static_cast<unsigned>(time(nullptr))); 
	for (int i = 0; i < 5; i++)                                 // цикл на 5 элементов, по логике игры на экране одновременно долдно быть <=5 блоков
	{
		block[i].setTexture(b);                                 // накладывает текстуру на спрайт
		block[i].setScale(0.8f, 0.8f);                          // уменьшает размер спрайта 
		bx[i] = rand() % 3;                                     // изображение имеет 6 видов блоков (3х2) bx - движение по х
		by[i] = rand() % 2;                                     // движение по у
		bty[i] = rand() % 3;                                    // задаёт случайное расположение блоков на "беговых уровнях" (1,2,3)
		block[i].setTextureRect(IntRect(158 * bx[i], 158 * by[i], 158, 155));  // случайный выбор блока на изображении
		block[i].setPosition(1920 + 220 * static_cast<float>(i), 235 + 335 * static_cast<float>(bty[i])); // случайное расположение блока в игре
	}
}

void Blocks::randCactusObj()                                    // случайная генерация КАКТУСОВ на 2 уровне сразу после начала игры
{
	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i < 5; i++)
	{
		cactus[i].setTexture(c);                                // накладывает текстуру на спрайт
		cactus[i].setScale(0.25f, 0.25f);                       // уменьшает размер спрайта 
		bx[i] = rand() % 3;                                     // изображение имеет 3 видов кактусов
		bty[i] = rand() % 3;
		cactus[i].setTextureRect(IntRect(550 * bx[i], 10, 545, 700));  
		cactus[i].setPosition(1920 + 310 * static_cast<float>(i), 150 + 330 * static_cast<float>(bty[i])); 
	}
}

void Blocks::randSnowManObj()                                    // случайная генерация СНЕГОВИКОВ на 3 уровне сразу после начала игры
{
	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i < 5; i++)
	{
		SnowMan[i].setTexture(sm);                               // накладывает текстуру на спрайт
		SnowMan[i].setScale(0.45f, 0.45f);                       // уменьшает размер спрайта 
		bx[i] = rand() % 3;                                      // изображение имеет 3 видов снеговиков
		bty[i] = rand() % 3;
		SnowMan[i].setTextureRect(IntRect(440 * bx[i], 0, 430, 500));
		SnowMan[i].setPosition(1920 + 600 * static_cast<float>(i), 140 + 320 * static_cast<float>(bty[i]));
	}
}

int Blocks::randMoveBlockObj(Sprite man)                         // случайная генерация БЛОКОВ на 1 уровне с движением
{
	srand(static_cast<unsigned>(time(nullptr)));
	Vector2f bk[5];
	for (int i = 0; i < 5; i++)
	{
		block[i].move(-1.0, 0);                                  // движение по Х                 
		block[i].setScale(0.8f, 0.8f);                           // масштаб спрайта
		bk[i] = block[i].getPosition();   
		if (bk[i].x < -100)                                      // как только координата по Х = -100 объект пропадает с экрана и появляется новый
		{
			bx[i] = rand() % 3;                                  // изображение имеет 6 видов блоков (3х2)
			by[i] = rand() % 2;
			bty[i] = rand() % 3;
			block[i].setTextureRect(IntRect(158 * bx[i], 158 * by[i], 158, 155));
			block[i].setPosition(1920 + 160 * static_cast<float>(i), 235 + 335 * static_cast<float>(bty[i]));
		}
		if (man.getGlobalBounds().intersects(block[i].getGlobalBounds()))    // проверка на столкновение героя с препятствием
			return 2;                                            // если столкнулись возвращаем значение 2 и игра завершается
	}
	return 0;                                                    // если столкновения не было возвращаем 0
}

int Blocks::randMoveCactusObj(Sprite man)                        // случайная генерация КАКТУСОВ на 2 уровне с движением
{
	srand(static_cast<unsigned>(time(nullptr)));
	Vector2f bk[5];
	for (int i = 0; i < 5; i++)
	{
		cactus[i].setScale(0.25f, 0.25f);                        // масштаб спрайта
		cactus[i].move(-1.1f, 0);                                // скорость движения по оси Х
		bk[i] = cactus[i].getPosition();
		if (bk[i].x < -100)                                      // как только координата по Х = -100 объект пропадает с экрана и появляется новый
		{
			bx[i] = rand() % 3;                                  // изображение имеет 3 видов кактусов
			bty[i] = rand() % 3;
			cactus[i].setTextureRect(IntRect(550 * bx[i], 10, 550, 700));
			cactus[i].setPosition(1920 + 280 * static_cast<float>(i), 150 + 330 * static_cast<float>(bty[i]));
		}
		if (man.getGlobalBounds().intersects(cactus[i].getGlobalBounds()))    // проверка на столкновение героя с препятствием
			return 2;
	}
	return 0;
}

int Blocks::randMoveSnowManObj(Sprite man)                        // случайная генерация СНЕГОВИКОВ на 1 уровне с движением
{
	srand(static_cast<unsigned>(time(nullptr)));
	Vector2f bk[5];
	for (int i = 0; i < 5; i++)
	{
		SnowMan[i].setScale(0.5f, 0.5f);                          // масштаб спрайта
		SnowMan[i].move(-1.2f, 0);                                // скорость движения по оси Х
		bk[i] = SnowMan[i].getPosition();
		if (bk[i].x < -440)                                       // как только координата по Х = -100 объект пропадает с экрана и появляется новый
		{
			bx[i] = rand() % 3;
			bty[i] = rand() % 3;
			SnowMan[i].setTextureRect(IntRect(440 * bx[i], 0, 430, 500));
			SnowMan[i].setPosition(1920 + 420 * static_cast<float>(i), 140 + 320 * static_cast<float>(bty[i]));
		} 
		if (man.getGlobalBounds().intersects(SnowMan[i].getGlobalBounds()))    // проверка на столкновение героя с препятствием
			return 2;
	}
	return 0;
}

void Blocks::draw(RenderWindow& window)            // ф-я отображения БЛОКОВ на экране
{
	for (const auto& i : block)
		window.draw(i);
}

void Blocks::drawCactus(RenderWindow& window)      // ф-я отображения КАКТУСОВ на экране
{
	for (const auto& i : cactus)
		window.draw(i);
}

void Blocks::drawSnowMan(RenderWindow& window)    // ф-я отображения СНЕГОВИКОВ на экране
{
	for (const auto& i : SnowMan)
		window.draw(i);
}


//Проект готов! однако хочу изменить геометрию объектов чуть-чуть

//for (int i = 0; i < 5; i++)
//{
//	SnowMa[i].setTexture(&sm);
//	SnowMa[i].setScale(0.4f, 0.4f);
//	SnowMa[i].setPointCount(6);
//	SnowMa[i].setPoint(0, Vector2f(90, 0));
//	SnowMa[i].setPoint(1, Vector2f(340, 0));
//	SnowMa[i].setPoint(2, Vector2f(0, 200));
//	SnowMa[i].setPoint(3, Vector2f(430, 200));
//	SnowMa[i].setPoint(4, Vector2f(0, 500));
//	SnowMa[i].setPoint(5, Vector2f(430, 500));
//	bx[i] = rand() % 3;
//	bty[i] = rand() % 3;
//	SnowMa[i].setTextureRect(IntRect(440 * bx[i], 0, 430, 500));
//	SnowMa[i].setPosition(1920 + 600 * static_cast<float>(i), 140 + 300 * static_cast<float>(bty[i]));
//}

//for (int i = 0; i < 5; i++)
	//{
	//	SnowMa[i].setTexture(&sm);
	//	SnowMa[i].setScale(0.4f, 0.4f);
	//	SnowMa[i].move(-0.9f, 0);
	//	bk[i] = SnowMa[i].getPosition();

	//	if (bk[i].x < -440)
	//	{
	//		SnowMa[i].setPointCount(6);
	//		SnowMa[i].setPoint(0, Vector2f(180, 0));
	//		SnowMa[i].setPoint(1, Vector2f(200, 0));
	//		SnowMa[i].setPoint(2, Vector2f(430, 200));
	//		SnowMa[i].setPoint(3, Vector2f(430, 500));
	//		SnowMa[i].setPoint(4, Vector2f(0, 500));
	//		SnowMa[i].setPoint(5, Vector2f(0, 200));
	//	
	//		bx[i] = rand() % 3;
	//		bty[i] = rand() % 3;
	//		SnowMa[i].setTextureRect(IntRect(440 * bx[i], 0, 430, 500));
	//		SnowMa[i].setPosition(1920 + 600 * static_cast<float>(i), 140 + 300 * static_cast<float>(bty[i]));
	//	}
	//	if (man.getGlobalBounds().intersects(SnowMa[i].getGlobalBounds()))
	//			return 2;
	//}
	//return 0;