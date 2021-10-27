#include <SFML/Graphics.hpp>
#include "Score.h"

using namespace sf;

void Score::loadFile()                                       // подключение изображений   
{
	sc.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/score.png");
}

void Score::ScoreObjStart()
{
	for (int i = 0; i < 3; i++)                              // цикл на 3, поскольку в счёте будет 3-х значное число
	{
		score[i].setTexture(sc);
		score[i].setTextureRect(IntRect(0, 0, 44, 55));
		score[i].setPosition(45 * static_cast<float>(i), 0);
		fs[i] = 0;
	}
}

bool Score::ScoreObjRun(int game, int& GameLocation, bool& scoreX10)
{
    if (game == 1)
    {
        fs[2] += 0.001;
        if (fs[2] >= 10)
        {
            fs[2] -= 10;
            fs[1]++;
        }
        if (scoreX10 == true)
            fs[1]++;
        if (fs[1] >= 10)
        {
            fs[1] -= 10;
            fs[0]++;
        }
        if (fs[0] >= 1)
        {
            if (GameLocation == 1)
            {
                GameLocation = 2;
                return false;
            }
            if (GameLocation == 2)
            {
                GameLocation = 3;
                return false;
            }
        }                                                     // считывание нужной цифры с изображения
        score[0].setTextureRect(IntRect(44 * static_cast<int>(fs[0]), 0, 44, 55)); 
        score[1].setTextureRect(IntRect(44 * static_cast<int>(fs[1]), 0, 44, 55));
        score[2].setTextureRect(IntRect(44 * static_cast<int>(fs[2]), 0, 44, 55));
    }
    return true;
}

void Score::draw(RenderWindow& window)                        // отображения счёта на экране
{
    for (const auto& i : score)
	    window.draw(i);
}