#include "Room.h"

CollisionObjectAdder::CollisionObjectAdder(int _type, Vector2f _position, Vector2f _scale, Vector2i _amount) {
	// Inicjalizacja wartoœci dla obiektu typu CollisionObjectAdder
	this->m_Type = _type;
	this->m_Position = _position;
	this->m_Scale = _scale;
	this->m_Amount = _amount;
}

PlatformAdder::PlatformAdder(Vector2f _position, Vector2f _scale, Vector2i _amount) {
	// Inicjalizacja wartoœci dla obiektu typu PlatformAdder
	this->m_Type = CollisionObjectAdder::COLLISIONOBJECTTYPE::PLATFORM;
	this->m_Position = _position;
	this->m_Scale = _scale;
	this->m_Amount = _amount;
}

KeyAdder::KeyAdder(Vector2f _position, Vector2f _scale) {
	// Inicjalizacja wartoœci dla obiektu typu KeyAdder
	this->m_Type = CollisionObjectAdder::COLLISIONOBJECTTYPE::KEY;
	this->m_Position = _position;
	this->m_Scale = _scale;
	this->m_Amount = { 1, 1 }; // Domyœlna liczba kluczy (1, 1)
}

Room::Room(string _backgroundPath) {
	// Wczytanie tekstury t³a z podanej œcie¿ki
	if (!this->m_BackgroundTexture.loadFromFile(_backgroundPath))
		this->m_BackgroundSprite.setColor(Color::Black); // Ustawienie koloru t³a na czarny, jeœli tekstura nie zosta³a za³adowana
	else
		this->m_BackgroundSprite.setTexture(this->m_BackgroundTexture); // Ustawienie tekstury t³a

	this->m_Keys = new vector<Key*>; // Inicjalizacja wskaŸnika na wektor wskaŸników kluczy
	std::cout << _backgroundPath << std::endl; // Wypisanie œcie¿ki t³a
}

void Room::addPlatform(Vector2f _position, Vector2f _scale, Vector2i _amount) {
	std::cout << _amount.x << " | " << _amount.y << "\n"; // Wypisanie liczby platform w osi x i y
	for (int i = 0; i < _amount.y; i++) {
		for (int j = 0; j < _amount.x; j++) {
			// Tworzenie i dodawanie platformy na podstawie podanej pozycji, skali i iloœci
			Platform* platform = new Platform(_position, _scale);
			platform->setPosition({ platform->getCollider().width * j + _position.x, platform->getCollider().height * i + _position.y });
			this->m_Platforms.push_back(platform); // Dodanie platformy do wektora platform
		}
	}
}

void Room::addKey(Vector2f _position, Vector2f _scale) {
	// Tworzenie i dodawanie klucza na podstawie podanej pozycji i skali
	Key* key = new Key(_position, _scale);
	this->m_Keys->push_back(key); // Dodanie klucza do wektora wskaŸników kluczy
}

void Room::draw(RenderWindow* _window) {
	// Rysowanie t³a
	_window->draw(this->m_BackgroundSprite);

	// Rysowanie platform
	for (Platform* _platform : this->m_Platforms)
		_platform->draw(_window);

	// Rysowanie kluczy
	for (auto it = this->m_Keys->begin(); it != this->m_Keys->end(); ++it) {
		Key* key = *it;
		key->draw(_window);
	}
}
