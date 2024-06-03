#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>

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

using std::vector;
using std::string;
using std::to_string;
using std::remove;

#define DISABLE_TASKBAR TRUE
#define ENABLE_CONSOLE FALSE
#define DEBUGGING FALSE

const string GAME_TITLE = "Key Hunter";

const int WINDOW_X = 800;
const int WINDOW_Y = 600;
const int FRAMERATE_LIMIT = 144;
const int FALL_TIME = 200;

const float GRAVITY = 150.0f;
const float JUMP_VELOCITY = -200.0f;
const float FRAME_TIME = 0.25f;
const float PLAYER_SPEED = 100.0f;