#pragma once
#include "Room.h"

class Level {
protected:
	enum LEVELS {
		DARKFOREST
	};

private:

	int m_BackgroundLevels[1] = { 20 };
	int m_Keys = 0;

	vector<vector<Room*>> m_Rooms;
	Room* m_StartRoom = nullptr;
	Vector2i m_Size;
	int m_CurrentRoomId = -1;
	class GameManager* m_GameManager;
	Music m_Music;
public:
	enum DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Level(GameManager*);
	Level(GameManager*, int, int, int, int);

	Room* getCurrentRoom(void) { return this->m_Rooms[m_CurrentRoomId / this->m_Size.x][m_CurrentRoomId % this->m_Size.x]; }

	int getKeys(void) { return this->m_Keys; }
	void addKey(void);
	void remKey(void);

	void addRoom(int, vector<CollisionObjectAdder>);
	void addMusic(string);
	int changeRoom(int);
	void manageMusic(void);

	void render(RenderWindow*);	
};