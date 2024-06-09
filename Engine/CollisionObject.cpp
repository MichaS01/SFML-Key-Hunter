#include "CollisionObject.h" // Do³¹cza plik nag³ówkowy CollisionObject

// Definicja metody setPosition klasy CollisionObject
// Ustawia pozycjê sprite'a obiektu kolizji na podan¹ pozycjê
void CollisionObject::setPosition(Vector2f _position) {
    this->m_Sprite.setPosition(_position); // Ustawia pozycjê sprite'a na now¹ wartoœæ
}

// Definicja metody draw klasy CollisionObject
// Rysuje sprite'a obiektu kolizji na podanym oknie renderowania
void CollisionObject::draw(RenderWindow* _window) {
    _window->draw(this->m_Sprite); // Rysuje sprite'a na oknie
}
