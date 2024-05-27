#pragma once
#include "Platform.h"

class Player : public Object {
private:
	sf::Texture m_Texture;
	float m_JumpVelocity,
		m_ElapsedTime,
		m_PowerJump;
	bool m_IsJumping,
		m_IsFalling,
		m_Splashed;
	int m_AnimationIndex, m_FallTime;
	std::vector<sf::SoundBuffer*> m_SoundBuffers;
	std::vector<sf::Sound*> m_Sounds;
	class Game* m_Game;

	std::vector<std::string> m_SoundLibrary = {
		"Jump.wav",
		"Slap.wav"
	};

	enum SFX {
		JUMPSOUND,
		SPLASHSOUND
	};

	enum ANIMATIONFRAMES {
		DEFAULT,
		WALK00,
		WALK01,
		WALK02,

		DOWN,
		JUMP,
		FALL,
		FLAT,

		OBLIQUE,
		TPOSE00,
		TPOSE01,
		TPOSE02,

		TPOSE03,
		UP
	};

	std::vector<sf::IntRect> m_AnimationFrames = {
		sf::IntRect(0, 0, 64, 64),
		sf::IntRect(64, 0, 64, 64),
		sf::IntRect(128, 0, 64, 64),
		sf::IntRect(192, 0, 64, 64),

		sf::IntRect(0, 64, 64, 64),
		sf::IntRect(64, 64, 64, 64),
		sf::IntRect(128, 64, 64, 64),
		sf::IntRect(192, 64, 64, 64),

		sf::IntRect(0, 128, 64, 64),
		sf::IntRect(64, 128, 64, 64),
		sf::IntRect(128, 128, 64, 64),
		sf::IntRect(192, 128, 64, 64),

		sf::IntRect(0, 192, 64, 64),
		sf::IntRect(64, 192, 64, 64)
	};

	bool isOnPlatform(Platform*);

	void jumpControl(std::vector<Platform*>&, float);
	void animationControl(std::vector<Platform*>&);
	void loadSounds(void);

public:
	Player(Game*);
	void render(sf::RenderWindow*);
	void update(std::vector<Platform*>&);
};