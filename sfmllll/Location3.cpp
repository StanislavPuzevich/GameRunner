#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Blocks.h"                          // ÊÎÌÌÅÍÒÀÐÈÈ ÈÄÅÍÒÈ×ÍÛ ÏÅÐÂÎÉ ËÎÊÀÖÈÈ
#include "Earth.h"
#include "Score.h"
#include "Boost.h"

using namespace  sf;

void ManAnimationRun(Sprite& man, Earth& land, Blocks& bk, Sound& hit, float& frame, float& py, float& dy, int& game, Sound& zvon,
    float& spead, float& y, bool& anim, bool& up, bool& down, int& GameLocation, Boost& boost, bool& scoreX10, Score& sc);
void UpDownMovement(int& game, Event& event, Sound& jump, Music& pl, bool& down, bool& up, float& dy, float& py);

void Location3(int& GameLocation, RenderWindow& window)
{
    Music pl;         
    pl.openFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/SnowMusic.wav");
    pl.setVolume(60);
    pl.setLoop(true);

    SoundBuffer jm;   
    jm.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Jump.wav");
    Sound jump(jm);
    jump.setVolume(10);

    SoundBuffer dr;   
    dr.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/SoundFire.wav");
    Sound drop(dr);
    drop.setVolume(40);

    SoundBuffer ht;  
    ht.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Hit.wav");
    Sound hit(ht);
    hit.setVolume(100);

    Texture f;      
    f.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/fon6.png");
    Sprite fon(f);

    Earth l;    
    l.loadFile();
    l.randSnowObj();

    Texture m;      
    m.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/man.png");
    Sprite man(m);

    Boost boost;
    boost.loadFile();
    boost.randBoostFireObj();

    float y = 540, frame = 0, py = 0, dy = 0, spead = 1, fx = 0; 
    bool up = false, down = false, anim = true, scoreX10 = false;
    int game = 0;

    Texture t;       
    t.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/textLev3.png");
    Sprite text(t);
    text.setScale(1, 1);
    text.setPosition(370, 400);

    Blocks bk;      
    bk.loadFile();
    bk.randSnowManObj();

    Texture go;     
    go.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/GO.png");
    Sprite gameover(go);
    gameover.setScale(1, 1);
    gameover.setPosition(290, 450);

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


        window.draw(fon);

        l.drawSnow(window);

        man.setPosition(200, y);
        window.draw(man);
        if (game == 0)
        {
            fx += 0.005;
            if (fx > 5)
                fx -= 5;
            if (fx < 3) window.draw(text);
        }

        boost.draw(window);
        bk.drawSnowMan(window);
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