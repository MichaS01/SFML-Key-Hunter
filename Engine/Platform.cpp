#include "Platform.h" // Do��cza plik nag��wkowy Platform

// Konstruktor klasy Platform, kt�ry inicjalizuje pozycj� i rozmiar platformy
Platform::Platform(Vector2f _position, Vector2f _scale) {
    this->m_Position = _position; // Ustawia pozycj� platformy
    this->m_Size = _scale; // Ustawia rozmiar platformy

    // �aduje tekstur� platformy z pliku
    if (!m_Texture.loadFromFile("Assets/Graphics/Platform.png"))
        return; // Je�li nie uda�o si� za�adowa� tekstury, zako�cz dzia�anie konstruktora

    this->m_Sprite.setTexture(m_Texture); // Ustawia tekstur� sprite'a
    this->m_Sprite.setPosition(m_Position); // Ustawia pozycj� sprite'a
    this->m_Sprite.setScale(m_Size); // Ustawia skal� sprite'a
}
