#include "Level.h"
#include "GameManager.h"

Level::Level(GameManager* _gameManager) {
	this->m_Size.x = 0;
	this->m_Size.y = 0;
	this->m_Keys = 0;
	this->m_GameManager = _gameManager;
}

Level::Level(GameManager* _gameManager, int _x, int _y, int _start, int _levelType)
	: m_GameManager(_gameManager)
{
	this->m_Size.x = _x;
	this->m_Size.y = _y;

	m_Rooms.resize(_y);
	
	string levelBackground = "Assets/Graphics/Maps/#" + to_string(_levelType);
		levelBackground += "/";

	for (int y = 0; y < this->m_Size.y; y++) {
		m_Rooms[y].resize(_x);
		for (int x = 0; x < this->m_Size.x; x++) {
			string levelId = to_string(rand() % this->m_BackgroundLevels[_levelType]);
			if (levelId.length() == 1) levelId = "0" + levelId;
			this->m_Rooms[y][x] = new Room(levelBackground + levelId + ".png");
		}
	}

	if (_start >= 0 &&
		_start < this->m_Size.x * this->m_Size.y) {
		//!_start ? this->m_StartRoom = this->m_Rooms[0][0] : this->m_StartRoom = this->m_Rooms[(_start - 1) % this->m_Size.x][(_start - 1) / this->m_Size.x];
		this->m_StartRoom = this->m_Rooms[_start / this->m_Size.x][_start % this->m_Size.x];
		m_CurrentRoomId = _start;
	}
}

void Level::addKey(void) {
	this->m_Keys++;
}

void Level::remKey(void) {
	this->m_Keys--;
}

void Level::addRoom(int _idx, vector<CollisionObjectAdder> _platformAdder) {
	if (!(_idx >= 0 &&
		_idx < this->m_Size.x * this->m_Size.y))
		return;

	Room* selectedRoom = this->m_Rooms[_idx / this->m_Size.x][_idx % this->m_Size.x];
	//!_idx ? selectedRoom = this->m_Rooms[0][0] : selectedRoom = this->m_Rooms[(_idx - 1) % this->m_Size.x][(_idx - 1) / this->m_Size.x];
	for (CollisionObjectAdder& pa : _platformAdder) {
		switch (pa.m_Type) {
		case CollisionObjectAdder::COLLISIONOBJECTTYPE::PLATFORM:
			selectedRoom->addPlatform(pa.m_Position, pa.m_Scale, pa.m_Amount);
			break;

		case CollisionObjectAdder::COLLISIONOBJECTTYPE::KEY:
			selectedRoom->addKey(pa.m_Position, pa.m_Scale);
			this->m_Keys++;
			break;
		}
	}
}

void Level::addMusic(string _path) {
	if (!this->m_Music.openFromFile(_path))
		return;
	m_Music.setLoop(true);
	m_Music.setVolume(25.0f);
}

int Level::changeRoom(int _direction) {
	switch (_direction) {
	case DIRECTION::UP:
		if (this->m_CurrentRoomId - this->m_Size.x >= 0)
			this->m_CurrentRoomId -= this->m_Size.x;
		else return 0;
		break;
	case DIRECTION::DOWN:
		if (this->m_CurrentRoomId + this->m_Size.x < this->m_Size.x * this->m_Size.y)
			this->m_CurrentRoomId += this->m_Size.x;
		else return 0;
		break;
	case DIRECTION::LEFT:
		if (this->m_CurrentRoomId % this->m_Size.x - 1 >= 0)
			this->m_CurrentRoomId--;
		else return 0;
		break;
	case DIRECTION::RIGHT:
		if (this->m_CurrentRoomId % this->m_Size.x + 1 < this->m_Size.x)
			this->m_CurrentRoomId++;
		else return 0;
		break;
	}
	std::cout << m_CurrentRoomId << std::endl;
	std::cout << m_CurrentRoomId / this->m_Size.x << " " << m_CurrentRoomId % this->m_Size.x << std::endl;
	return 1;
}

void Level::manageMusic() {

	switch (this->m_GameManager->getGameStatus()) {
	case GameManager::GAMESTATE::PLAYING:
		if (this->m_Music.getStatus() != Music::Status::Playing)
			this->m_Music.play();
		break;

	case GameManager::GAMESTATE::PAUSED:
		if (this->m_Music.getStatus() == Music::Status::Playing)
			this->m_Music.pause();
		break;

	default:
		this->m_Music.stop();
		break;
	}
}

void Level::render(RenderWindow* _window) {
	this->m_Rooms[m_CurrentRoomId / this->m_Size.x][m_CurrentRoomId % this->m_Size.x]->draw(_window);	
}