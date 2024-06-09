#pragma once
#include "Player.h"

// Struktura do dodawania obiekt�w kolizyjnych
struct CollisionObjectAdder {

	enum COLLISIONOBJECTTYPE {
		PLATFORM, // Typ platformy
		KEY // Typ klucza
	};

	int m_Type; // Typ obiektu

	Vector2f m_Position, m_Scale; // Pozycja i skala obiektu
	Vector2i m_Amount; // Ilo�� obiekt�w

	// Konstruktor domy�lny
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

// Klasa reprezentuj�ca pok�j w grze
class Room {
protected:
	Texture m_BackgroundTexture; // Tekstura t�a
	Sprite m_BackgroundSprite; // Sprite t�a
	vector<Platform*> m_Platforms; // Wektor platform
	vector<Key*>* m_Keys; // Wektor wska�nik�w na klucze

public:
	// Konstruktor klasy Room
	Room(string);

	// Funkcja dodaj�ca platform�
	void addPlatform(Vector2f, Vector2f, Vector2i);

	// Funkcja dodaj�ca klucz
	void addKey(Vector2f, Vector2f);

	// Funkcja rysuj�ca pok�j
	void draw(RenderWindow*);

	// Metody dost�pu do platform i kluczy
	vector<Platform*> getPlatforms(void) { return this->m_Platforms; }
	vector<Key*>* getKeys(void) { return this->m_Keys; }
};
