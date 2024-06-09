#pragma once // Zapewnia, �e ten plik nag��wkowy jest do��czany tylko raz podczas kompilacji
#include "CollisionObject.h" // Do��cza plik nag��wkowy CollisionObject

// Klasa Platform dziedziczy po CollisionObject i reprezentuje platform� w grze
class Platform : public CollisionObject {
public:
    // Konstruktor klasy Platform, kt�ry przyjmuje pozycj� i rozmiar jako argumenty
    Platform(Vector2f, Vector2f);
};
