#include "MainMenu.h"
#include "../Engine/GameManager.h"

MainMenu::MainMenu(GameManager& _gameManager)
	: m_GameManager(_gameManager), m_Timer(0)
{
	if (!m_BackgroundTexture.loadFromFile("Assets/Graphics/background.png"))
		return;
	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	m_BackgroundSprite.setColor(Color(0, 0, 0, 255));
	m_BackgroundSprite.setScale(WINDOW_X / m_BackgroundSprite.getLocalBounds().width, WINDOW_Y / m_BackgroundSprite.getLocalBounds().height);

	if (this->m_LogoTexture.loadFromFile("Assets/Graphics/Logo.png"))
		this->m_LogoSprite.setTexture(this->m_LogoTexture);
	this->m_LogoSprite.setColor(Color(255, 255, 255, 0));
	this->m_LogoSprite.setPosition(WINDOW_X / 2 - this->m_LogoSprite.getGlobalBounds().width / 2, 0.0f);

	if (this->m_IconTexture.loadFromFile("Assets/Graphics/Player.png")) {
		this->m_IconSprite.setTexture(this->m_IconTexture);
		this->m_IconSprite.setTextureRect(IntRect(192, 64, 64, 64));
		this->m_IconSprite.setScale(1.5f, 1.5f);
	} this->m_IconSprite.setColor(Color::Black);
	this->m_IconSprite.setPosition(this->m_LogoSprite.getPosition().x + 360, this->m_LogoSprite.getPosition().y + 68);

	this->m_PlayButton.setSize(Vector2f(200.f, 50.f));
	this->m_PlayButton.setPosition(WINDOW_X / 2 - this->m_PlayButton.getSize().x / 2, 300.f);
	this->m_PlayButton.setFillColor(Color(0, 255, 0, 0));

	this->m_ExitButton.setSize(Vector2f(200.f, 50.f));
	this->m_ExitButton.setPosition(WINDOW_X / 2 - this->m_ExitButton.getSize().x / 2, 400.f);
	this->m_ExitButton.setFillColor(Color(255, 0, 0, 0));

	if (!this->m_TextFont.loadFromFile("Assets/Fonts/SitkaB.ttc"))
		return;

	this->m_PlayText.setFont(this->m_TextFont);
	this->m_PlayText.setString("Start");
	this->m_PlayText.setFillColor(Color::Black);
	this->m_PlayText.setPosition(this->m_PlayButton.getPosition().x + this->m_PlayButton.getSize().x / 2 - this->m_PlayText.getGlobalBounds().width / 2,
		this->m_PlayButton.getPosition().y + this->m_PlayButton.getSize().y / 2 - this->m_PlayText.getGlobalBounds().height);

	this->m_ExitText.setFont(this->m_TextFont);
	this->m_ExitText.setString("Exit");
	this->m_ExitText.setFillColor(Color::Black);
	this->m_ExitText.setPosition(this->m_ExitButton.getPosition().x + this->m_ExitButton.getSize().x / 2 - this->m_ExitText.getGlobalBounds().width / 2,
		this->m_ExitButton.getPosition().y + this->m_ExitButton.getSize().y / 2 - this->m_ExitText.getGlobalBounds().height);

	if (!this->m_Buffer.loadFromFile("Assets/Sounds/SFX/MainMenu.wav"))
		return;
	this->m_Sound.setBuffer(this->m_Buffer);
	this->m_Sound.play();
}

void MainMenu::handleInput(RenderWindow* _window, Event& _event) {
	while (_window->pollEvent(_event)) {
		switch (_event.type) {
		case Event::Closed:
			_window->close();
			break;

		case Event::MouseButtonPressed:
			if (_event.mouseButton.button == Mouse::Left) {

				if (this->m_Timer < 767)
					return;

				Vector2f mousePos = Vector2f(_event.mouseButton.x * 1.0f, _event.mouseButton.y * 1.0f);
				if (this->m_PlayButton.getGlobalBounds().contains(mousePos))
					this->m_GameManager.setMenu(nullptr, GameManager::GAMESTATE::PLAYING);

				else if (this->m_ExitButton.getGlobalBounds().contains(mousePos))
					_window->close();
			}
			break;
		}
	}
}

void MainMenu::render(RenderWindow* _window) {
	this->update();
	_window->draw(this->m_BackgroundSprite);
	_window->draw(this->m_LogoSprite);
	_window->draw(this->m_IconSprite);
	_window->draw(this->m_PlayButton);
	_window->draw(this->m_ExitButton);
	_window->draw(this->m_PlayText);
	_window->draw(this->m_ExitText);
}

void MainMenu::update(void) {
	if (this->m_Timer >= 256 * 3 - 1)
		return;

	if (this->m_Timer <= 255) {
		this->m_LogoSprite.setColor(Color(255, 255, 255, this->m_Timer));
	} else if (this->m_Timer > 255 &&
		this->m_Timer <= 511) {
		this->m_IconSprite.setColor(Color(255, 255, 255, this->m_Timer));
	} else if (this->m_Timer > 511 &&
		this->m_Timer <= 767) {
		this->m_PlayButton.setFillColor(Color(0, 255, 0, this->m_Timer));
		this->m_ExitButton.setFillColor(Color(255, 0, 0, this->m_Timer));
	} this->m_Timer += 1;
}