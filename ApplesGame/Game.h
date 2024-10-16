#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"
#include "Constants.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"

namespace ApplesGame
{
	struct Game
	{
		Rectangle screenRect;
		
		Player player;
		Apple apples[NUM_APPLES];
		Rock rocks[NUM_ROCKS];

		// Global game data
		int numEatenApples = 0;
		bool isGameFinished = false;
		float timeSinceGameFinish = 0.f;
		sf::RectangleShape background;

		// Resources
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::SoundBuffer appleEat;
		sf::SoundBuffer gameOver;

		// Sound
		sf::Sound soundAppleEat;
		sf::Sound soundGameOver;

		// Texts and fonts
		sf::Font font;
		sf::Text scoreText;
		sf::Text controlsHintText;
		sf::Text gameOverText;
		sf::Text gameOverScoreText;
	};

	void InitGame(Game& game);
	void UpdateGame(Game& game, float deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window);
	void DeinializeGame(Game& game);

	void StartPlayingState(Game& game);
	void UpdatePlayingState(Game& game, float deltaTime);

	void StartGameoverState(Game& game);
	void UpdateGameoverState(Game& game, float deltaTime);
}