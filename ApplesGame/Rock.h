#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	struct Rock
	{
		Position2D position;
		sf::Sprite sprite;
	};

	struct Game;

	void InitRock(Rock& rock, const Game& game);
	void SetRockPosition(Rock& rock, const Position2D& position);
	Rectangle GetRockCollider(const Rock& rock);
	void DrawRock(Rock& rock, sf::RenderWindow& window);
}