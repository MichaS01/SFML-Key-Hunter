#pragma once // Zapewnia, ¿e ten plik nag³ówkowy jest do³¹czany tylko raz podczas kompilacji
#include "CollisionObject.h" // Do³¹cza plik nag³ówkowy CollisionObject

// Klasa Platform dziedziczy po CollisionObject i reprezentuje platformê w grze
class Platform : public CollisionObject {
public:
    // Konstruktor klasy Platform, który przyjmuje pozycjê i rozmiar jako argumenty
    Platform(Vector2f, Vector2f);
};
