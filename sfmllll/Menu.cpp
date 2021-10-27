#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int Menu()
{
	RenderWindow menu(VideoMode(960, 720, 32), "GameRunner");                         // создаём окно Меню
    Texture fn, textmenu1, textmenu2, textmenu3, textmenu4, ct, ab;                   // переменные текстур
    fn.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/bg.png");          // загружаем текстуры
    ct.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/control1.png");
    ab.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/about.png");
    textmenu1.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/pl.png");
    textmenu2.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/control.png");
    textmenu3.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/ab.png");
    textmenu4.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/ex.png");
    Sprite fonmenu(fn), text1(textmenu1), text2(textmenu2), text3(textmenu3), text4(textmenu4), control(ct), about(ab);
    text1.setScale(0.8, 0.8);                                                         // переменный спрайтов
    text2.setScale(0.7, 0.7);                                                         // масштабы для надписей в Меню
    text3.setScale(0.2, 0.2);
    text4.setScale(0.7, 0.7);

    Image icon;                                                                       // блок отвечает за создание эмблемы приложения
    icon.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/IconMenu.png");
    menu.setIcon(100, 100, icon.getPixelsPtr());

    Music MenuSound;                                                                  // мелодия меню
    MenuSound.openFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/MenuSound.wav");
    MenuSound.setVolume(60);                                                          // громкость
    MenuSound.setLoop(true);                                                          // постоянный повтор пока bool sound = true

    SoundBuffer mc;                                                                   // звук кликов 
    mc.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/MenuBatt.wav");
    Sound MenuClick(mc);
    MenuClick.setVolume(100);

    text1.setPosition(15, 80);                                                        // расположение надписей на экране
    text2.setPosition(20, 170);
    text3.setPosition(25, 250);
    text4.setPosition(8, 315);

    bool sound = true;      
    bool menuOpen = true;
    int menuNum = 0;

    while (menuOpen)
    {
        Event event{};

        text1.setColor(Color::White);                                                 // возвращает надписям изначальный цвет, после окрашивания в красный
        text2.setColor(Color::White);
        text3.setColor(Color::White);
        text4.setColor(Color::White);

        if (sound)
        {
            MenuSound.play();
            sound = false;
        }
                                                                                      // если навести курсор на надпись, она окрасится в красный цвет
        if (IntRect(15, 80, 320, 55).contains(Mouse::getPosition(menu))) { MenuClick.play(); text1.setColor(Color::Red); menuNum = 1; }
        if (IntRect(24, 175, 465, 45).contains(Mouse::getPosition(menu))) { MenuClick.play(); text2.setColor(Color::Red); menuNum = 2; }
        if (IntRect(25, 252, 360, 42).contains(Mouse::getPosition(menu))) { MenuClick.play(); text3.setColor(Color::Red); menuNum = 3; }
        if (IntRect(22, 325, 250, 43).contains(Mouse::getPosition(menu))) { MenuClick.play(); text4.setColor(Color::Red); menuNum = 4; }

        while (menu.pollEvent(event))
        {
            if (event.type == Event::MouseButtonPressed)
                if (Keyboard::Key::Left)
                {                                                                     // выбор и клик на надписи в меню и последующие события
                    if (IntRect(15, 80, 320, 55).contains(Mouse::getPosition(menu))) menuOpen = false;
                    if (IntRect(24, 175, 465, 45).contains(Mouse::getPosition(menu))){ menu.draw(control); menu.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)){}}
                    if (IntRect(25, 252, 360, 42).contains(Mouse::getPosition(menu))){ menu.draw(about); menu.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)){}}
                    if (IntRect(22, 325, 250, 43).contains(Mouse::getPosition(menu))) menuOpen = false;
                }
            if (event.type == Event::Closed)
                menuOpen = false;
        }
        menu.draw(fonmenu);                                                           // отрисовка надписей, бекграундов и т.д. и т.п.
        menu.draw(text1);
        menu.draw(text2);
        menu.draw(text3);
        menu.draw(text4);
        menu.display();
    }
    return menuNum;
}