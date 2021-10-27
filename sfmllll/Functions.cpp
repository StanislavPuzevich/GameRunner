#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Blocks.h"
#include "Earth.h"
#include "Boost.h"
#include "Score.h"

using namespace  sf;

void UpDownMovement(int& game, Event& event, Sound& jump, Music& pl, bool& down, bool& up, float& dy, float& py) 
{                                                     // когда game = 0, игра статична, меняются только кадры Персонажа
    if (event.type == Event::MouseButtonPressed)      // если пользователь нажал на любую клавишу мыши
        if (Keyboard::Key::Left)
            if (game == 0)                            
            {
                game = 1;                             // движение в игре начинается
                pl.play();                            // проигрывается фоновая музыка
            } 
    if (game == 1)                                     
        if (event.type == Event::KeyPressed)
            if (event.key.code == Keyboard::Up)       // если пользователь нажимает на клавишу UP
            {
                dy = -340;                            // изменение движения в пикселях по вертикали ось У
                up = true;
                jump.play();                          //звук прыжка
            }
            else if (event.key.code == Keyboard::Down)// если пользователь нажимает на клавишу DOWN
            {
                dy = 340;                             // изменение движения в пикселях по вертикали ось У
                down = true;
                jump.play();                          // звук прыжка
            }
}

void ManAnimationRun(Sprite& man, Earth& land, Blocks& bk, Sound& hit, float& frame, float& py, float& dy, int& game, Sound& zvon,
    float& spead, float& y, bool& anim, bool& up, bool& down, int& GameLocation, Boost& boost, bool& scoreX10, Score& sc)
{
    if (game == 0)                                    // если локация только загрузилась, game = 0, то меняются только кадры Персонажа
    {
        frame += 0.001f;
        if (frame > 4)
            frame -= 4;
        man.setTextureRect(IntRect(80 * static_cast<int>(frame), 0, 80, 130));
    }
    else if (game == 1)
    {
        if (py != dy)                                 // данный блок отвечает за перемещение Персонажа вверх и вниз, а также за вкл и выкл анимации движения Перс
        {                                             // py - координата нахождения Персонажа на оси У
            if (dy > 0)                               // dy - это координата к которой стремится Персонаж после нажатия клавишь UP and DOWN
            {
                py = spead;                
                dy = dy - spead;
            }
            if (dy < 0)
            {
                py = -spead;
                dy = dy + spead;
            }
            y += py;
            anim = false;                             // если была нажата клавиша UP or DOWN, то анимация бега на момент прыжка отключается
        } 
        else                                          // если клавиши были не нажаты
        {
            up = false;                               // анимация движения вверх
            down = false;                             // анимация движения вниз
            anim = true;                              // анимация бега
        }
        if (y < 216) y = 216;                         // ограничиваем движение по У вверх, чтобы игрок не улетел выше экрана при многократном нажатии клавиши UP
        else if (y > 890) y = 890;                    // ограничиваем движение по У вниз, чтобы игрок не падал ниже экрана при многократном нажатии клавиши DOWN
        if (anim)                                     // если анимация бега включена
        {
            frame += 0.02f;                           // скорость смены кадров, их всего 6
            if (frame > 6)
                frame -= 6;
            switch (static_cast<int>(frame))          // в зависимоси от значения frame показывается нужный кадр с изображения
            { 
            case 0: man.setTextureRect(IntRect(0, 135, 80, 130)); break;
            case 1: man.setTextureRect(IntRect(80, 135, 90, 130)); break;
            case 2: man.setTextureRect(IntRect(172, 135, 100, 130)); break;
            case 3: man.setTextureRect(IntRect(0, 270, 88, 130)); break;
            case 4: man.setTextureRect(IntRect(88, 270, 88, 130)); break;
            case 5: man.setTextureRect(IntRect(172, 270, 90, 130)); break;
            default: ;
            }
            if (GameLocation == 1)                    // в зависимости от значения GameLocation, вызываем ф-ию анимации бустов
                boost.AnimationCoin(frame);
            else if (GameLocation == 2)             
                boost.AnimationDrop(frame);
            else if (GameLocation == 3)
                boost.AnimationFire(frame);
        }
        else                                          // во время прыжка когда переменная anim = false
        {
            if (up)                                   // при прыжке вверх берём один кадр
                man.setTextureRect(IntRect(0, 400, 80, 150));
            if (down)                                 // при прыжке вниз берём другой
                man.setTextureRect(IntRect(83, 400, 100, 150));

            frame += 0.02f;                           // частота смены кадров у Персонажа и у бустов одинаковая
            if (frame > 6)
                frame -= 6;

            if (GameLocation == 1)                    // дублируем вызов функций, объясняю зачем
                boost.AnimationCoin(frame);           // когда игрок прыгает, anim = false, анимации бега нет, соответственно
            else if (GameLocation == 2)               // предыдущий идентичный этому блок не выполняется.
                boost.AnimationDrop(frame);           // но ведь монетки должны вращаться а не повисать во время прыжка,
            else if (GameLocation == 3)               // поэтому дублируем строки 85-90
                boost.AnimationFire(frame);
        }

        if (GameLocation == 1)                        // в зависимости от GameLocation запускаем движение (анимацию) почвы
            land.randMoveEsarthObj();                 // для каждой локации своя ф-ия
        else if (GameLocation == 2)
            land.randMoveDeserthObj();
        else if (GameLocation == 3)
            land.randMoveSnowObj();

                                                      // для каждой из окаций делаем одно и тоже
        if (GameLocation == 1)
        {
            boost.randMoveBoostObj(man, scoreX10, game, GameLocation, sc, zvon);  // вызываем ф-ию динамического создания бустов
            if (bk.randMoveBlockObj(man) == 2)                            // вызываем ф-ию динамического создания препятствий и сразуже проверям на столкновение
            {                                                             // если ф-ия вернула  значение 2, значит столкновение с Персонажем было
                man.setTextureRect(IntRect(190, 400, 105, 150));          // соответсвенно отображаем кадр "Плачущий мальчик"
                hit.play();                                               // звук удара
                game = bk.randMoveBlockObj(man);                          // и присваеваем game = 2, чтобы игра завершилась
            }
        }
        else if (GameLocation == 2)
        {
            boost.randMoveBoostObj(man, scoreX10,game, GameLocation, sc, zvon);
            if (bk.randMoveCactusObj(man) == 2)
            {
                man.setTextureRect(IntRect(190, 400, 105, 150));
                hit.play();
                game = bk.randMoveCactusObj(man);
            }
        }
        else if (GameLocation == 3)
        {
            boost.randMoveBoostObj(man, scoreX10, game, GameLocation, sc, zvon);
            if (bk.randMoveSnowManObj(man) == 2)
            {
                man.setTextureRect(IntRect(190, 400, 105, 150));
                hit.play();
                game = bk.randMoveSnowManObj(man);
            }
        }
    }
}