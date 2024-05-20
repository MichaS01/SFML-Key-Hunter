#include "../Headers/Game.h"

Game::Game(void) {
	this->m_RenderWindow = new sf::RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), GAME_TITLE);

	this->render();
}

void Game::eventController(void) {

	if (this->getGameStatus() != GAMESTATE::PLAYING)
		return;

	while(this->m_RenderWindow->pollEvent(this->m_Event))
		switch (this->m_Event.type) {
			case sf::Event::Closed:
				this->m_RenderWindow->close();
				break;
		}
}

void Game::render(void) {

	while (this->m_RenderWindow->isOpen()) {
		
		this->eventController();

		this->m_RenderWindow->clear();

		// ...

		this->m_RenderWindow->display();
	}
}