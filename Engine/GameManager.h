#pragma once // Zapewnia, ¿e ten plik nag³ówkowy jest do³¹czany tylko raz podczas kompilacji

#include "Player.h" // Do³¹cza plik nag³ówkowy Player
#include "../Levels/Levels.h" // Do³¹cza plik nag³ówkowy Levels
#include "../Menus/MenusList.h" // Do³¹cza plik nag³ówkowy MenusList

class Menu; // Deklaracja wstêpna klasy Menu

// Klasa GameManager zarz¹dza stanem gry i jej elementami
class GameManager {
private:
    int m_GameState; // Zmienna przechowuj¹ca stan gry
    HWND m_WindowHandler; // Uchwyt okna gry

    Player* m_Player; // WskaŸnik na obiekt gracza
    Level* m_CurrentLevel; // WskaŸnik na bie¿¹cy poziom
    Menu* m_Menu; // WskaŸnik na aktualne menu
    RenderWindow* m_Window; // WskaŸnik na okno renderowania

    int m_GameTime; // Zmienna przechowuj¹ca czas gry
    float m_ElapsedTime; // Zmienna przechowuj¹ca czas, jaki up³yn¹³ podczas liczenia

    Clock m_Clock; // Obiekt przechowuj¹cy zegar
    Event m_Event; // Obiekt przechowuj¹cy zdarzenia

    // £aduje ustawienia gry
    void loadSettings(void);
    // Zarz¹dza zdarzeniami w grze
    void eventManager(void);
    // Renderuje aktualny stan gry
    void render(void);

public:
    // Enumaracja stanów gry
    enum GAMESTATE {
        MAINMENU,
        PLAYING,
        PAUSED,
        OVER
    };

    // Konstruktor klasy GameManager
    GameManager(void);

    // Zwraca wskaŸnik na bie¿¹cy poziom
    Level* getCurrentLevel(void) { return this->m_CurrentLevel; }
    // Zwraca wskaŸnik na obiekt gracza
    Player* getPlayer(void) { return this->m_Player; }

    // Zwraca aktualny stan gry
    int getGameStatus(void) { return this->m_GameState; };

    // Ustawia menu i jego stan
    void setMenu(Menu*, int);
    // Restartuje grê
    void restartGame(void);

    // Koniec gry
    void gameOver(void);

    // Zmienia pokój na podany indeks
    void changeRoom(int);
};
