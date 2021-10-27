#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int Menu()
{
	RenderWindow menu(VideoMode(960, 720, 32), "GameRunner");                         // ������ ���� ����
    Texture fn, textmenu1, textmenu2, textmenu3, textmenu4, ct, ab;                   // ���������� �������
    fn.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/bg.png");          // ��������� ��������
    ct.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/control1.png");
    ab.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/about.png");
    textmenu1.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/pl.png");
    textmenu2.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/control.png");
    textmenu3.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/ab.png");
    textmenu4.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/ex.png");
    Sprite fonmenu(fn), text1(textmenu1), text2(textmenu2), text3(textmenu3), text4(textmenu4), control(ct), about(ab);
    text1.setScale(0.8, 0.8);                                                         // ���������� ��������
    text2.setScale(0.7, 0.7);                                                         // �������� ��� �������� � ����
    text3.setScale(0.2, 0.2);
    text4.setScale(0.7, 0.7);

    Image icon;                                                                       // ���� �������� �� �������� ������� ����������
    icon.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/IconMenu.png");
    menu.setIcon(100, 100, icon.getPixelsPtr());

    Music MenuSound;                                                                  // ������� ����
    MenuSound.openFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/MenuSound.wav");
    MenuSound.setVolume(60);                                                          // ���������
    MenuSound.setLoop(true);                                                          // ���������� ������ ���� bool sound = true

    SoundBuffer mc;                                                                   // ���� ������ 
    mc.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/MenuBatt.wav");
    Sound MenuClick(mc);
    MenuClick.setVolume(100);

    text1.setPosition(15, 80);                                                        // ������������ �������� �� ������
    text2.setPosition(20, 170);
    text3.setPosition(25, 250);
    text4.setPosition(8, 315);

    bool sound = true;      
    bool menuOpen = true;
    int menuNum = 0;

    while (menuOpen)
    {
        Event event{};

        text1.setColor(Color::White);                                                 // ���������� �������� ����������� ����, ����� ����������� � �������
        text2.setColor(Color::White);
        text3.setColor(Color::White);
        text4.setColor(Color::White);

        if (sound)
        {
            MenuSound.play();
            sound = false;
        }
                                                                                      // ���� ������� ������ �� �������, ��� ��������� � ������� ����
        if (IntRect(15, 80, 320, 55).contains(Mouse::getPosition(menu))) { MenuClick.play(); text1.setColor(Color::Red); menuNum = 1; }
        if (IntRect(24, 175, 465, 45).contains(Mouse::getPosition(menu))) { MenuClick.play(); text2.setColor(Color::Red); menuNum = 2; }
        if (IntRect(25, 252, 360, 42).contains(Mouse::getPosition(menu))) { MenuClick.play(); text3.setColor(Color::Red); menuNum = 3; }
        if (IntRect(22, 325, 250, 43).contains(Mouse::getPosition(menu))) { MenuClick.play(); text4.setColor(Color::Red); menuNum = 4; }

        while (menu.pollEvent(event))
        {
            if (event.type == Event::MouseButtonPressed)
                if (Keyboard::Key::Left)
                {                                                                     // ����� � ���� �� ������� � ���� � ����������� �������
                    if (IntRect(15, 80, 320, 55).contains(Mouse::getPosition(menu))) menuOpen = false;
                    if (IntRect(24, 175, 465, 45).contains(Mouse::getPosition(menu))){ menu.draw(control); menu.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)){}}
                    if (IntRect(25, 252, 360, 42).contains(Mouse::getPosition(menu))){ menu.draw(about); menu.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)){}}
                    if (IntRect(22, 325, 250, 43).contains(Mouse::getPosition(menu))) menuOpen = false;
                }
            if (event.type == Event::Closed)
                menuOpen = false;
        }
        menu.draw(fonmenu);                                                           // ��������� ��������, ����������� � �.�. � �.�.
        menu.draw(text1);
        menu.draw(text2);
        menu.draw(text3);
        menu.draw(text4);
        menu.display();
    }
    return menuNum;
}