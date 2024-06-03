#pragma once
#include "Player.h"

struct CollisionObjectAdder {

	enum COLLISIONOBJECTTYPE {
		PLATFORM,
		KEY
	};

	int m_Type;

	Vector2f m_Position, m_Scale;
	Vector2i m_Amount;

	CollisionObjectAdder(void) : m_Type(0) {};
	CollisionObjectAdder(int, Vector2f, Vector2f, Vector2i);
};

struct PlatformAdder : public CollisionObjectAdder {
	PlatformAdder(Vector2f, Vector2f, Vector2i);
};

struct KeyAdder : public CollisionObjectAdder {
	KeyAdder(Vector2f, Vector2f);
};

class Room {
protected:
	Texture m_BackgroundTexture;
	Sprite m_BackgroundSprite;
	vector<Platform*> m_Platforms;
	vector<Key*>* m_Keys;


public:
	Room(string);
	void addPlatform(Vector2f, Vector2f, Vector2i);
	void addKey(Vector2f, Vector2f);
	//void addMusic(string);

	vector<Platform*> getPlatforms(void) { return this->m_Platforms; }
	vector<Key*>* getKeys(void) { return this->m_Keys; }
	
	void draw(RenderWindow*);

	//Music m_Music;
};