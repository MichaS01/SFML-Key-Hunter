#pragma once
#include "Settings.h"

class Game {
private:

	int m_GameState;

	sf::RenderWindow* m_RenderWindow;
	sf::Event m_Event;

	void eventController(void);
	void render(void);

public:

	enum GAMESTATE { MAINMENU, PLAYING, PAUSED, OVER };
	
	Game(void);
	int getGameStatus(void) { return this->m_GameState; }

};