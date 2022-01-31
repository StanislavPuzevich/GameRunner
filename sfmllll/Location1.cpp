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
    Music pl;                                                     // èãðîâàÿ ìåëîäèÿ
    pl.openFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Game.wav");
    pl.setVolume(60);                                             // ãðîìêîñòü 
    pl.setLoop(true);                                             // áåñêîíå÷íûé ïîâòîð

    SoundBuffer jm;                                               // çâóê ïðûæêà
    jm.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Jump.wav");
    Sound jump(jm);
    jump.setVolume(10);

    SoundBuffer dr;                                               // çâóê êàïëè
    dr.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/ZvonCoin.wav");
    Sound drop(dr);
    drop.setVolume(60);
     
    SoundBuffer ht;                                               //çâóê óäàðà
    ht.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/Hit.wav");
    Sound hit(ht);
    hit.setVolume(100);

    Texture f;                                                    // áåêãðàóíä
    f.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/fon2.png");
    Sprite fon(f);

    Earth l;                                                      // êëàññ "ïî÷âû"
    l.loadFile();
    l.randEarthObj();

    Texture m;                                                    // Ïåðñîíàæ
    m.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/man.png");
    Sprite man(m);                                                // èñõîäíèê òåêñòóð äëÿ ïåðñîíàæà

    Boost boost;                                                  // êëàññ áóñòîâ
    boost.loadFile();
    boost.randBoostObj();

    float y = 540, frame = 0, py = 0, dy = 0, spead = 1, fx = 0;  // ó - èçíà÷àëüíàÿ êîîðäèíàòà Ïåðñîíàæà, frame - ñêîðîñòü ñìåíû è ñìåíà êàäðîâ, py - íûíåøíåå
    bool up = false, down = false, anim = true, scoreX10 = false; // ïîëîæåíèå Ïåðñ íà îñè Ó, dy - ê êîòîðîìó ñòðåìèòñÿ, fx - ÷àñòîòà êàäðîâ íàäïèñåé,
    int game = 0;                                                 // up, down, anim - àíèìàöèÿ Ïåðñîíàæà, scoreX10 - óâåëè÷åíèå áóñòà íà 10
                                                                  // game - ïåðåìåííàÿ "ñëåäÿùàÿ" çà èãðîâûìè ñîáûòèÿìè, îòâå÷àåò çà íà÷ëî è êîíåö èãðû
    Texture t;                                                    // Òåñò "Óðîâåíü 1"
    t.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/textLev1.png");
    Sprite text(t);
    text.setPosition(370, 400);                                   // ðàñïîëîæåíèå íàäïèñè íà ýêðàíå

    Blocks bk;                                                    // êëàññ ïðåïÿòñòâèÿé â âèäå áëîêîâ
    bk.loadFile();
    bk.randBlockObj();

    Texture go;                                                   // òåêñò Ãåéì Îâåð
    go.loadFromFile("C:/Users/Lenovo/Desktop/MyPR/GameRunner/Paint/GO.png");
    Sprite gameover(go);
    gameover.setPosition(290, 450);                               // ðàñïîëîæåíèå íàäïèñè íà ýêðàíå

    Score sc;                                                     // êëàññ "Ñ÷¸ò÷èê î÷êîâ"
    sc.loadFile();
    sc.ScoreObjStart();

    while (window.isOpen())                                       // ïîêà îòêðûòî îêíî
    {
        Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            UpDownMovement(game, event, jump, pl, down, up, dy, py);// ô-ÿ àíèìàöèè ñòàðòîâîãî îêíà è äâèæåíèÿ ââåðõ è âíèç
        }

        ManAnimationRun(man, l, bk, hit, frame, py, dy, game, drop, spead, y, anim, up, down, GameLocation, boost, scoreX10, sc);
                                                                  // ô-ÿ àíèìàöèè âñåõ îáúåêòîâ
        if (GameLocation == 2)                                    // Åñëè GameLocation = 2 òî çàêðûâàåì ýòî îêíî è ïåðåõîäèì íà ñëåäóþùèé óðîâåíü
            break;

        window.draw(fon);                                         // èçîáðàæåíèå áåêãðàóíäà

        l.draw(window);                                           // èçîáðàæåíèå ïî÷âû

        man.setPosition(200.f, y);                                // ïîñòîÿííàÿ êîîðäèíàòà Ïåðñîíàæà ïî îñè Õ
        window.draw(man);                                         // èçîáðàæåíèå Ïåðñîíàæà
        if (game == 0)
        {
            fx += 0.005f;
            if (fx > 5)
                fx -= 5;
            if (fx < 3) window.draw(text);                        // àíèìàöèÿ òåêñòà "Ëåâ 1 íàæìèòå äëÿ ïðîäîëæåíèÿ"
        }

        boost.draw(window);                                       // èçîáðàæåíèå áóñòîâ
        bk.draw(window);                                          // èçîáðàæåíèå ïðåïÿòñòâèé
        sc.draw(window);                                          // èçîáðàæåíèå ñ÷¸òà

        if (game == 2)             
        {
            window.draw(gameover);                                // åñëè game = 2, âûâîäèì íàäïèñü Ãåéì Îâåð
            if (event.type == Event::MouseButtonPressed)          // îæèäàåì íàæàòèÿ êëàâèíè ìûøè
                if (Keyboard::Key::Left)
                {
                    GameLocation = 1;                             // ïîñëå ÷åãî âîçâðàùàåì  GameLocation = 1
                    window.clear();                               // î÷èùàåì è çàêðûâàåì îêíî
                    window.close();
                }
        }
        window.display();
    }
}
