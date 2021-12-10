#pragma once

class Score
{
private:
	sf::Texture sc;
	sf::Sprite score[3];
	double fs[3] = {};

public:

	void loadFile();                            // çàãðóçêà òåêñòóð
	void ScoreObjStart();                       // çàäàåò êîîðäèíàòû ýëåìåíòîâ ïðè ïåðâîì öèêëå
	bool ScoreObjRun(int, int&, bool& scoreX10);
	void draw(sf::RenderWindow& window);        //âûâîäèò íà ýêðàí ýëåìåíòû
};
