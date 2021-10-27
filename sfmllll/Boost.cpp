#include "Boost.h"
#include "Score.h"
#include <cstdlib>

using namespace sf;

void Boost::loadFile()                                               // ����������� �����������       
{
	bst.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/coin.png");
	dr.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/drop.png");
	fr.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Fire.png");
}

void  Boost::randBoostObj()                                          // ��������� ��������� ����� �� 1 ������ ����� ����� ������ ����
{
	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i < 3; i++)                                      // ���� �� 3 ��������, �� ������ ���� �� ������ ������������ ����� ���� �� ����� 3 �����
	{
		boost[i].setTexture(bst);                                    // ����������� �������� �� ������
		bx[i] = rand() % 3;                                          // ��� ���������� ����������� �� ����� �� 3 ������� �������
		if (anim)
		{
			frame += 0.02;                                           // ��� ������ �������� �� ����� ������
			if (frame > 6)                                           // ���������  ������ ����� 6, ���� frame �������� 6, �� ������������ � 1-� �����������
				frame -= 6;
			switch (static_cast<int>(frame))                         // � ����������� �� �������� frame ���� ��������������� ����������� ��� �������
			{
			case 0: boost[i].setTextureRect(IntRect(0, 0, 85, 84)); break;
			case 1: boost[i].setTextureRect(IntRect(85, 0, 85, 84)); break;
			case 2: boost[i].setTextureRect(IntRect(170, 0, 85, 84)); break;
			case 3: boost[i].setTextureRect(IntRect(255, 0, 85, 84)); break;
			case 4: boost[i].setTextureRect(IntRect(340, 0, 85, 84)); break;
			case 5: boost[i].setTextureRect(IntRect(425, 0, 85, 84)); break;
			default: ;
			}
		}
		boost[i].setPosition(1920 + 200 * static_cast<float>(bx[i]), 230 + 330 * static_cast<float>(bx[i]));   // �������� ���������� � ���� �� ���� � � �
	}
}

void Boost::randBoostDropObj()                                       // �-� ��������� ���������� �� ����������� ���-�� ������, �� 5
{
	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i < 3; i++)
	{
		boost[i].setTexture(dr);
		boost[i].setScale(0.25, 0.25);                               // ������� �������
		bx[i] = rand() % 3;

		if (anim)
		{
			frame += 0.02;
			if (frame > 5)                                           // 5 ������
				frame -= 5;
			switch (static_cast<int>(frame))
			{
			case 0: boost[i].setTextureRect(IntRect(0, 0, 300, 380)); break;
			case 1: boost[i].setTextureRect(IntRect(300, 0, 300, 380)); break;
			case 2: boost[i].setTextureRect(IntRect(600, 0, 300, 380)); break;
			case 3: boost[i].setTextureRect(IntRect(900, 0, 300, 380)); break;
			case 4: boost[i].setTextureRect(IntRect(1200, 0, 300, 380)); break;
			default: ;
			}
		}
		boost[i].setPosition(1920 + 200 * static_cast<float>(bx[i]), 230 + 330 * static_cast<float>(bx[i]));
	}
}

void  Boost::randBoostFireObj()                                     // �-� ��������� ���������� �� ����������� ���-�� ������, �� ����� 6
{
	srand(static_cast<unsigned>(time(nullptr)));
	for (int i = 0; i < 3; i++)
	{
		boost[i].setTexture(fr);
		boost[i].setScale(0.25, 0.25);                              // ������� �������
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

void Boost::randMoveBoostObj(Sprite man, bool& scoreX10,int& game, int& GameLocation, Score& sc, Sound& zvon)    // ��������� ��������� ���� ������
{
	bool brk = true;                                          // ���������� �������� �� ������������� ����� �� ����� for
	srand(static_cast<unsigned>(time(nullptr)));
	Vector2f bk[3];
	for (int i = 0; i < 3; i++)
	{
		brk = sc.ScoreObjRun(game, GameLocation, scoreX10);   // � ������ ���������� ������� ScoreObjRun, ������� ���������� true ���� ���-�� ����� ������ 100,
		if (brk == false)                                     // � false ���� ���� ������ 100, � ������ � ����������� �� �������� ���������� �����,
			break;                                            // ���� ������� �� �����
		else
		{
			if (GameLocation == 1)                            // �-� ��������� �������� "GameLocation" � � ����������� �� ���� ���������� ��������
				boost[i].move(-1.0, 0);                       // �������� �������� ��� �����
			else if (GameLocation == 2)                       // � ������ ������� �������� ������������� �� 0.1
				boost[i].move(-1.1, 0);
			else if (GameLocation == 3)
				boost[i].move(-1.2, 0);
			bk[i] = boost[i].getPosition();
			if (man.getGlobalBounds().intersects(boost[i].getGlobalBounds()))   // ���� �������� "������" ���� (���� ���������� ��������� � ����� �������)
			{
				if (bk[i].x < 200)                            // �� ���� �������� � ���������� � = 200, ��� ���������� ��� ������ ��������� ��������
				{
					zvon.play();                              // ����������� ����
					scoreX10 = true;                          // ��� ���������� ��������� � ������� ScoreObjRun �� ������ � ����������� ���� �� 10 ��������
					bx[i] = rand() % 3;
					boost[i].setPosition(1920 + 200 * static_cast<float>(i), 230 + 330 * static_cast<float>(bx[i]));   // ��������� ������������ �����
				}
			}
			else                                              // ���� �������� �� "������" ���� (���� ���������� ��������� � ����� ������)
			{
				scoreX10 = false;                             // ���� �� 10 �� �������������
				if (bk[i].x < -85)                            // � ���� �������� ��� ���� ��������� �� ���������� ���������� � = -85
				{
					bx[i] = rand() % 3;                       // ����� ������������, ���������� ����� ����
					boost[i].setPosition(1920 + 150 * static_cast<float>(i), 230 + 330 * static_cast<float>(bx[i]));   
				}
			}
		}
	}
}

void Boost::AnimationCoin(float& frame)                        // �-�� ��������� �� �������� ����� � ��������
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
		default: ;
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
		default: ;
		}
	}
}

void Boost::draw(RenderWindow& window)   // �-� ���������� ����� �� ������
{
	for (const auto& i : boost)
		window.draw(i);
}