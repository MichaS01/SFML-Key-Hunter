#include "../Headers/Game.h"

Game::Game(void) {
	this->m_RenderWindow = new sf::RenderWindow(sf::VideoMode(WINDOW_X, WINDOW_Y), GAME_TITLE);
	
	this->restart();
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

void Game::restart(void) {
	delete this->m_Player;
	delete this->m_Platforms;

	this->m_GameState = GAMESTATE::PLAYING;

	this->m_Platforms = new std::vector<Platform*>;
	this->m_Platforms->push_back(new Platform(sf::Vector2f(WINDOW_X / 2.f, WINDOW_Y - 96.f), sf::Vector2f(1, 1)));
	
	this->m_Player = new Player(this);
}

void Game::render(void) {

	while (this->m_RenderWindow->isOpen()) {
		
		this->eventController();

		this->m_RenderWindow->clear();

		if (this->m_Player != nullptr) {
			this->m_Player->update(*this->m_Platforms);
			this->m_Player->render(this->m_RenderWindow);
		}

		if (this->m_Platforms != nullptr)
			for (Platform* _platform : *this->m_Platforms)
				_platform->render(this->m_RenderWindow);
		// ...

		this->m_RenderWindow->display();
	}
}