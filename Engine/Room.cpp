#include "Room.h"

CollisionObjectAdder::CollisionObjectAdder(int _type, Vector2f _position, Vector2f _scale, Vector2i _amount) {
	this->m_Type = _type;
	this->m_Position = _position;
	this->m_Scale = _scale;
	this->m_Amount = _amount;
}

PlatformAdder::PlatformAdder(Vector2f _position, Vector2f _scale, Vector2i _amount) {
	this->m_Type = CollisionObjectAdder::COLLISIONOBJECTTYPE::PLATFORM;
	this->m_Position = _position;
	this->m_Scale = _scale;
	this->m_Amount = _amount;
}

KeyAdder::KeyAdder(Vector2f _position, Vector2f _scale) {
	this->m_Type = CollisionObjectAdder::COLLISIONOBJECTTYPE::KEY;
	this->m_Position = _position;
	this->m_Scale = _scale;
	this->m_Amount = { 1, 1 };
}

Room::Room(string _backgroundPath) {
	if (!this->m_BackgroundTexture.loadFromFile(_backgroundPath))
		this->m_BackgroundSprite.setColor(Color::Black);
	else this->m_BackgroundSprite.setTexture(this->m_BackgroundTexture);

	this->m_Keys = new vector<Key*>;
	std::cout << _backgroundPath << std::endl;
}

void Room::addPlatform(Vector2f _position, Vector2f _scale, Vector2i _amount) {
	std::cout << _amount.x << " | " << _amount.y << "\n";
	for (int i = 0; i < _amount.y; i++)
		for (int j = 0; j < _amount.x; j++) {
			Platform* platform = new Platform(_position, _scale);
			platform->setPosition({ platform->getCollider().width * j + _position.x, platform->getCollider().height * i + _position.y });
			this->m_Platforms.push_back(platform);
		}
}

void Room::addKey(Vector2f _position, Vector2f _scale) {
	Key* key = new Key(_position, _scale);
	this->m_Keys->push_back(key);
}

//void Room::addMusic(string _path) {
//	if (!this->m_Music.openFromFile(_path))
//		return;
//	m_Music.setLoop(true);
//	m_Music.setVolume(25.0f);
//}

void Room::draw(RenderWindow* _window) {
	_window->draw(this->m_BackgroundSprite);

	for (Platform* _platform : this->m_Platforms)
		_platform->draw(_window);

	for (auto it = this->m_Keys->begin(); it != this->m_Keys->end(); ++it) {
		Key* key = *it;
		key->draw(_window);
	}
}