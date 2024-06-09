#pragma once // Zapewnia, ¿e ten plik nag³ówkowy jest do³¹czany tylko raz podczas kompilacji
#include "Settings.h" // Do³¹cza plik nag³ówkowy Settings

class GameManager; // Deklaracja wstêpna klasy GameManager

// Klasa Menu reprezentuje abstrakcyjne menu w grze
class Menu {
private:
    // W sekcji prywatnej nie ma ¿adnych danych cz³onkowskich
public:
    // Konstruktor domyœlny
    Menu() {};

    // Wirtualny destruktor
    virtual ~Menu() {};

    // Czysto wirtualna funkcja obs³uguj¹ca wejœcie u¿ytkownika
    virtual void handleInput(RenderWindow*, Event&) = 0;

    // Czysto wirtualna funkcja aktualizuj¹ca stan menu
    virtual void update() = 0;

    // Czysto wirtualna funkcja renderuj¹ca menu na podanym oknie renderowania
    virtual void render(RenderWindow*) = 0;
};
