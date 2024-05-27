#include "../Headers/Player.h"
#include "../Headers/Game.h"

Player::Player(Game* _game)
	: m_Game(_game),
	m_JumpVelocity(1.f), m_ElapsedTime(0.f), m_PowerJump(1.f),
	m_IsJumping(false), m_IsFalling(false), m_Splashed(false),
	m_AnimationIndex(0), m_FallTime(0)
{
	if (!this->m_Texture.loadFromFile("Assets/Graphics/Player.png"))
		this->setColor(sf::Color::Black);
	else this->setTexture(this->m_Texture);

	this->setTextureRect(this->m_AnimationFrames[0]);
	this->setPosition(WINDOW_X / 2.f, WINDOW_Y / 2.f);

	this->loadSounds();
};

void Player::render(sf::RenderWindow* _window) {
	_window->draw(*this);
}

void Player::update(std::vector<Platform*>& _platforms) {

	if (this->m_Game->getGameStatus() != Game::GAMESTATE::PLAYING)
		return;

	float deltaTime = PLAYER_SPEED / 5000.0f;
	this->m_ElapsedTime += deltaTime;

	this->jumpControl(_platforms, deltaTime);
	this->animationControl(_platforms);

	if (this->m_ElapsedTime >= FRAME_TIME) {
		this->setTextureRect(this->m_AnimationFrames[this->m_AnimationIndex]);
		this->m_ElapsedTime -= FRAME_TIME;
	}
}

void Player::jumpControl(std::vector<Platform*>& _platforms, float _deltaTime) {
	float displacement = m_JumpVelocity * _deltaTime + 0.5f * GRAVITY * _deltaTime * _deltaTime;
	bool isOnAnyPlatform = false;

	if (m_IsJumping || m_IsFalling) {
		if (displacement > 0) m_IsFalling = true;

		m_JumpVelocity += GRAVITY * _deltaTime;

		bool collision = false;
		for (Platform* _platform : _platforms) {
			if (this->getPosition().y + this->getGlobalBounds().height >= _platform->getGlobalBounds().top &&
				this->getGlobalBounds().top <= _platform->getPosition().y + _platform->getGlobalBounds().height + 5.f &&
				this->getPosition().x >= _platform->getPosition().x - _platform->getGlobalBounds().width / 2.f &&
				this->getPosition().x < _platform->getPosition().x + _platform->getGlobalBounds().width) {
				collision = true;
				break;
			}
		}
		this->move(0.0f, displacement);

		if (collision && displacement < 0.0f)
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
					this->m_Sounds[SFX::SPLASHSOUND]->play();
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
		if (!m_IsJumping && !m_IsFalling && !m_Splashed) {
			m_IsJumping = true;
			m_JumpVelocity = JUMP_VELOCITY;
			m_FallTime = 0;

			if (m_AnimationIndex == ANIMATIONFRAMES::DOWN)
				m_JumpVelocity *= m_PowerJump;
			m_PowerJump = 1.0f;

			this->m_Sounds[SFX::JUMPSOUND]->play();
		}
	}
}

void Player::animationControl(std::vector<Platform*>& _platforms) {
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->m_AnimationIndex = ANIMATIONFRAMES::DEFAULT;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || this->m_IsJumping || this->m_IsFalling) &&
		!this->m_Splashed) {

		if (!this->m_IsJumping) {
			this->m_AnimationIndex++;
			if (this->m_AnimationIndex > ANIMATIONFRAMES::WALK02)
				this->m_AnimationIndex = ANIMATIONFRAMES::WALK00;
		}

		if (getPosition().x > 0.0f - this->getGlobalBounds().width) {
			this->move(-PLAYER_SPEED / 100.0f, 0.0f);
			this->setScale(-1.0f, 1.0f);
			this->setOrigin(this->getGlobalBounds().width, 0.0f);
		}

		for (Platform* _platform : _platforms) {
			if (this->getPosition().x <= _platform->getPosition().x + _platform->getGlobalBounds().width &&
				this->getPosition().x + this->getGlobalBounds().width >= _platform->getPosition().x &&
				this->getPosition().y <= _platform->getPosition().y + _platform->getGlobalBounds().height &&
				this->getPosition().y + this->getGlobalBounds().height > _platform->getPosition().y) {
				this->setPosition(getPosition().x + PLAYER_SPEED / 75.0f, getPosition().y);
				this->setScale(-1.0f, 1.0f);
				this->setOrigin(this->getGlobalBounds().width, 0.0f);
				break;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || this->m_IsJumping || this->m_IsFalling) &&
		!this->m_Splashed) {

		if (!this->m_IsJumping) {
			this->m_AnimationIndex++;
			if (this->m_AnimationIndex > ANIMATIONFRAMES::WALK02)
				this->m_AnimationIndex = ANIMATIONFRAMES::WALK00;
		}

		if (getPosition().x + this->getGlobalBounds().width < WINDOW_X + this->getGlobalBounds().width) {
			this->move(PLAYER_SPEED / 100.0f, 0.0f);
			this->setScale(1.0f, 1.0f);
			this->setOrigin(0, 0.0f);
		}

		for (Platform* _platform : _platforms) {
			if (this->getPosition().x <= _platform->getPosition().x + _platform->getGlobalBounds().width &&
				this->getPosition().x + this->getGlobalBounds().width > _platform->getPosition().x &&
				this->getPosition().y <= _platform->getPosition().y + _platform->getGlobalBounds().height &&
				this->getPosition().y + this->getGlobalBounds().height > _platform->getPosition().y) {
				this->setPosition(getPosition().x - PLAYER_SPEED / 75.0f, getPosition().y);
				this->setScale(1.0f, 1.0f);
				this->setOrigin(0, 0.0f);
				break;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !m_IsFalling && !m_IsJumping) {

		if (!m_IsFalling && !m_IsJumping) {
			this->m_AnimationIndex = ANIMATIONFRAMES::UP;
			if (this->m_Splashed) this->m_Splashed = false;
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !this->m_Splashed && !m_IsFalling && !m_IsJumping) {

		this->m_AnimationIndex = ANIMATIONFRAMES::DOWN;
		if (this->m_PowerJump < 1.5f) this->m_PowerJump += 0.005f;
	}
	else this->m_PowerJump = 1.0f;

	if (this->m_IsJumping) this->m_AnimationIndex = ANIMATIONFRAMES::JUMP;
	if (this->m_IsFalling) this->m_AnimationIndex = ANIMATIONFRAMES::FALL;
	if (this->m_Splashed) this->m_AnimationIndex = ANIMATIONFRAMES::FLAT;
}

bool Player::isOnPlatform(Platform* _platform) {
	return this->getPosition().x + this->getGlobalBounds().width >= _platform->getPosition().x &&
		this->getPosition().x < _platform->getPosition().x + _platform->getGlobalBounds().width &&
		this->getGlobalBounds().top + 5.f >= _platform->getPosition().y - this->getGlobalBounds().height &&
		this->getPosition().y + this->getGlobalBounds().height <= _platform->getPosition().y + 5.f;
}

void Player::loadSounds() {
	for (std::string sound : this->m_SoundLibrary) {
		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		buffer->loadFromFile("Assets/Sounds/SFX/" + sound);
		sf::Sound* sound = new sf::Sound(*buffer);
		this->m_SoundBuffers.push_back(buffer);
		sound->setVolume(25.0f);
		this->m_Sounds.push_back(sound);
	}
}