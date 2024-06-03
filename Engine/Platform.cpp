#include "Platform.h"


Platform::Platform(Vector2f _position, Vector2f _scale) {
	this->m_Position = _position;
	this->m_Size = _scale;

	if (!m_Texture.loadFromFile("Assets/Graphics/Platform.png"))
		return;

	this->m_Sprite.setTexture(m_Texture);
	this->m_Sprite.setPosition(m_Position);
	this->m_Sprite.setScale(m_Size);
}