#pragma once

#include <SFML/Graphics.hpp> // Biblioteka SFML do obs³ugi grafiki
#include <SFML/Audio.hpp> // Biblioteka SFML do obs³ugi dŸwiêku
#include <vector> // Standardowa biblioteka C++ do obs³ugi wektorów
#include <iostream> // Standardowa biblioteka C++ do obs³ugi strumieni wejœcia/wyjœcia
#include <time.h> // Biblioteka C do obs³ugi czasu
#include <Windows.h> // Biblioteka Windows.h do obs³ugi funkcji systemowych systemu Windows
#include <conio.h> // Biblioteka conio.h do obs³ugi funkcji do kontroli konsoli

// Deklaracje u¿ywanych typów danych z biblioteki SFML
using sf::Text;
using sf::Font;
using sf::Texture;
using sf::Sprite;
using sf::RectangleShape;
using sf::RenderWindow;
using sf::IntRect;
using sf::FloatRect;
using sf::Vector2f;
using sf::Vector2i;
using sf::Event;
using sf::Color;
using sf::Mouse;
using sf::Keyboard;
using sf::Music;
using sf::Sound;
using sf::SoundBuffer;

using std::vector; // U¿ycie przestrzeni nazw std do u³atwienia korzystania z wektorów
using std::string; // U¿ycie przestrzeni nazw std do u³atwienia korzystania ze stringów
using std::to_string; // U¿ycie przestrzeni nazw std do u³atwienia konwersji typów liczbowych na stringi
using std::remove; // U¿ycie przestrzeni nazw std do u³atwienia usuwania elementów z kontenerów

#define DISABLE_TASKBAR TRUE // Sta³a definuj¹ca wy³¹czenie paska zadañ
#define ENABLE_CONSOLE FALSE // Sta³a definuj¹ca wy³¹czenie konsoli
#define DEBUGGING FALSE // Sta³a definuj¹ca tryb debugowania

const string GAME_TITLE = "Key Hunter"; // Tytu³ gry

const int WINDOW_X = 800; // Szerokoœæ okna
const int WINDOW_Y = 600; // Wysokoœæ okna
const int FRAMERATE_LIMIT = 144; // Limit klatek na sekundê
const int FALL_TIME = 200; // Czas upadku

const float GRAVITY = 150.0f; // Sta³a grawitacji
const float JUMP_VELOCITY = -200.0f; // Sta³a prêdkoœci skoku
const float FRAME_TIME = 0.25f; // Sta³a czasu trwania klatki animacji
const float PLAYER_SPEED = 100.0f; // Sta³a prêdkoœci gracza
