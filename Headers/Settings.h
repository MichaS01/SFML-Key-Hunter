#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

const std::string GAME_TITLE = "Key Hunter";

const int WINDOW_X = 800;
const int WINDOW_Y = 600;
const int FRAMERATE_LIMIT = 144;
const int FALL_TIME = 200;

const float GRAVITY = 150.0f;
const float JUMP_VELOCITY = -200.0f;
const float FRAME_TIME = 0.25f;
const float PLAYER_SPEED = 100.0f;