#include "PauseMenu.h"
#include "../Engine/GameManager.h"

PauseMenu::PauseMenu(GameManager& _gameManager)
	: m_GameManager(_gameManager)
{
	if (!this->m_BackgroundTexture.loadFromFile("Assets/Graphics/background.png"))
		return;
	this->m_BackgroundSprite.setTexture(this->m_BackgroundTexture);
	this->m_BackgroundSprite.setColor(Color(0, 0, 0, 153));
	this->m_BackgroundSprite.setScale(WINDOW_X / this->m_BackgroundSprite.getLocalBounds().width, WINDOW_Y / this->m_BackgroundSprite.getLocalBounds().height);

	if (this->m_LogoTexture.loadFromFile("Assets/Graphics/Logo.png"))
		this->m_LogoSprite.setTexture(this->m_LogoTexture);
	this->m_LogoSprite.setColor(Color(255, 255, 255, 153));
	this->m_LogoSprite.setPosition(WINDOW_X / 2 - this->m_LogoSprite.getGlobalBounds().width / 2, 0.0f);

	this->m_ReturnButton.setSize(Vector2f(200.f, 50.f));
	this->m_ReturnButton.setPosition(WINDOW_X / 2 - this->m_ReturnButton.getSize().x / 2, 300.f);
	this->m_ReturnButton.setFillColor(Color(0, 255, 0, 153));

	this->m_ExitButton.setSize(Vector2f(200.f, 50.f));
	this->m_ExitButton.setPosition(WINDOW_X / 2 - this->m_ExitButton.getSize().x / 2, 400.f);
	this->m_ExitButton.setFillColor(Color(255, 0, 0, 153));

	if (!this->m_TextFont.loadFromFile("Assets/Fonts/SitkaB.ttc"))
		return;

	this->m_ReturnText.setFont(this->m_TextFont);
	this->m_ReturnText.setString("Return");
	this->m_ReturnText.setFillColor(Color::Black);
	this->m_ReturnText.setPosition(this->m_ReturnButton.getPosition().x + this->m_ReturnButton.getSize().x / 2 - this->m_ReturnText.getGlobalBounds().width / 2,
		this->m_ReturnButton.getPosition().y + this->m_ReturnButton.getSize().y / 2 - this->m_ReturnText.getGlobalBounds().height);

	this->m_ExitText.setFont(this->m_TextFont);
	this->m_ExitText.setString("Exit");
	this->m_ExitText.setFillColor(Color::Black);
	this->m_ExitText.setPosition(this->m_ExitButton.getPosition().x + this->m_ExitButton.getSize().x / 2 - this->m_ExitText.getGlobalBounds().width / 2,
		this->m_ExitButton.getPosition().y + this->m_ExitButton.getSize().y / 2 - this->m_ExitText.getGlobalBounds().height);
}

void PauseMenu::handleInput(RenderWindow* _window, Event& _event) {
	while (_window->pollEvent(_event)) {
		switch (_event.type) {
		case Event::Closed:
			_window->close();
			break;

		case Event::MouseButtonPressed:
			if (_event.mouseButton.button == Mouse::Left) {

				Vector2f mousePos = Vector2f(_event.mouseButton.x * 1.0f, _event.mouseButton.y * 1.0f);
				if (this->m_ReturnButton.getGlobalBounds().contains(mousePos))
					this->m_GameManager.setMenu(nullptr, GameManager::GAMESTATE::PLAYING);

				else if (this->m_ExitButton.getGlobalBounds().contains(mousePos))
					_window->close();
			}
			break;

		case Event::KeyPressed:
			if (_event.key.code == Keyboard::Escape)
				this->m_GameManager.setMenu(nullptr, GameManager::GAMESTATE::PLAYING);
			break;
		}
	}
}

void PauseMenu::render(RenderWindow* _window) {
	_window->draw(this->m_BackgroundSprite);
	_window->draw(this->m_LogoSprite);
	_window->draw(this->m_ReturnButton);
	_window->draw(this->m_ExitButton);
	_window->draw(this->m_ReturnText);
	_window->draw(this->m_ExitText);
}