#include <SFML/Graphics.hpp>
#include "Earth.h"

using namespace sf;

void Earth::loadFile()                                             // ����������� �����������       
{
	e.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/earth.png");
    des.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/desert.png");
    sn.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Snow.png");
}

void Earth::randEarthObj()                                         // �-�� ���������� ������������ �������� "�����"
{
    for (int i = 0; i < 3; i++)                                    // ���� �� 3, ������ ��� � ���� 3 ������� ������
    {
        earth[i].setTexture(e);                                    // ����������� �������� �� ������
        earth[i].setScale(2.f, 0.4f);                              // ������� �������
        earth[i].setPosition(0, 335 + 335 * static_cast<float>(i));// ������������ �������� �� ������
    }
}

void Earth::randDesertObj()                                        // �-�� ���������� ������������ �������� "�����"
{
    for (int i = 0; i < 3; i++)
    {
        desert[i].setTexture(des);
        desert[i].setScale(6.f, 0.7f);                             // ����������� ��������� �� ���������� �������, �������� ��������� � 6 ��� :) � ���� �� �������
        desert[i].setPosition(-70, 320 + 320 * static_cast<float>(i));
    }
}
 
void Earth::randSnowObj()                                          // �-�� ���������� ������������ �������� "����"
{
    for (int i = 0; i < 3; i++)
    {
        snow[i].setTexture(sn);
        snow[i].setScale(9.f, 1.1f);                               // ����������� ��������� �� ���������� �������, �������� ��������� � 9 ��� :) � ���� �� �������
        snow[i].setPosition(0, 325 + 325 * static_cast<float>(i));
    }
}

void Earth::randMoveEsarthObj()                                    // �-�� ������������� ������������ �������� "�����"
{
    Vector2f eh[3];
    for (int i = 0; i < 3; i++)
    {
        earth[i].move(-1.f, 0.f);                                  // �������� �������� ����� � ������ ������� �������������
        eh[i] = earth[i].getPosition();
        if (eh[i].x < -1920)                                       // ��� ������ ������ ��������� ���������� �� � = -1920, ������ �����
            earth[i].setPosition(0, 335 + 335 * static_cast<float>(i));
    }
}

void Earth::randMoveDeserthObj()                                   // �-�� ������������� ������������ �������� "�����"
{
    Vector2f eh[3];
    for (int i = 0; i < 3; i++)
    {
        desert[i].move(-1.1f, 0.f);                                // �������� �������� �����
        eh[i] = desert[i].getPosition();
        if (eh[i].x < -1920)
            desert[i].setPosition(-70, 320 + 320 * static_cast<float>(i));
    }
}

void Earth::randMoveSnowObj()                                      // �-�� ������������� ������������ �������� "����"
{
    Vector2f eh[3];
    for (int i = 0; i < 3; i++)
    {
        snow[i].move(-1.2f, 0.f);                                  // �������� �������� �����
        eh[i] = snow[i].getPosition();
        if (eh[i].x < -1920)
            snow[i].setPosition(0, 325 + 325 * static_cast<float>(i));
    }
}

void Earth::draw(RenderWindow& window)                             // �-�� ������������ ����� �� ������
{
    for (const auto& i : earth)
	    window.draw(i);
}

void Earth::drawDesert(RenderWindow& window)
{
    for (const auto& i : desert)
	    window.draw(i);
}

void Earth::drawSnow(RenderWindow& window)
{
    for (const auto& i : snow)
	    window.draw(i);
}