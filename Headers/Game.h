#pragma once
#include "Player.h"

class Game {
private:

	int m_GameState;

	Player* m_Player;
	std::vector<Platform*>* m_Platforms;

	sf::RenderWindow* m_RenderWindow;
	sf::Event m_Event;

	Player* getPlayer(void) { return this->m_Player; }

	void eventController(void);
	void restart(void);
	void render(void);

public:

	enum GAMESTATE { MAINMENU, PLAYING, PAUSED, OVER };
	
	Game(void);
	int getGameStatus(void) { return this->m_GameState; }

};