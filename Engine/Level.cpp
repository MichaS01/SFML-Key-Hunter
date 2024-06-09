#include "Level.h"
#include "GameManager.h"

// Konstruktor inicjalizuj¹cy poziom z menad¿erem gry
Level::Level(GameManager* _gameManager) {
    this->m_Size.x = 0; // Ustawia pocz¹tkowy rozmiar poziomu na 0
    this->m_Size.y = 0; // Ustawia pocz¹tkowy rozmiar poziomu na 0
    this->m_Keys = 0; // Ustawia liczbê kluczy na 0
    this->m_GameManager = _gameManager; // Przypisuje menad¿era gry
}

// Konstruktor inicjalizuj¹cy poziom z menad¿erem gry, rozmiarem i typem poziomu
Level::Level(GameManager* _gameManager, int _x, int _y, int _start, int _levelType)
    : m_GameManager(_gameManager) // Inicjalizacja listy inicjalizacyjnej
{
    this->m_Size.x = _x; // Ustawia szerokoœæ poziomu
    this->m_Size.y = _y; // Ustawia wysokoœæ poziomu

    m_Rooms.resize(_y); // Zmienia rozmiar wektora pokoi na wysokoœæ poziomu

    // Tworzy œcie¿kê do zasobów graficznych poziomu
    string levelBackground = "Assets/Graphics/Maps/#" + to_string(_levelType) + "/";

    // Inicjalizuje ka¿dy pokój w poziomie
    for (int y = 0; y < this->m_Size.y; y++) {
        m_Rooms[y].resize(_x); // Zmienia rozmiar wektora pokoi na szerokoœæ poziomu
        for (int x = 0; x < this->m_Size.x; x++) {
            // Generuje losowy identyfikator pokoju i tworzy œcie¿kê do pliku graficznego
            string levelId = to_string(rand() % this->m_BackgroundLevels[_levelType]);
            if (levelId.length() == 1) levelId = "0" + levelId;
            this->m_Rooms[y][x] = new Room(levelBackground + levelId + ".png"); // Tworzy nowy pokój
        }
    }

    // Ustawia pokój pocz¹tkowy, jeœli startowy indeks jest prawid³owy
    if (_start >= 0 && _start < this->m_Size.x * this->m_Size.y) {
        this->m_StartRoom = this->m_Rooms[_start / this->m_Size.x][_start % this->m_Size.x];
        m_CurrentRoomId = _start; // Ustawia bie¿¹cy pokój
    }
}

// Funkcja dodaj¹ca klucz do poziomu
void Level::addKey(void) {
    this->m_Keys++; // Zwiêksza liczbê kluczy o 1
}

// Funkcja usuwaj¹ca klucz z poziomu
void Level::remKey(void) {
    this->m_Keys--; // Zmniejsza liczbê kluczy o 1
}

// Funkcja dodaj¹ca pokój do poziomu
void Level::addRoom(int _idx, vector<CollisionObjectAdder> _platformAdder) {
    // Sprawdza, czy indeks pokoju jest prawid³owy
    if (!(_idx >= 0 && _idx < this->m_Size.x * this->m_Size.y))
        return;

    Room* selectedRoom = this->m_Rooms[_idx / this->m_Size.x][_idx % this->m_Size.x]; // Pobiera wskazany pokój
    // Dodaje obiekty kolizyjne do pokoju
    for (CollisionObjectAdder& pa : _platformAdder) {
        switch (pa.m_Type) {
        case CollisionObjectAdder::COLLISIONOBJECTTYPE::PLATFORM:
            selectedRoom->addPlatform(pa.m_Position, pa.m_Scale, pa.m_Amount); // Dodaje platformê
            break;

        case CollisionObjectAdder::COLLISIONOBJECTTYPE::KEY:
            selectedRoom->addKey(pa.m_Position, pa.m_Scale); // Dodaje klucz
            this->m_Keys++; // Zwiêksza liczbê kluczy o 1
            break;
        }
    }
}

// Funkcja dodaj¹ca muzykê do poziomu
void Level::addMusic(string _path) {
    if (!this->m_Music.openFromFile(_path))
        return; // Jeœli nie uda³o siê za³adowaæ pliku muzycznego, zakoñcz dzia³anie funkcji
    m_Music.setLoop(true); // Ustawia muzykê na zapêtlanie
    m_Music.setVolume(25.0f); // Ustawia g³oœnoœæ muzyki
}

// Funkcja zmieniaj¹ca pokój w podanym kierunku
int Level::changeRoom(int _direction) {
    switch (_direction) {
    case DIRECTION::UP:
        if (this->m_CurrentRoomId - this->m_Size.x >= 0)
            this->m_CurrentRoomId -= this->m_Size.x; // Zmienia pokój w górê
        else return 0;
        break;
    case DIRECTION::DOWN:
        if (this->m_CurrentRoomId + this->m_Size.x < this->m_Size.x * this->m_Size.y)
            this->m_CurrentRoomId += this->m_Size.x; // Zmienia pokój w dó³
        else return 0;
        break;
    case DIRECTION::LEFT:
        if (this->m_CurrentRoomId % this->m_Size.x - 1 >= 0)
            this->m_CurrentRoomId--; // Zmienia pokój w lewo
        else return 0;
        break;
    case DIRECTION::RIGHT:
        if (this->m_CurrentRoomId % this->m_Size.x + 1 < this->m_Size.x)
            this->m_CurrentRoomId++; // Zmienia pokój w prawo
        else return 0;
        break;
    }
    std::cout << m_CurrentRoomId << std::endl; // Wypisuje identyfikator bie¿¹cego pokoju
    std::cout << m_CurrentRoomId / this->m_Size.x << " " << m_CurrentRoomId % this->m_Size.x << std::endl; // Wypisuje wspó³rzêdne bie¿¹cego pokoju
    return 1;
}

// Funkcja zarz¹dzaj¹ca muzyk¹ w zale¿noœci od stanu gry
void Level::manageMusic() {
    switch (this->m_GameManager->getGameStatus()) {
    case GameManager::GAMESTATE::PLAYING:
        if (this->m_Music.getStatus() != Music::Status::Playing)
            this->m_Music.play(); // Odtwarza muzykê, jeœli gra jest w stanie gry
        break;

    case GameManager::GAMESTATE::PAUSED:
        if (this->m_Music.getStatus() == Music::Status::Playing)
            this->m_Music.pause(); // Wstrzymuje muzykê, jeœli gra jest w stanie pauzy
        break;

    default:
        this->m_Music.stop(); // Zatrzymuje muzykê w pozosta³ych stanach
        break;
    }
}

// Funkcja renderuj¹ca bie¿¹cy pokój na podanym oknie renderowania
void Level::render(RenderWindow* _window) {
    this->m_Rooms[m_CurrentRoomId / this->m_Size.x][m_CurrentRoomId % this->m_Size.x]->draw(_window); // Renderuje bie¿¹cy pokój
}
