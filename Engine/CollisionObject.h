#pragma once // Zapewnia, �e ten plik nag��wkowy jest do��czany tylko raz podczas kompilacji

#include "Settings.h" // Do��cza plik nag��wkowy Settings

// Klasa CollisionObject reprezentuje obiekt, kt�ry mo�e bra� udzia� w kolizjach
class CollisionObject {
protected:
    Vector2f m_Position, m_Size; // Pozycja i rozmiar obiektu kolizji
    Texture m_Texture; // Tekstura obiektu kolizji
    Sprite m_Sprite; // Sprite reprezentuj�cy obiekt kolizji

public:
    // Ustawia pozycj� obiektu kolizji
    void setPosition(Vector2f);

    // Zwraca sprite obiektu kolizji
    Sprite getSprite(void) { return this->m_Sprite; }

    // Zwraca pozycj� sprite'a obiektu kolizji
    Vector2f getPosition(void) { return this->m_Sprite.getPosition(); }

    // Zwraca collider (ramk� ograniczaj�c�) sprite'a obiektu kolizji
    FloatRect getCollider() const { return this->m_Sprite.getGlobalBounds(); }

    // Rysuje obiekt kolizji na podanym oknie renderowania
    void draw(RenderWindow*);
};
