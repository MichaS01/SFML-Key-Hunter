#pragma once // Zapewnia, �e ten plik nag��wkowy jest do��czany tylko raz podczas kompilacji

#include "CollisionObject.h" // Do��cza plik nag��wkowy CollisionObject

// Klasa Key dziedziczy z CollisionObject i reprezentuje klucz w grze
class Key : public CollisionObject {
public:
    // Konstruktor klasy Key przyjmuje pozycj� i rozmiar jako argumenty
    Key(Vector2f, Vector2f);
};
