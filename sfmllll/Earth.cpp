#include "Earth.h"

using namespace sf;

void Earth::loadFile()                                             // подключение изображений       
{
    e.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/earth.png");
    des.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/desert.png");
    sn.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Snow.png");
}

void Earth::randEarthObj()                                         // ф-ия начального расположения объектов "земля"
{
    for (int i = 0; i < 3; i++)                                    // цикл на 3, потому что в игре 3 беговых уровня
    {
        earth[i].setTexture(e);                                    // накладывает текстуру на спрайт
        earth[i].setScale(2.f, 0.4f);                              // масштаб спрайта
        earth[i].setPosition(0, 335 + 335 * static_cast<float>(i));// расположение спрайтов на экране
    }
}

void Earth::randDesertObj()                                        // ф-ия начального расположения объектов "песок"
{
    for (int i = 0; i < 3; i++)
    {
        desert[i].setTexture(des);
        desert[i].setScale(6.f, 0.7f);               // изображение оказалось не достаточно широким, пришлось растянуть в 6 раз :) в игре не заметно
        desert[i].setPosition(-70, 320 + 320 * static_cast<float>(i));
    }
}

void Earth::randSnowObj()                                          // ф-ия начального расположения объектов "снег"
{
    for (int i = 0; i < 3; i++)
    {
        snow[i].setTexture(sn);
        snow[i].setScale(9.f, 1.1f);                 // изображение оказалось не достаточно широким, пришлось растянуть в 9 раз :) в игре не заметно
        snow[i].setPosition(0, 325 + 325 * static_cast<float>(i));
    }
}

void Earth::randMoveEsarthObj()                                     // ф-ия динамического расположения объектов "земля"
{
    Vector2f eh[3];
    for (int i = 0; i < 3; i++)
    {
        earth[i].move(-1.f, 0);                       // скорость движения почвы с каждым уровнем увеличивается
        eh[i] = earth[i].getPosition();
        if (eh[i].x < -1920)                                       // как только спрайт достигает координаты по Х = -1920, создаём новый
            earth[i].setPosition(0, 335 + 335 * static_cast<float>(i));
    }
}

void Earth::randMoveDeserthObj()                                   // ф-ия динамического расположения объектов "песок"
{
    Vector2f eh[3];
    for (int i = 0; i < 3; i++)
    {
        desert[i].move(-1.1f, 0);                                  // скорость движения почвы
        eh[i] = desert[i].getPosition();
        if (eh[i].x < -1920)
            desert[i].setPosition(-70, 320 + 320 * static_cast<float>(i));
    }
}

void Earth::randMoveSnowObj()                                      // ф-ия динамического расположения объектов "снег"
{
    Vector2f eh[3];
    for (int i = 0; i < 3; i++)
    {
        snow[i].move(-1.2f, 0);                                    // скорость движения почвы
        eh[i] = snow[i].getPosition();
        if (eh[i].x < -1920)
            snow[i].setPosition(0, 325 + 325 * static_cast<float>(i));
    }
}

void Earth::draw(RenderWindow& window)                             // ф-ии отображаюшие почву на экране
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
