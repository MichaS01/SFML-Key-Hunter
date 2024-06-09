#pragma once // Zapewnia, �e ten plik nag��wkowy jest do��czany tylko raz podczas kompilacji

#include "Player.h" // Do��cza plik nag��wkowy Player
#include "../Levels/Levels.h" // Do��cza plik nag��wkowy Levels
#include "../Menus/MenusList.h" // Do��cza plik nag��wkowy MenusList

class Menu; // Deklaracja wst�pna klasy Menu

// Klasa GameManager zarz�dza stanem gry i jej elementami
class GameManager {
private:
    int m_GameState; // Zmienna przechowuj�ca stan gry
    HWND m_WindowHandler; // Uchwyt okna gry

    Player* m_Player; // Wska�nik na obiekt gracza
    Level* m_CurrentLevel; // Wska�nik na bie��cy poziom
    Menu* m_Menu; // Wska�nik na aktualne menu
    RenderWindow* m_Window; // Wska�nik na okno renderowania

    int m_GameTime; // Zmienna przechowuj�ca czas gry
    float m_ElapsedTime; // Zmienna przechowuj�ca czas, jaki up�yn�� podczas liczenia

    Clock m_Clock; // Obiekt przechowuj�cy zegar
    Event m_Event; // Obiekt przechowuj�cy zdarzenia

    // �aduje ustawienia gry
    void loadSettings(void);
    // Zarz�dza zdarzeniami w grze
    void eventManager(void);
    // Renderuje aktualny stan gry
    void render(void);

public:
    // Enumaracja stan�w gry
    enum GAMESTATE {
        MAINMENU,
        PLAYING,
        PAUSED,
        OVER
    };

    // Konstruktor klasy GameManager
    GameManager(void);

    // Zwraca wska�nik na bie��cy poziom
    Level* getCurrentLevel(void) { return this->m_CurrentLevel; }
    // Zwraca wska�nik na obiekt gracza
    Player* getPlayer(void) { return this->m_Player; }

    // Zwraca aktualny stan gry
    int getGameStatus(void) { return this->m_GameState; };

    // Ustawia menu i jego stan
    void setMenu(Menu*, int);
    // Restartuje gr�
    void restartGame(void);

    // Koniec gry
    void gameOver(void);

    // Zmienia pok�j na podany indeks
    void changeRoom(int);
};
