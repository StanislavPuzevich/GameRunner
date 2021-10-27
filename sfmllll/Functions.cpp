#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Blocks.h"
#include "Earth.h"
#include "Boost.h"
#include "Score.h"

using namespace  sf;

void UpDownMovement(int& game, Event& event, Sound& jump, Music& pl, bool& down, bool& up, float& dy, float& py) 
{                                                     // ����� game = 0, ���� ��������, �������� ������ ����� ���������
    if (event.type == Event::MouseButtonPressed)      // ���� ������������ ����� �� ����� ������� ����
        if (Keyboard::Key::Left)
            if (game == 0)                            
            {
                game = 1;                             // �������� � ���� ����������
                pl.play();                            // ������������� ������� ������
            } 
    if (game == 1)                                     
        if (event.type == Event::KeyPressed)
            if (event.key.code == Keyboard::Up)       // ���� ������������ �������� �� ������� UP
            {
                dy = -340;                            // ��������� �������� � �������� �� ��������� ��� �
                up = true;
                jump.play();                          //���� ������
            }
            else if (event.key.code == Keyboard::Down)// ���� ������������ �������� �� ������� DOWN
            {
                dy = 340;                             // ��������� �������� � �������� �� ��������� ��� �
                down = true;
                jump.play();                          // ���� ������
            }
}

void ManAnimationRun(Sprite& man, Earth& land, Blocks& bk, Sound& hit, float& frame, float& py, float& dy, int& game, Sound& zvon,
    float& spead, float& y, bool& anim, bool& up, bool& down, int& GameLocation, Boost& boost, bool& scoreX10, Score& sc)
{
    if (game == 0)                                    // ���� ������� ������ �����������, game = 0, �� �������� ������ ����� ���������
    {
        frame += 0.001f;
        if (frame > 4)
            frame -= 4;
        man.setTextureRect(IntRect(80 * static_cast<int>(frame), 0, 80, 130));
    }
    else if (game == 1)
    {
        if (py != dy)                                 // ������ ���� �������� �� ����������� ��������� ����� � ����, � ����� �� ��� � ���� �������� �������� ����
        {                                             // py - ���������� ���������� ��������� �� ��� �
            if (dy > 0)                               // dy - ��� ���������� � ������� ��������� �������� ����� ������� ������� UP and DOWN
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
            anim = false;                             // ���� ���� ������ ������� UP or DOWN, �� �������� ���� �� ������ ������ �����������
        } 
        else                                          // ���� ������� ���� �� ������
        {
            up = false;                               // �������� �������� �����
            down = false;                             // �������� �������� ����
            anim = true;                              // �������� ����
        }
        if (y < 216) y = 216;                         // ������������ �������� �� � �����, ����� ����� �� ������ ���� ������ ��� ������������ ������� ������� UP
        else if (y > 890) y = 890;                    // ������������ �������� �� � ����, ����� ����� �� ����� ���� ������ ��� ������������ ������� ������� DOWN
        if (anim)                                     // ���� �������� ���� ��������
        {
            frame += 0.02f;                           // �������� ����� ������, �� ����� 6
            if (frame > 6)
                frame -= 6;
            switch (static_cast<int>(frame))          // � ���������� �� �������� frame ������������ ������ ���� � �����������
            { 
            case 0: man.setTextureRect(IntRect(0, 135, 80, 130)); break;
            case 1: man.setTextureRect(IntRect(80, 135, 90, 130)); break;
            case 2: man.setTextureRect(IntRect(172, 135, 100, 130)); break;
            case 3: man.setTextureRect(IntRect(0, 270, 88, 130)); break;
            case 4: man.setTextureRect(IntRect(88, 270, 88, 130)); break;
            case 5: man.setTextureRect(IntRect(172, 270, 90, 130)); break;
            default: ;
            }
            if (GameLocation == 1)                    // � ����������� �� �������� GameLocation, �������� �-�� �������� ������
                boost.AnimationCoin(frame);
            else if (GameLocation == 2)             
                boost.AnimationDrop(frame);
            else if (GameLocation == 3)
                boost.AnimationFire(frame);
        }
        else                                          // �� ����� ������ ����� ���������� anim = false
        {
            if (up)                                   // ��� ������ ����� ���� ���� ����
                man.setTextureRect(IntRect(0, 400, 80, 150));
            if (down)                                 // ��� ������ ���� ���� ������
                man.setTextureRect(IntRect(83, 400, 100, 150));

            frame += 0.02f;                           // ������� ����� ������ � ��������� � � ������ ����������
            if (frame > 6)
                frame -= 6;

            if (GameLocation == 1)                    // ��������� ����� �������, �������� �����
                boost.AnimationCoin(frame);           // ����� ����� �������, anim = false, �������� ���� ���, ��������������
            else if (GameLocation == 2)               // ���������� ���������� ����� ���� �� �����������.
                boost.AnimationDrop(frame);           // �� ���� ������� ������ ��������� � �� �������� �� ����� ������,
            else if (GameLocation == 3)               // ������� ��������� ������ 85-90
                boost.AnimationFire(frame);
        }

        if (GameLocation == 1)                        // � ����������� �� GameLocation ��������� �������� (��������) �����
            land.randMoveEsarthObj();                 // ��� ������ ������� ���� �-��
        else if (GameLocation == 2)
            land.randMoveDeserthObj();
        else if (GameLocation == 3)
            land.randMoveSnowObj();

                                                      // ��� ������ �� ������ ������ ���� � ����
        if (GameLocation == 1)
        {
            boost.randMoveBoostObj(man, scoreX10, game, GameLocation, sc, zvon);  // �������� �-�� ������������� �������� ������
            if (bk.randMoveBlockObj(man) == 2)                            // �������� �-�� ������������� �������� ����������� � ������� �������� �� ������������
            {                                                             // ���� �-�� �������  �������� 2, ������ ������������ � ���������� ����
                man.setTextureRect(IntRect(190, 400, 105, 150));          // ������������� ���������� ���� "�������� �������"
                hit.play();                                               // ���� �����
                game = bk.randMoveBlockObj(man);                          // � ����������� game = 2, ����� ���� �����������
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