#include "Platform.h" // Do³¹cza plik nag³ówkowy Platform

// Konstruktor klasy Platform, który inicjalizuje pozycjê i rozmiar platformy
Platform::Platform(Vector2f _position, Vector2f _scale) {
    this->m_Position = _position; // Ustawia pozycjê platformy
    this->m_Size = _scale; // Ustawia rozmiar platformy

    // £aduje teksturê platformy z pliku
    if (!m_Texture.loadFromFile("Assets/Graphics/Platform.png"))
        return; // Jeœli nie uda³o siê za³adowaæ tekstury, zakoñcz dzia³anie konstruktora

    this->m_Sprite.setTexture(m_Texture); // Ustawia teksturê sprite'a
    this->m_Sprite.setPosition(m_Position); // Ustawia pozycjê sprite'a
    this->m_Sprite.setScale(m_Size); // Ustawia skalê sprite'a
}
