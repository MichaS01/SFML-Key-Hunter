#pragma once
#include "Settings.h"

class Object : public sf::Sprite {
protected:
	sf::Texture m_Texture;

public:
	void render(sf::RenderWindow*);
};