#pragma once
#include "Platform.h"
#include "Key.h"

class Player {
private:
	Texture m_Texture;
	Sprite m_Sprite;
	float m_JumpVelocity = 1.0f, m_ElapsedTime = 0.0f, m_PowerJump = 1.0f;
	bool m_IsJumping = false, m_IsFalling = false, m_Splashed = false;
	int m_AnimationIndex = 0, m_FallTime = 0;
	vector<SoundBuffer*> m_SoundBuffers;
	vector<Sound*> m_Sounds;
	class GameManager* m_GameManager;

	vector<string> m_SoundLibrary = {
		"Jump.wav",
		"Slap.wav",
		"Coin.wav"
	};

	enum SFXS {
		JUMPSOUND,
		SPLASHSOUND,
		COINSOUND
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

	vector<IntRect> m_AnimationFrames = {
		IntRect(0, 0, 64, 64),
		IntRect(64, 0, 64, 64),
		IntRect(128, 0, 64, 64),
		IntRect(192, 0, 64, 64),

		IntRect(0, 64, 64, 64),
		IntRect(64, 64, 64, 64),
		IntRect(128, 64, 64, 64),
		IntRect(192, 64, 64, 64),

		IntRect(0, 128, 64, 64),
		IntRect(64, 128, 64, 64),
		IntRect(128, 128, 64, 64),
		IntRect(192, 128, 64, 64),

		IntRect(0, 192, 64, 64),
		IntRect(64, 192, 64, 64)
	};

	void jumpControl(vector<Platform*>, float);
	void animationControl(vector<Platform*>);
	void progressionControl(vector<Key*>*);
	void roomControl(void);
	void loadSounds(void);

public:
	Player(GameManager*);

	FloatRect getCollider(void) const;
	Vector2f getPosition(void) { return this->m_Sprite.getPosition(); }
	Sprite getSprite(void) { return this->m_Sprite; }

	void setPosition(float, float);

	bool isOnPlatform(Platform*);

	void render(RenderWindow*);
	void update(vector<Platform*>, vector<Key*>*);
};