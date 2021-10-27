#include <SFML/Graphics.hpp>

using namespace  sf;

void Location1(int& GameLocation, RenderWindow& window);   
void Location2(int& GameLocation, RenderWindow& window);
void Location3(int& GameLocation, RenderWindow& window);
int Menu();

int main()
{
    int choiceMenu;                             // ���������� ������������ ���� � ����
    bool menuOpen = true;                       // ���������� ���� ����
    while (menuOpen)
    {
        choiceMenu = Menu();                    // ����� ������� ����  � ���������� ������ ���������� ������

        if (choiceMenu == 1)                    // ���� ��� ������ ����� �1 ���� (Play)
        {
            int GameLocation = 1;               // ���������� �������� �� ����� �������

            RenderWindow window(VideoMode(0, 0, 32), "SFML works!", Style::Fullscreen);  // ������ ���� ����

            if (GameLocation == 1)              // � ����������� �� ������� �� ������� ������ ������� � ����, �������� ��������������� �-��
                Location1(GameLocation, window);
            if (GameLocation == 2)
                Location2(GameLocation, window);
            if (GameLocation == 3)
                Location3(GameLocation, window);
        }
        else if (choiceMenu == 4)               // ���� � ���� ��� ������ ����� �4, �� ��������� ���� � ����������
            menuOpen = false;                   // ������� �� �����
    }
    return 0;
}