#include "Boost.h"
#include "Score.h"
#include <cstdlib>

using namespace sf;

void Boost::loadFile()                                               // подключение изображений       
{
	bst.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/coin.png");
	dr.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/drop.png");
	fr.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Fire.png");
}

void  Boost::randBoostObj()                                          // случайная генерация МОНЕТ на 1 уровне сразу после начала игры
{
	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i < 3; i++)                                      // цикл на 3 элемента, по логике игры на экране одновременно может быть не более 3 монет
	{
		boost[i].setTexture(bst);                                    // накладывает текстуру на спрайт
		bx[i] = rand() % 3;                                          // для случайного отображения на одном из 3 беговых уровней
		if (anim)
		{
			frame += 0.02;                                           // эта строка отвечает за смену кадров
			if (frame > 6)                                           // поскольку  кадров всего 6, если frame достигло 6, то возвращаемся к 1-у изображению
				frame -= 6;
			switch (static_cast<int>(frame))                         // в зависимости от значения frame берём соответствующее изоюражение для спрайта
			{
			case 0: boost[i].setTextureRect(IntRect(0, 0, 85, 84)); break;
			case 1: boost[i].setTextureRect(IntRect(85, 0, 85, 84)); break;
			case 2: boost[i].setTextureRect(IntRect(170, 0, 85, 84)); break;
			case 3: boost[i].setTextureRect(IntRect(255, 0, 85, 84)); break;
			case 4: boost[i].setTextureRect(IntRect(340, 0, 85, 84)); break;
			case 5: boost[i].setTextureRect(IntRect(425, 0, 85, 84)); break;
			default:;
			}
		}
		boost[i].setPosition(1920 + 200 * static_cast<float>(bx[i]), 230 + 330 * static_cast<float>(bx[i]));   // случайно отображаем в игре по осям Х и У
	}
}

void Boost::randBoostDropObj()                                       // ф-я идентична предыдущей за исключением кол-ва кадров, их 5
{
	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i < 3; i++)
	{
		boost[i].setTexture(dr);
		boost[i].setScale(0.25f, 0.25f);                               // масштаб спрайта
		bx[i] = rand() % 3;

		if (anim)
		{
			frame += 0.02;
			if (frame > 5)                                           // 5 кадров
				frame -= 5;
			switch (static_cast<int>(frame))
			{
			case 0: boost[i].setTextureRect(IntRect(0, 0, 300, 380)); break;
			case 1: boost[i].setTextureRect(IntRect(300, 0, 300, 380)); break;
			case 2: boost[i].setTextureRect(IntRect(600, 0, 300, 380)); break;
			case 3: boost[i].setTextureRect(IntRect(900, 0, 300, 380)); break;
			case 4: boost[i].setTextureRect(IntRect(1200, 0, 300, 380)); break;
			default:;
			}
		}
		boost[i].setPosition(1920 + 200 * static_cast<float>(bx[i]), 230 + 330 * static_cast<float>(bx[i]));
	}
}

void  Boost::randBoostFireObj()                                     // ф-я идентична предыдущей за исключением кол-ва кадров, их снова 6
{
	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i < 3; i++)
	{
		boost[i].setTexture(fr);
		boost[i].setScale(0.25f, 0.25f);                              // масштаб спрайта
		bx[i] = rand() % 3;
		if (anim)
		{
			frame += 0.02;
			if (frame > 6)
				frame -= 6;
			switch (static_cast<int>(frame))
			{
			case 0: boost[i].setTextureRect(IntRect(0, 0, 330, 400)); break;
			case 1: boost[i].setTextureRect(IntRect(300, 0, 330, 400)); break;
			case 2: boost[i].setTextureRect(IntRect(600, 0, 330, 400)); break;
			case 3: boost[i].setTextureRect(IntRect(900, 0, 330, 400)); break;
			case 4: boost[i].setTextureRect(IntRect(1200, 0, 330, 400)); break;
			case 5: boost[i].setTextureRect(IntRect(1500, 0, 330, 400)); break;
			default:;
			}
		}
		boost[i].setPosition(1920 + 200 * static_cast<float>(bx[i]), 230 + 330 * static_cast<float>(bx[i]));
	}
}

