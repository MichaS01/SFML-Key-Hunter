#include "Player.h"
#include "GameManager.h"

Player::Player(GameManager* _gameManager)
	: m_GameManager(_gameManager)
{
	if (!m_Texture.loadFromFile("Assets/Graphics/Player.png"))
		this->m_Sprite.setColor(Color::Black);
	else this->m_Sprite.setTexture(m_Texture);

	this->m_Sprite.setTextureRect(m_AnimationFrames[0]);
	this->m_Sprite.setPosition(WINDOW_X / 2.f, WINDOW_Y / 2.f);
	
	this->loadSounds();
}

sf::FloatRect Player::getCollider() const {
	sf::FloatRect bounds = this->m_Sprite.getGlobalBounds();
	sf::FloatRect bottomBounds = bounds;
	bottomBounds.top += bounds.height - 10;
	bottomBounds.height = 10;
	return bottomBounds;
}

void Player::setPosition(float _x, float _y) {
	this->m_Sprite.setPosition(_x, _y);
}

bool Player::isOnPlatform(Platform* _platform) {
	return (getPosition().x + getCollider().width - 10 >= _platform->getPosition().x &&
		getPosition().x < _platform->getPosition().x + _platform->getCollider().width - 10 &&
		getCollider().intersects(_platform->getCollider()) &&
		m_Sprite.getPosition().y + getCollider().height <= _platform->getSprite().getPosition().y - 40.0f);
}

void Player::render(RenderWindow* _window) {
	_window->draw(m_Sprite);
}

void Player::update(vector<Platform*> _platforms, vector<Key*>* _keys) {
	if (this->m_GameManager->getGameStatus() != GameManager::GAMESTATE::PLAYING)
		return;

	float deltaTime = PLAYER_SPEED / 5000.0f;
	m_ElapsedTime += deltaTime;

	this->jumpControl(_platforms, deltaTime);
	this->animationControl(_platforms);

	if (m_ElapsedTime >= FRAME_TIME) {
		m_Sprite.setTextureRect(m_AnimationFrames[m_AnimationIndex]);
		m_ElapsedTime -= FRAME_TIME;
	}

	this->roomControl();
	this->progressionControl(_keys);
}

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

void Player::animationControl(std::vector<Platform*> _platforms) {
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_AnimationIndex = ANIMATIONFRAMES::DEFAULT;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || m_IsJumping || m_IsFalling) &&
		!m_Splashed) {

		if (!m_IsJumping) {
			m_AnimationIndex++;
			if (m_AnimationIndex > ANIMATIONFRAMES::WALK02)
				m_AnimationIndex = ANIMATIONFRAMES::WALK00;
		}

		if (getPosition().x > 0.0f - getCollider().width) {
			m_Sprite.move(-PLAYER_SPEED / 100.0f, 0.0f);
			m_Sprite.setScale(-1.0f, 1.0f);
			m_Sprite.setOrigin(getCollider().width, 0.0f);
		}

		for (Platform* platform : _platforms) {
			if (getPosition().x <= platform->getPosition().x + platform->getCollider().width &&
				getPosition().x + getCollider().width >= platform->getPosition().x + 20.0f &&
				getPosition().y <= platform->getPosition().y + platform->getCollider().height &&
				getPosition().y + getCollider().height > platform->getPosition().y - 40.0f) {
				m_Sprite.setPosition(getPosition().x + PLAYER_SPEED / 75.0f, getPosition().y);
				m_Sprite.setScale(-1.0f, 1.0f);
				m_Sprite.setOrigin(getCollider().width, 0.0f);
				break;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || m_IsJumping || m_IsFalling) &&
		!m_Splashed) {

		if (!m_IsJumping) {
			m_AnimationIndex++;
			if (m_AnimationIndex > ANIMATIONFRAMES::WALK02)
				m_AnimationIndex = ANIMATIONFRAMES::WALK00;
		}

		if (getPosition().x + getCollider().width < WINDOW_X + getCollider().width) {
			m_Sprite.move(PLAYER_SPEED / 100.0f, 0.0f);
			m_Sprite.setScale(1.0f, 1.0f);
			m_Sprite.setOrigin(0, 0.0f);
		}

		for (Platform* platform : _platforms) {
			if (getPosition().x <= platform->getPosition().x + platform->getCollider().width &&
				getPosition().x + getCollider().width > platform->getPosition().x &&
				getPosition().y <= platform->getPosition().y + platform->getCollider().height &&
				getPosition().y + getCollider().height > platform->getPosition().y - 40.0f) {
				m_Sprite.setPosition(getPosition().x - PLAYER_SPEED / 75.0f, getPosition().y);
				m_Sprite.setScale(1.0f, 1.0f);
				m_Sprite.setOrigin(0, 0.0f);
				break;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_AnimationIndex = ANIMATIONFRAMES::UP;
		if (m_Splashed) m_Splashed = false;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !m_Splashed) {
		m_AnimationIndex = ANIMATIONFRAMES::DOWN;
		if (m_PowerJump < 1.5f) m_PowerJump += 0.005f;
	} else m_PowerJump = 1.0f;

	if (m_IsJumping) m_AnimationIndex = ANIMATIONFRAMES::JUMP;
	if (m_IsFalling) m_AnimationIndex = ANIMATIONFRAMES::FALL;
	if (m_Splashed) m_AnimationIndex = ANIMATIONFRAMES::FLAT;
}

void Player::roomControl() {
	if (this->getPosition().x + (this->getCollider().width / 2.0f) < 0.0f)
		this->m_GameManager->changeRoom(Level::DIRECTION::LEFT);
	else if (this->getPosition().x + (this->getCollider().width / 2.0f) > WINDOW_X)
		this->m_GameManager->changeRoom(Level::DIRECTION::RIGHT);
	else if (this->getPosition().y + (this->getCollider().height / 2) < 0.0f)
		this->m_GameManager->changeRoom(Level::DIRECTION::UP);
	else if (this->getPosition().y + (this->getCollider().height / 2) > WINDOW_Y)
		this->m_GameManager->changeRoom(Level::DIRECTION::DOWN);
}

void Player::progressionControl(vector<Key*>* _keys) {
	if (!this->m_GameManager->getCurrentLevel()->getKeys()) {
		this->m_GameManager->setMenu(new GameOverMenu(*this->m_GameManager), GameManager::GAMESTATE::OVER);
		return;
	}

	for (auto it = _keys->begin(); it != _keys->end(); ++it) {
		Key* key = *it;
		if (this->getPosition().x + this->getCollider().width > key->getPosition().x &&
			this->getPosition().x <= key->getPosition().x + key->getCollider().width &&
			this->getPosition().y + this->getCollider().height > key->getPosition().y &&
			this->getPosition().y <= key->getPosition().y + key->getCollider().height) {

			delete key;
			_keys->erase(remove(_keys->begin(), _keys->end(), key), _keys->end());
			this->m_GameManager->getCurrentLevel()->remKey();
			this->m_Sounds[SFXS::COINSOUND]->play();
			break;
		}
	}
}

void Player::loadSounds() {
	for (string sound : this->m_SoundLibrary) {
		SoundBuffer* buffer = new SoundBuffer();
		buffer->loadFromFile("Assets/Sounds/SFX/" + sound);
		Sound* sound = new Sound(*buffer);
		this->m_SoundBuffers.push_back(buffer);
		sound->setVolume(25.0f);
		this->m_Sounds.push_back(sound);
	}
}