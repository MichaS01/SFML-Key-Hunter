#include "CollisionObject.h"

void CollisionObject::setPosition(Vector2f _position) {
	this->m_Sprite.setPosition(_position);
}

void CollisionObject::draw(RenderWindow* _window) {
	_window->draw(this->m_Sprite);
}