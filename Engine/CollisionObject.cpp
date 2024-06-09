#include "CollisionObject.h" // Do��cza plik nag��wkowy CollisionObject

// Definicja metody setPosition klasy CollisionObject
// Ustawia pozycj� sprite'a obiektu kolizji na podan� pozycj�
void CollisionObject::setPosition(Vector2f _position) {
    this->m_Sprite.setPosition(_position); // Ustawia pozycj� sprite'a na now� warto��
}

// Definicja metody draw klasy CollisionObject
// Rysuje sprite'a obiektu kolizji na podanym oknie renderowania
void CollisionObject::draw(RenderWindow* _window) {
    _window->draw(this->m_Sprite); // Rysuje sprite'a na oknie
}
