#include "Key.h" // Do³¹cza plik nag³ówkowy Key

// Konstruktor klasy Key, który inicjalizuje pozycjê i rozmiar klucza
Key::Key(Vector2f _position, Vector2f _scale) {
    this->m_Position = _position; // Ustawia pozycjê klucza
    this->m_Size = _scale; // Ustawia rozmiar klucza

    // £aduje teksturê klucza z pliku
    if (!m_Texture.loadFromFile("Assets/Graphics/Key.png"))
        return; // Jeœli nie uda³o siê za³adowaæ tekstury, zakoñcz dzia³anie konstruktora

    this->m_Sprite.setTexture(m_Texture); // Ustawia teksturê sprite'a
    this->m_Sprite.setPosition(m_Position); // Ustawia pozycjê sprite'a
    this->m_Sprite.setScale(m_Size); // Ustawia skalê sprite'a
}
