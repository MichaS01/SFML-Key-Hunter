#pragma once

#include <SFML/Graphics.hpp> // Biblioteka SFML do obs�ugi grafiki
#include <SFML/Audio.hpp> // Biblioteka SFML do obs�ugi d�wi�ku
#include <vector> // Standardowa biblioteka C++ do obs�ugi wektor�w
#include <iostream> // Standardowa biblioteka C++ do obs�ugi strumieni wej�cia/wyj�cia
#include <time.h> // Biblioteka C do obs�ugi czasu
#include <Windows.h> // Biblioteka Windows.h do obs�ugi funkcji systemowych systemu Windows
#include <conio.h> // Biblioteka conio.h do obs�ugi funkcji do kontroli konsoli

// Deklaracje u�ywanych typ�w danych z biblioteki SFML
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

using std::vector; // U�ycie przestrzeni nazw std do u�atwienia korzystania z wektor�w
using std::string; // U�ycie przestrzeni nazw std do u�atwienia korzystania ze string�w
using std::to_string; // U�ycie przestrzeni nazw std do u�atwienia konwersji typ�w liczbowych na stringi
using std::remove; // U�ycie przestrzeni nazw std do u�atwienia usuwania element�w z kontener�w

#define DISABLE_TASKBAR TRUE // Sta�a definuj�ca wy��czenie paska zada�
#define ENABLE_CONSOLE FALSE // Sta�a definuj�ca wy��czenie konsoli
#define DEBUGGING FALSE // Sta�a definuj�ca tryb debugowania

const string GAME_TITLE = "Key Hunter"; // Tytu� gry

const int WINDOW_X = 800; // Szeroko�� okna
const int WINDOW_Y = 600; // Wysoko�� okna
const int FRAMERATE_LIMIT = 144; // Limit klatek na sekund�
const int FALL_TIME = 200; // Czas upadku

const float GRAVITY = 150.0f; // Sta�a grawitacji
const float JUMP_VELOCITY = -200.0f; // Sta�a pr�dko�ci skoku
const float FRAME_TIME = 0.25f; // Sta�a czasu trwania klatki animacji
const float PLAYER_SPEED = 100.0f; // Sta�a pr�dko�ci gracza
