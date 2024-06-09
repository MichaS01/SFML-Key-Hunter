#pragma once
#include "Player.h"

// Struktura do dodawania obiektów kolizyjnych
struct CollisionObjectAdder {

	enum COLLISIONOBJECTTYPE {
		PLATFORM, // Typ platformy
		KEY // Typ klucza
	};

	int m_Type; // Typ obiektu

	Vector2f m_Position, m_Scale; // Pozycja i skala obiektu
	Vector2i m_Amount; // Iloœæ obiektów

	// Konstruktor domyœlny
	CollisionObjectAdder(void) : m_Type(0) {};

	// Konstruktor
	CollisionObjectAdder(int, Vector2f, Vector2f, Vector2i);
};

// Struktura do dodawania platform
struct PlatformAdder : public CollisionObjectAdder {
	PlatformAdder(Vector2f, Vector2f, Vector2i);
};

// Struktura do dodawania kluczy
struct KeyAdder : public CollisionObjectAdder {
	KeyAdder(Vector2f, Vector2f);
};

// Klasa reprezentuj¹ca pokój w grze
class Room {
protected:
	Texture m_BackgroundTexture; // Tekstura t³a
	Sprite m_BackgroundSprite; // Sprite t³a
	vector<Platform*> m_Platforms; // Wektor platform
	vector<Key*>* m_Keys; // Wektor wskaŸników na klucze

public:
	// Konstruktor klasy Room
	Room(string);

	// Funkcja dodaj¹ca platformê
	void addPlatform(Vector2f, Vector2f, Vector2i);

	// Funkcja dodaj¹ca klucz
	void addKey(Vector2f, Vector2f);

	// Funkcja rysuj¹ca pokój
	void draw(RenderWindow*);

	// Metody dostêpu do platform i kluczy
	vector<Platform*> getPlatforms(void) { return this->m_Platforms; }
	vector<Key*>* getKeys(void) { return this->m_Keys; }
};
