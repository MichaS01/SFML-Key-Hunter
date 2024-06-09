#pragma once // Zapewnia, ¿e ten plik nag³ówkowy jest do³¹czany tylko raz podczas kompilacji

#include "Room.h" // Do³¹cza plik nag³ówkowy Room

// Klasa Level reprezentuje poziom w grze, sk³adaj¹cy siê z wielu pokoi
class Level {
protected:
    // Enum reprezentuj¹cy ró¿ne poziomy
    enum LEVELS {
        DARKFOREST
    };

private:
    int m_BackgroundLevels[1] = { 20 }; // Tablica przechowuj¹ca poziomy t³a (na razie tylko jeden poziom)
    int m_Keys = 0; // Liczba kluczy zebranych na poziomie

    vector<vector<Room*>> m_Rooms; // Dwuwymiarowy wektor przechowuj¹cy wskaŸniki do pokoi
    Room* m_StartRoom = nullptr; // WskaŸnik na pocz¹tkowy pokój poziomu
    Vector2i m_Size; // Rozmiar poziomu (liczba pokoi w poziomie i pionie)
    int m_CurrentRoomId = -1; // Identyfikator bie¿¹cego pokoju
    class GameManager* m_GameManager; // WskaŸnik do menad¿era gry
    Music m_Music; // Obiekt zarz¹dzaj¹cy muzyk¹ poziomu

public:
    // Enum reprezentuj¹cy kierunki zmiany pokoju
    enum DIRECTION {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    // Konstruktor poziomu przyjmuj¹cy wskaŸnik do menad¿era gry
    Level(GameManager*);
    // Konstruktor poziomu przyjmuj¹cy wskaŸnik do menad¿era gry oraz rozmiar poziomu i pocz¹tkowy pokój
    Level(GameManager*, int, int, int, int);

    // Zwraca wskaŸnik do bie¿¹cego pokoju
    Room* getCurrentRoom(void) { return this->m_Rooms[m_CurrentRoomId / this->m_Size.x][m_CurrentRoomId % this->m_Size.x]; }

    // Zwraca liczbê kluczy
    int getKeys(void) { return this->m_Keys; }
    // Dodaje klucz do licznika
    void addKey(void);
    // Usuwa klucz z licznika
    void remKey(void);

    // Dodaje pokój do poziomu
    void addRoom(int, vector<CollisionObjectAdder>);
    // Dodaje muzykê do poziomu
    void addMusic(string);
    // Zmienia pokój na podany kierunek
    int changeRoom(int);
    // Zarz¹dza odtwarzaniem muzyki
    void manageMusic(void);

    // Renderuje poziom na podanym oknie renderowania
    void render(RenderWindow*);
};
