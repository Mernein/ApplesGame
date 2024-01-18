#pragma once
#include <string>

namespace ApplesGame
{
	const std::string RESOURCES_PATH = "Resources/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const float INITIAL_SPEED = 100.f; // Pixels per frame
	const float PLAYER_SIZE = 20.f;
	const float ACCELERATION = 20.f; // Pixels per seconds per seconds
	const int NUM_APPLES = 20;
	const float APPLE_SIZE = 20.f;
	const float PAUSE_LENGTH = 3.f;
	const int NUM_ROCKS = 10;
	const float ROCK_SIZE = 15.f;

	const int APPLES[NUM_APPLES] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
	const int ROCKS[NUM_ROCKS] = { 0,1,2,3,4,5,6,7,8,9 };
}