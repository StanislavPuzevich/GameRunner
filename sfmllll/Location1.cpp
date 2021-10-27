#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Blocks.h"
#include "Earth.h"
#include "Score.h"
#include "Boost.h"

using namespace  sf;

void ManAnimationRun(Sprite& man, Earth& land, Blocks& bk, Sound& hit, float& frame, float& py, float& dy, int& game, Sound& zvon,
    float& spead, float& y, bool& anim, bool& up, bool& down, int& GameLocation, Boost& boost, bool& scoreX10, Score& sc);
void UpDownMovement(int& game, Event& event, Sound& jump, Music& pl, bool& down, bool& up, float& dy, float& py);

void Location1(int& GameLocation, RenderWindow& window)
{
    Music pl;                                                     // игровая мелодия
    pl.openFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Game.wav");
    pl.setVolume(60);                                             // громкость 
    pl.setLoop(true);                                             // бесконечный повтор

    SoundBuffer jm;                                               // звук прыжка
    jm.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Jump.wav");
    Sound jump(jm);
    jump.setVolume(10);

    SoundBuffer dr;                                               // звук капли
    dr.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/ZvonCoin.wav");
    Sound drop(dr);
    drop.setVolume(60);
     
    SoundBuffer ht;                                               //звук удара
    ht.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Hit.wav");
    Sound hit(ht);
    hit.setVolume(100);

    Texture f;                                                    // бекграунд
    f.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/fon2.png");
    Sprite fon(f);

    Earth l;                                                      // класс "почвы"
    l.loadFile();
    l.randEarthObj();

    Texture m;                                                    // Персонаж
    m.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/man.png");
    Sprite man(m);                                                // исходник текстур для персонажа

    Boost boost;                                                  // класс бустов
    boost.loadFile();
    boost.randBoostObj();

    float y = 540, frame = 0, py = 0, dy = 0, spead = 1, fx = 0;  // у - изначальная координата Персонажа, frame - скорость смены и смена кадров, py - нынешнее
    bool up = false, down = false, anim = true, scoreX10 = false; // положение Перс на оси У, dy - к которому стремится, fx - частота кадров надписей,
    int game = 0;                                                 // up, down, anim - анимация Персонажа, scoreX10 - увеличение буста на 10
                                                                  // game - переменная "следящая" за игровыми событиями, отвечает за начло и конец игры
    Texture t;                                                    // Тест "Уровень 1"
    t.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/textLev1.png");
    Sprite text(t);
    text.setPosition(370, 400);                                   // расположение надписи на экране

    Blocks bk;                                                    // класс препятствияй в виде блоков
    bk.loadFile();
    bk.randBlockObj();

    Texture go;                                                   // текст Гейм Овер
    go.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/GO.png");
    Sprite gameover(go);
    gameover.setPosition(290, 450);                               // расположение надписи на экране

    Score sc;                                                     // класс "Счётчик очков"
    sc.loadFile();
    sc.ScoreObjStart();

    while (window.isOpen())                                       // пока открыто окно
    {
        Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            UpDownMovement(game, event, jump, pl, down, up, dy, py);// ф-я анимации стартового окна и движения вверх и вниз
        }

        ManAnimationRun(man, l, bk, hit, frame, py, dy, game, drop, spead, y, anim, up, down, GameLocation, boost, scoreX10, sc);
                                                                  // ф-я анимации всех объектов
        if (GameLocation == 2)                                    // Если GameLocation = 2 то закрываем это окно и переходим на следующий уровень
            break;

        window.draw(fon);                                         // изображение бекграунда

        l.draw(window);                                           // изображение почвы

        man.setPosition(200.f, y);                                // постоянная координата Персонажа по оси Х
        window.draw(man);                                         // изображение Персонажа
        if (game == 0)
        {
            fx += 0.005f;
            if (fx > 5)
                fx -= 5;
            if (fx < 3) window.draw(text);                        // анимация текста "Лев 1 нажмите для продолжения"
        }

        boost.draw(window);                                       // изображение бустов
        bk.draw(window);                                          // изображение препятствий
        sc.draw(window);                                          // изображение счёта

        if (game == 2)             
        {
            window.draw(gameover);                                // если game = 2, выводим надпись Гейм Овер
            if (event.type == Event::MouseButtonPressed)          // ожидаем нажатия клавини мыши
                if (Keyboard::Key::Left)
                {
                    GameLocation = 1;                             // после чего возвращаем  GameLocation = 1
                    window.clear();                               // очищаем и закрываем окно
                    window.close();
                }
        }
        window.display();
    }
}