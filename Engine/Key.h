#pragma once // Zapewnia, ¿e ten plik nag³ówkowy jest do³¹czany tylko raz podczas kompilacji

#include "CollisionObject.h" // Do³¹cza plik nag³ówkowy CollisionObject

// Klasa Key dziedziczy z CollisionObject i reprezentuje klucz w grze
class Key : public CollisionObject {
public:
    // Konstruktor klasy Key przyjmuje pozycjê i rozmiar jako argumenty
    Key(Vector2f, Vector2f);
};
