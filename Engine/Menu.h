#pragma once
#include "Settings.h"

class GameManager;

class Menu {
private:
public:
	Menu() {};
	virtual ~Menu() {};
	virtual void handleInput(RenderWindow*, Event&) = 0;
	virtual void update() = 0;
	virtual void render(RenderWindow*) = 0;
};