void Boost::randMoveBoostObj(Sprite man, bool& scoreX10, int& game, int& GameLocation, Score& sc, Sound& zvon)    // случайная генерация всех БУСТОВ
{
	bool brk = true;                                          // переменная отвечает за своевременный выход из цикла for
	srand(static_cast<unsigned>(time(nullptr)));
	Vector2f bk[3];
	for (int i = 0; i < 3; i++)
	{
		brk = sc.ScoreObjRun(game, GameLocation, scoreX10);   // в строке выполнятся функция ScoreObjRun, которая возвращает true если кол-во очков меньше 100,
		if (brk == false)                                     // и false если счёт достиг 100, а дальше в зависимости от значения генерируем бусты,
			break;                                            // либо выходим из цикла
		else
		{
			if (GameLocation == 1)                            // ф-я принимает значение "GameLocation" и в зависимости от него определяет значение
				boost[i].move(-1.f, 0);                       // скорости движения для буста
			else if (GameLocation == 2)                       // с каждым уровнем скорость увеличивается на 0.1
				boost[i].move(-1.1f, 0);
			else if (GameLocation == 3)
				boost[i].move(-1.2f, 0);
			bk[i] = boost[i].getPosition();
			if (man.getGlobalBounds().intersects(boost[i].getGlobalBounds()))   // если Персонаж "поймал" буст (если координаты Персонажа и буста совпали)
			{
				if (bk[i].x < 200)                            // то буст исчезает в координате х = 200, это координата где ВСЕГДА нахожится Персонаж
				{
					zvon.play();                              // проигрываем звук
					scoreX10 = true;                          // эта переменная передаётся в функцию ScoreObjRun по ссылке и увеличивает счён НА 10 значений
					bx[i] = rand() % 3;
					boost[i].setPosition(1920 + 200 * static_cast<float>(i), 230 + 330 * static_cast<float>(bx[i]));   // случайное расположение буста
				}
			}
			else                                              // если Персонаж НЕ "поймал" буст (если координаты Персонажа и буста разные)
			{
				scoreX10 = false;                             // счёт на 10 НЕ увеличивается
				if (bk[i].x < -85)                            // а буст исчезает вне зоны видимости по достижению координаты х = -85
				{
					bx[i] = rand() % 3;                       // после исчезновения, генерируем новый буст
					boost[i].setPosition(1920 + 150 * static_cast<float>(i), 230 + 330 * static_cast<float>(bx[i]));
				}
			}
		}
	}
}

void Boost::AnimationCoin(float& frame)                        // ф-ии отвечаают за анимацию буста в движении
{
	for (auto& i : boost)
	{
		switch (static_cast<int>(frame))
		{
		case 0: i.setTextureRect(IntRect(0, 0, 85, 84)); break;
		case 1: i.setTextureRect(IntRect(85, 0, 85, 84)); break;
		case 2: i.setTextureRect(IntRect(170, 0, 85, 84)); break;
		case 3: i.setTextureRect(IntRect(255, 0, 85, 84)); break;
		case 4: i.setTextureRect(IntRect(340, 0, 85, 84)); break;
		case 5: i.setTextureRect(IntRect(425, 0, 85, 84)); break;
		default:;
		}
	}
}

void Boost::AnimationDrop(float& frame)
{
	for (auto& i : boost)
	{
		if (frame == 5.f) frame = 4.0;
		switch (static_cast<int>(frame))
		{
		case 0: i.setTextureRect(IntRect(0, 0, 300, 380)); break;
		case 1: i.setTextureRect(IntRect(300, 0, 300, 380)); break;
		case 2: i.setTextureRect(IntRect(600, 0, 300, 380)); break;
		case 3: i.setTextureRect(IntRect(900, 0, 300, 380)); break;
		case 4: i.setTextureRect(IntRect(1200, 0, 300, 380)); break;
		default:;
		}
	}
}

void Boost::AnimationFire(float& frame)
{
	for (auto& i : boost)
	{
		switch (static_cast<int>(frame))
		{
		case 0: i.setTextureRect(IntRect(0, 0, 330, 400)); break;
		case 1: i.setTextureRect(IntRect(310, 0, 300, 400)); break;
		case 2: i.setTextureRect(IntRect(570, 0, 300, 400)); break;
		case 3: i.setTextureRect(IntRect(850, 0, 330, 400)); break;
		case 4: i.setTextureRect(IntRect(1200, 0, 330, 400)); break;
		case 5: i.setTextureRect(IntRect(1500, 0, 330, 400)); break;
		default:;
		}
	}
}

void Boost::draw(RenderWindow& window)   // ф-я отображает бусты на экране
{
	for (const auto& i : boost)
		window.draw(i);
}
