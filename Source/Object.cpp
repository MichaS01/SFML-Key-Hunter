#include "../Headers/Object.h"

void Object::render(sf::RenderWindow* _window) {
	_window->draw(*this);
}