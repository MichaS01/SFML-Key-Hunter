#pragma once
#include "Settings.h"

class CollisionObject {
protected:
	Vector2f m_Position, m_Size;
	Texture m_Texture;
	Sprite m_Sprite;

public:
	void setPosition(Vector2f);

	Sprite getSprite(void) { return this->m_Sprite; }
	Vector2f getPosition(void) { return this->m_Sprite.getPosition(); }
	FloatRect getCollider() const { return this->m_Sprite.getGlobalBounds(); }

	void draw(RenderWindow*);
};