#include "Player.h"
#include "GameManager.h"

// Konstruktor klasy Player
Player::Player(GameManager* _gameManager)
	: m_GameManager(_gameManager) // Inicjalizacja wskaŸnika GameManager
{
	// Wczytywanie tekstury gracza
	if (!m_Texture.loadFromFile("Assets/Graphics/Player.png"))
		this->m_Sprite.setColor(Color::Black); // Ustawienie koloru w przypadku braku tekstury
	else
		this->m_Sprite.setTexture(m_Texture); // Ustawienie tekstury

	// Ustawienie pocz¹tkowej pozycji gracza na œrodku okna gry
	this->m_Sprite.setTextureRect(m_AnimationFrames[0]);
	this->m_Sprite.setPosition(WINDOW_X / 2.f, WINDOW_Y / 2.f);

	// Za³adowanie dŸwiêków gracza
	this->loadSounds();
}

// Pobranie prostok¹ta kolizji gracza
sf::FloatRect Player::getCollider() const {
	sf::FloatRect bounds = this->m_Sprite.getGlobalBounds();
	sf::FloatRect bottomBounds = bounds;
	bottomBounds.top += bounds.height - 10;
	bottomBounds.height = 10;
	return bottomBounds;
}

// Ustawienie pozycji gracza
void Player::setPosition(float _x, float _y) {
	this->m_Sprite.setPosition(_x, _y);
}

// Sprawdzenie, czy gracz znajduje siê na platformie
bool Player::isOnPlatform(Platform* _platform) {
	return (getPosition().x + getCollider().width - 10 >= _platform->getPosition().x &&
		getPosition().x < _platform->getPosition().x + _platform->getCollider().width - 10 &&
		getCollider().intersects(_platform->getCollider()) &&
		m_Sprite.getPosition().y + getCollider().height <= _platform->getSprite().getPosition().y - 40.0f);
}

// Renderowanie gracza na ekranie
void Player::render(RenderWindow* _window) {
	_window->draw(m_Sprite);
}

// Aktualizacja logiki gracza
void Player::update(vector<Platform*> _platforms, vector<Key*>* _keys) {
	// Sprawdzenie stanu gry, czy gra jest w trybie gry
	if (this->m_GameManager->getGameStatus() != GameManager::GAMESTATE::PLAYING)
		return;

	float deltaTime = PLAYER_SPEED / 5000.0f;
	m_ElapsedTime += deltaTime;

	// Kontrola skoku gracza
	this->jumpControl(_platforms, deltaTime);

	// Kontrola animacji gracza
	this->animationControl(_platforms);

	// Aktualizacja animacji gracza zgodnie z czasem
	if (m_ElapsedTime >= FRAME_TIME) {
		m_Sprite.setTextureRect(m_AnimationFrames[m_AnimationIndex]);
		m_ElapsedTime -= FRAME_TIME;
	}

	// Kontrola zmiany pokoju
	this->roomControl();

	// Kontrola postêpu gry
	this->progressionControl(_keys);
}

// Funkcja odpowiedzialna za kontrolê skoku gracza
void Player::jumpControl(std::vector<Platform*> _platforms, float _deltaTime) {
	float displacement = m_JumpVelocity * _deltaTime + 0.5f * GRAVITY * _deltaTime * _deltaTime;
	bool isOnAnyPlatform = false;

	if (m_IsJumping || m_IsFalling) {
		if (displacement > 0) m_IsFalling = true;

		m_JumpVelocity += GRAVITY * _deltaTime;

		bool hitted = false;
		for (Platform* platform : _platforms) {
			if (getPosition().y + getCollider().height >= platform->getCollider().top + 5.0f &&
				getCollider().top <= platform->getPosition().y + platform->getCollider().height + m_AnimationFrames[m_AnimationIndex].height &&
				getPosition().x >= platform->getPosition().x - platform->getCollider().width / 2.0f &&
				getPosition().x < platform->getPosition().x + platform->getCollider().width) {
				hitted = true;
				break;
			}
		}
		m_Sprite.move(0.0f, displacement);

		if (hitted && displacement < 0.0f)
			m_JumpVelocity = 0.0f;
	}

	if (m_IsFalling) {
		m_FallTime++;
		for (Platform* platform : _platforms) {
			if (isOnPlatform(platform)) {
				m_JumpVelocity = 0.0f;
				m_IsJumping = false;
				m_IsFalling = false;
				isOnAnyPlatform = true;

				if (m_FallTime > FALL_TIME) {
					m_Splashed = true;
					this->m_Sounds[SFXS::SPLASHSOUND]->play();
				}
				m_FallTime = 0;

				break;
			}
		}
	}

	else if (!m_IsJumping && !m_IsFalling) {
		for (Platform* platform : _platforms)
			if (isOnPlatform(platform)) {
				isOnAnyPlatform = true;
				break;
			}
	}

	if (!isOnAnyPlatform && displacement > 0)
		m_IsFalling = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (!m_IsJumping && !m_Splashed && !m_IsFalling) {
			m_IsJumping = true;
			m_JumpVelocity = JUMP_VELOCITY;
			m_FallTime = 0;

			if (m_AnimationIndex == ANIMATIONFRAMES::DOWN)
				m_JumpVelocity *= m_PowerJump;
			m_PowerJump = 1.0f;

			this->m_Sounds[SFXS::JUMPSOUND]->play();
		}
	}
}

// Funkcja odpowiedzialna za kontrolê animacji gracza
void Player::animationControl(std::vector<Platform*> _platforms) {
	// Kontrola animacji podczas braku naciœniêtych klawiszy
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_AnimationIndex = ANIMATIONFRAMES::DEFAULT;

	// Kontrola animacji podczas ruchu w lewo
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || m_IsJumping || m_IsFalling) &&
		!m_Splashed) {

		if (!m_IsJumping) {
			m_AnimationIndex++;
			if (m_AnimationIndex > ANIMATIONFRAMES::
