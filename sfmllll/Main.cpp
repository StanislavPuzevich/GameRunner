#include <SFML/Graphics.hpp>

using namespace  sf;

void Location1(int& GameLocation, RenderWindow& window);   
void Location2(int& GameLocation, RenderWindow& window);
void Location3(int& GameLocation, RenderWindow& window);
int Menu();

int main()
{
    int choiceMenu;                             // переменная связывающаяя игру с меню
    bool menuOpen = true;                       // переменная окна Меню
    while (menuOpen)
    {
        choiceMenu = Menu();                    // Вызов функции Меню  и получаение номера выбранного пункта

        if (choiceMenu == 1)                    // если был выбран пункт №1 меню (Play)
        {
            int GameLocation = 1;               // переменная отвечает за смену уровней

            RenderWindow window(VideoMode(0, 0, 32), "SFML works!", Style::Fullscreen);  // создаём окно игры

            if (GameLocation == 1)              // в зависимости от локации на текущий момент времени в игре, вызываем соответствующую ф-ию
                Location1(GameLocation, window);
            if (GameLocation == 2)
                Location2(GameLocation, window);
            if (GameLocation == 3)
                Location3(GameLocation, window);
        }
        else if (choiceMenu == 4)               // если в меню был выбран пункт №4, то закрываем Меню и приложение
            menuOpen = false;                   // выходим из цикла
    }
    return 0;
}