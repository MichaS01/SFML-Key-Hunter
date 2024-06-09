#include "Level.h"
#include "GameManager.h"

// Konstruktor inicjalizuj�cy poziom z menad�erem gry
Level::Level(GameManager* _gameManager) {
    this->m_Size.x = 0; // Ustawia pocz�tkowy rozmiar poziomu na 0
    this->m_Size.y = 0; // Ustawia pocz�tkowy rozmiar poziomu na 0
    this->m_Keys = 0; // Ustawia liczb� kluczy na 0
    this->m_GameManager = _gameManager; // Przypisuje menad�era gry
}

// Konstruktor inicjalizuj�cy poziom z menad�erem gry, rozmiarem i typem poziomu
Level::Level(GameManager* _gameManager, int _x, int _y, int _start, int _levelType)
    : m_GameManager(_gameManager) // Inicjalizacja listy inicjalizacyjnej
{
    this->m_Size.x = _x; // Ustawia szeroko�� poziomu
    this->m_Size.y = _y; // Ustawia wysoko�� poziomu

    m_Rooms.resize(_y); // Zmienia rozmiar wektora pokoi na wysoko�� poziomu

    // Tworzy �cie�k� do zasob�w graficznych poziomu
    string levelBackground = "Assets/Graphics/Maps/#" + to_string(_levelType) + "/";

    // Inicjalizuje ka�dy pok�j w poziomie
    for (int y = 0; y < this->m_Size.y; y++) {
        m_Rooms[y].resize(_x); // Zmienia rozmiar wektora pokoi na szeroko�� poziomu
        for (int x = 0; x < this->m_Size.x; x++) {
            // Generuje losowy identyfikator pokoju i tworzy �cie�k� do pliku graficznego
            string levelId = to_string(rand() % this->m_BackgroundLevels[_levelType]);
            if (levelId.length() == 1) levelId = "0" + levelId;
            this->m_Rooms[y][x] = new Room(levelBackground + levelId + ".png"); // Tworzy nowy pok�j
        }
    }

    // Ustawia pok�j pocz�tkowy, je�li startowy indeks jest prawid�owy
    if (_start >= 0 && _start < this->m_Size.x * this->m_Size.y) {
        this->m_StartRoom = this->m_Rooms[_start / this->m_Size.x][_start % this->m_Size.x];
        m_CurrentRoomId = _start; // Ustawia bie��cy pok�j
    }
}

// Funkcja dodaj�ca klucz do poziomu
void Level::addKey(void) {
    this->m_Keys++; // Zwi�ksza liczb� kluczy o 1
}

// Funkcja usuwaj�ca klucz z poziomu
void Level::remKey(void) {
    this->m_Keys--; // Zmniejsza liczb� kluczy o 1
}

// Funkcja dodaj�ca pok�j do poziomu
void Level::addRoom(int _idx, vector<CollisionObjectAdder> _platformAdder) {
    // Sprawdza, czy indeks pokoju jest prawid�owy
    if (!(_idx >= 0 && _idx < this->m_Size.x * this->m_Size.y))
        return;

    Room* selectedRoom = this->m_Rooms[_idx / this->m_Size.x][_idx % this->m_Size.x]; // Pobiera wskazany pok�j
    // Dodaje obiekty kolizyjne do pokoju
    for (CollisionObjectAdder& pa : _platformAdder) {
        switch (pa.m_Type) {
        case CollisionObjectAdder::COLLISIONOBJECTTYPE::PLATFORM:
            selectedRoom->addPlatform(pa.m_Position, pa.m_Scale, pa.m_Amount); // Dodaje platform�
            break;

        case CollisionObjectAdder::COLLISIONOBJECTTYPE::KEY:
            selectedRoom->addKey(pa.m_Position, pa.m_Scale); // Dodaje klucz
            this->m_Keys++; // Zwi�ksza liczb� kluczy o 1
            break;
        }
    }
}

// Funkcja dodaj�ca muzyk� do poziomu
void Level::addMusic(string _path) {
    if (!this->m_Music.openFromFile(_path))
        return; // Je�li nie uda�o si� za�adowa� pliku muzycznego, zako�cz dzia�anie funkcji
    m_Music.setLoop(true); // Ustawia muzyk� na zap�tlanie
    m_Music.setVolume(25.0f); // Ustawia g�o�no�� muzyki
}

// Funkcja zmieniaj�ca pok�j w podanym kierunku
int Level::changeRoom(int _direction) {
    switch (_direction) {
    case DIRECTION::UP:
        if (this->m_CurrentRoomId - this->m_Size.x >= 0)
            this->m_CurrentRoomId -= this->m_Size.x; // Zmienia pok�j w g�r�
        else return 0;
        break;
    case DIRECTION::DOWN:
        if (this->m_CurrentRoomId + this->m_Size.x < this->m_Size.x * this->m_Size.y)
            this->m_CurrentRoomId += this->m_Size.x; // Zmienia pok�j w d�
        else return 0;
        break;
    case DIRECTION::LEFT:
        if (this->m_CurrentRoomId % this->m_Size.x - 1 >= 0)
            this->m_CurrentRoomId--; // Zmienia pok�j w lewo
        else return 0;
        break;
    case DIRECTION::RIGHT:
        if (this->m_CurrentRoomId % this->m_Size.x + 1 < this->m_Size.x)
            this->m_CurrentRoomId++; // Zmienia pok�j w prawo
        else return 0;
        break;
    }
    std::cout << m_CurrentRoomId << std::endl; // Wypisuje identyfikator bie��cego pokoju
    std::cout << m_CurrentRoomId / this->m_Size.x << " " << m_CurrentRoomId % this->m_Size.x << std::endl; // Wypisuje wsp�rz�dne bie��cego pokoju
    return 1;
}

// Funkcja zarz�dzaj�ca muzyk� w zale�no�ci od stanu gry
void Level::manageMusic() {
    switch (this->m_GameManager->getGameStatus()) {
    case GameManager::GAMESTATE::PLAYING:
        if (this->m_Music.getStatus() != Music::Status::Playing)
            this->m_Music.play(); // Odtwarza muzyk�, je�li gra jest w stanie gry
        break;

    case GameManager::GAMESTATE::PAUSED:
        if (this->m_Music.getStatus() == Music::Status::Playing)
            this->m_Music.pause(); // Wstrzymuje muzyk�, je�li gra jest w stanie pauzy
        break;

    default:
        this->m_Music.stop(); // Zatrzymuje muzyk� w pozosta�ych stanach
        break;
    }
}

// Funkcja renderuj�ca bie��cy pok�j na podanym oknie renderowania
void Level::render(RenderWindow* _window) {
    this->m_Rooms[m_CurrentRoomId / this->m_Size.x][m_CurrentRoomId % this->m_Size.x]->draw(_window); // Renderuje bie��cy pok�j
}
