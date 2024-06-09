#pragma once // Zapewnia, �e ten plik nag��wkowy jest do��czany tylko raz podczas kompilacji
#include "Settings.h" // Do��cza plik nag��wkowy Settings

class GameManager; // Deklaracja wst�pna klasy GameManager

// Klasa Menu reprezentuje abstrakcyjne menu w grze
class Menu {
private:
    // W sekcji prywatnej nie ma �adnych danych cz�onkowskich
public:
    // Konstruktor domy�lny
    Menu() {};

    // Wirtualny destruktor
    virtual ~Menu() {};

    // Czysto wirtualna funkcja obs�uguj�ca wej�cie u�ytkownika
    virtual void handleInput(RenderWindow*, Event&) = 0;

    // Czysto wirtualna funkcja aktualizuj�ca stan menu
    virtual void update() = 0;

    // Czysto wirtualna funkcja renderuj�ca menu na podanym oknie renderowania
    virtual void render(RenderWindow*) = 0;
};
