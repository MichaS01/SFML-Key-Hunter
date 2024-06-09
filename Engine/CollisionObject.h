#pragma once // Zapewnia, ¿e ten plik nag³ówkowy jest do³¹czany tylko raz podczas kompilacji

#include "Settings.h" // Do³¹cza plik nag³ówkowy Settings

// Klasa CollisionObject reprezentuje obiekt, który mo¿e braæ udzia³ w kolizjach
class CollisionObject {
protected:
    Vector2f m_Position, m_Size; // Pozycja i rozmiar obiektu kolizji
    Texture m_Texture; // Tekstura obiektu kolizji
    Sprite m_Sprite; // Sprite reprezentuj¹cy obiekt kolizji

public:
    // Ustawia pozycjê obiektu kolizji
    void setPosition(Vector2f);

    // Zwraca sprite obiektu kolizji
    Sprite getSprite(void) { return this->m_Sprite; }

    // Zwraca pozycjê sprite'a obiektu kolizji
    Vector2f getPosition(void) { return this->m_Sprite.getPosition(); }

    // Zwraca collider (ramkê ograniczaj¹c¹) sprite'a obiektu kolizji
    FloatRect getCollider() const { return this->m_Sprite.getGlobalBounds(); }

    // Rysuje obiekt kolizji na podanym oknie renderowania
    void draw(RenderWindow*);
};
