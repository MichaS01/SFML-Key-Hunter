#include "../Headers/Platform.h"

Platform::Platform(sf::Vector2f _pos, sf::Vector2f _scale) {

	if (!this->m_Texture.loadFromFile("Assets/Graphics/Platform.png"))
		return;

	this->m_Texture.setRepeated(true);
	this->setTexture(this->m_Texture);
	this->setPosition(_pos);
	this->setScale(_scale);
}