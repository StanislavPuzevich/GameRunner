#include "Blocks.h"                                 // КОММЕНТАРИИ ИДЕНТИЧНЫ ПЕРВОЙ ЛОКАЦИИ
#include "Earth.h"
#include "Boost.h"

using namespace  sf;

void ManAnimationRun(Sprite& man, Earth& land, Blocks& bk, Sound& hit, float& frame, float& py, float& dy, int& game, Sound& zvon,
    float& spead, float& y, bool& anim, bool& up, bool& down, int& GameLocation, Boost& boost, bool& scoreX10, Score& sc);
void UpDownMovement(int& game, Event& event, Sound& jump, Music& pl, bool& down, bool& up, float& dy, float& py);

void Location2(int& GameLocation, RenderWindow& window)
{
    Music pl;                                       // игровая мелодия
    pl.openFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Lev2Music.wav");
    pl.setVolume(60.f);
    pl.setLoop(true);

    SoundBuffer jm;                                 //звуки прыжка
    jm.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Jump.wav");
    Sound jump(jm);
    jump.setVolume(10.f);

    SoundBuffer dr;                                 //звуки прыжка
    dr.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/drop.wav");
    Sound drop(dr);
    drop.setVolume(60.f);

    SoundBuffer ht;                                 //звук удара
    ht.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Hit.wav");
    Sound hit(ht);
    hit.setVolume(100.f);

    Texture f;                                      // бекгрануд
    f.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/fon4.png");
    Sprite fon(f);

    Earth l;
    l.loadFile();
    l.randDesertObj();

    Texture m;
    m.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/man.png");
    Sprite man(m);

    Boost boost;
    boost.loadFile();
    boost.randBoostDropObj();

    float y = 540, frame = 0, py = 0, dy = 0, spead = 1, fx = 0;
    bool up = false, down = false, anim = true, scoreX10 = false;
    int game = 0;

    Texture t;
    t.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/textLev2.png");
    Sprite text(t);
    text.setPosition(370.f, 400.f);

    Blocks bk;                                      // класс препятствияй в виде кактусов
    bk.loadFile();
    bk.randCactusObj();

    Texture go;
    go.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/GO.png");
    Sprite gameover(go);
    gameover.setPosition(290.f, 450.f);

    Score sc;
    sc.loadFile();
    sc.ScoreObjStart();

    while (window.isOpen())
    {
        Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            UpDownMovement(game, event, jump, pl, down, up, dy, py);
        }

        ManAnimationRun(man, l, bk, hit, frame, py, dy, game, drop, spead, y, anim, up, down, GameLocation, boost, scoreX10, sc);

        if (GameLocation == 3)
            break;

        window.draw(fon);

        l.drawDesert(window);

        man.setPosition(200.f, y);
        window.draw(man);
        if (game == 0)
        {
            fx += 0.005f;
            if (fx > 5)
                fx -= 5;
            if (fx < 3) window.draw(text);
        }

        boost.draw(window);
        bk.drawCactus(window);
        sc.draw(window);

        if (game == 2)
        {
            window.draw(gameover);
            if (event.type == Event::MouseButtonPressed)
                if (Keyboard::Key::Left)
                {
                    GameLocation = 1;
                    window.clear();
                    window.close();
                }
        }
        window.display();
    }
}
