#pragma once // Zapewnia, �e ten plik nag��wkowy jest do��czany tylko raz podczas kompilacji

#include "Room.h" // Do��cza plik nag��wkowy Room

// Klasa Level reprezentuje poziom w grze, sk�adaj�cy si� z wielu pokoi
class Level {
protected:
    // Enum reprezentuj�cy r�ne poziomy
    enum LEVELS {
        DARKFOREST
    };

private:
    int m_BackgroundLevels[1] = { 20 }; // Tablica przechowuj�ca poziomy t�a (na razie tylko jeden poziom)
    int m_Keys = 0; // Liczba kluczy zebranych na poziomie

    vector<vector<Room*>> m_Rooms; // Dwuwymiarowy wektor przechowuj�cy wska�niki do pokoi
    Room* m_StartRoom = nullptr; // Wska�nik na pocz�tkowy pok�j poziomu
    Vector2i m_Size; // Rozmiar poziomu (liczba pokoi w poziomie i pionie)
    int m_CurrentRoomId = -1; // Identyfikator bie��cego pokoju
    class GameManager* m_GameManager; // Wska�nik do menad�era gry
    Music m_Music; // Obiekt zarz�dzaj�cy muzyk� poziomu

public:
    // Enum reprezentuj�cy kierunki zmiany pokoju
    enum DIRECTION {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    // Konstruktor poziomu przyjmuj�cy wska�nik do menad�era gry
    Level(GameManager*);
    // Konstruktor poziomu przyjmuj�cy wska�nik do menad�era gry oraz rozmiar poziomu i pocz�tkowy pok�j
    Level(GameManager*, int, int, int, int);

    // Zwraca wska�nik do bie��cego pokoju
    Room* getCurrentRoom(void) { return this->m_Rooms[m_CurrentRoomId / this->m_Size.x][m_CurrentRoomId % this->m_Size.x]; }

    // Zwraca liczb� kluczy
    int getKeys(void) { return this->m_Keys; }
    // Dodaje klucz do licznika
    void addKey(void);
    // Usuwa klucz z licznika
    void remKey(void);

    // Dodaje pok�j do poziomu
    void addRoom(int, vector<CollisionObjectAdder>);
    // Dodaje muzyk� do poziomu
    void addMusic(string);
    // Zmienia pok�j na podany kierunek
    int changeRoom(int);
    // Zarz�dza odtwarzaniem muzyki
    void manageMusic(void);

    // Renderuje poziom na podanym oknie renderowania
    void render(RenderWindow*);
};
