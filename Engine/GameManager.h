#pragma once
#include "Player.h"
#include "../Levels/Levels.h"
#include "../Menus/MenusList.h"

class Menu;

class GameManager {
private:
	int m_GameState;
	HWND m_WindowHandler;

	Player* m_Player;
	Level* m_CurrentLevel;
	Menu* m_Menu;
	RenderWindow* m_Window;

	Event m_Event;

	
	void loadSettings(void);
	void eventManager(void);
	void render(void);

public:
	enum GAMESTATE {
		MAINMENU,
		PLAYING,
		PAUSED,
		OVER
	};

	GameManager();

	Level* getCurrentLevel(void) { return this->m_CurrentLevel; }
	Player* getPlayer(void) { return this->m_Player; }

	int getGameStatus(void) { return this->m_GameState; };

	void setMenu(Menu*, int);
	void restartGame(void);

	void changeRoom(int);
};