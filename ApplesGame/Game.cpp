#include "Game.h"
#include "cassert"

namespace ApplesGame
{
	void StartPlayingState(Game& game)
	{
		SetPlayerPosition(game.player, { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
		SetPlayerSpeed(game.player, INITIAL_SPEED);
		SetPlayerDirection(game.player, PlayerDirection::Right);

		// Init apples
		for (const auto apples : APPLES)
		{
			SetApplePosition(game.apples[apples], GetRandomPositionInRectangle(game.screenRect));
		}

		// Init rocks
		for (const auto rocks : ROCKS)
		{
			SetRockPosition(game.rocks[rocks], GetRandomPositionInRectangle(game.screenRect));
		}

		game.numEatenApples = 0;
		game.isGameFinished = false;
		game.timeSinceGameFinish = 0;
		game.scoreText.setString("Apples eaten: " + std::to_string(game.numEatenApples));
	}
	
	void UpdatePlayingState(Game& game, float deltaTime)
	{
		// Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			SetPlayerDirection(game.player, PlayerDirection::Right);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			SetPlayerDirection(game.player, PlayerDirection::Up);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			SetPlayerDirection(game.player, PlayerDirection::Left);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			SetPlayerDirection(game.player, PlayerDirection::Down);
		}

		UpdatePlayer(game.player, deltaTime);

		// Find player collision with apples
		for (const auto apples : APPLES)
		{
			if (DoShapesCollide(GetPlayerCollider(game.player), GetAppleCollider(game.apples[apples])))
			{
				SetApplePosition(game.apples[apples], GetRandomPositionInRectangle(game.screenRect));
				++game.numEatenApples;
				SetPlayerSpeed(game.player, GetPlayerSpeed(game.player) + ACCELERATION);
				game.soundAppleEat.play();
				game.scoreText.setString("Apples eaten: " + std::to_string(game.numEatenApples));
			}
		}

		// Find player collision with rocks
		for (const auto rocks : ROCKS)
		{
			if (DoShapesCollide(GetPlayerCollider(game.player), GetRockCollider(game.rocks[rocks])))
			{
				StartGameoverState(game);
			}
		}

		// Check screen borders collision
		if (!DoShapesCollide(GetPlayerCollider(game.player), game.screenRect))
		{
			StartGameoverState(game);
		}
	}
	
	void StartGameoverState(Game& game)
	{
		game.isGameFinished = true;
		game.timeSinceGameFinish = 0.f;
		game.soundGameOver.play();
		game.gameOverScoreText.setString("Your scores: " + std::to_string(game.numEatenApples));
	}

	void UpdateGameoverState(Game& game, float deltaTime)
	{
		if (game.timeSinceGameFinish <= PAUSE_LENGTH)
		{
			game.timeSinceGameFinish += deltaTime;
			game.background.setFillColor(sf::Color::Red);
		}
		else
		{
			// Reset background
			game.background.setFillColor(sf::Color::Black);

			StartPlayingState(game);
		}
	}

	void InitGame(Game& game)
	{
		assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(game.appleEat.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(game.gameOver.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Bold.ttf"));

		game.screenRect = { 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT };

		InitPlayer(game.player, game);

		// Init apples
		for (const auto apples : APPLES)
		{
			InitApple(game.apples[apples], game);
		}

		// Init rocks
		for (const auto rocks : ROCKS)
		{
			InitRock(game.rocks[rocks], game);
		}
		
		// Init background
		game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		game.background.setFillColor(sf::Color::Black);
		game.background.setPosition(0.f, 0.f);

		// Init sounds
		game.soundAppleEat.setBuffer(game.appleEat);
		game.soundGameOver.setBuffer(game.gameOver);

		// Init texts
		game.scoreText.setFont(game.font);
		game.scoreText.setCharacterSize(20);
		game.scoreText.setFillColor(sf::Color::White);
		game.scoreText.setPosition(20.f, 10.f);

		game.controlsHintText.setFont(game.font);
		game.controlsHintText.setCharacterSize(20);
		game.controlsHintText.setFillColor(sf::Color::White);
		game.controlsHintText.setString("Use arrows to move, ESC to exit");
		game.controlsHintText.setPosition(SCREEN_WIDTH - game.controlsHintText.getGlobalBounds().width - 20.f, 10.f);

		game.gameOverText.setFont(game.font);
		game.gameOverText.setCharacterSize(100);
		game.gameOverText.setFillColor(sf::Color::White);
		game.gameOverText.setPosition(SCREEN_WIDTH / 2.f - 200.f, SCREEN_HEIGHT / 2.f - 50.f);
		game.gameOverText.setString("Game Over");

		game.gameOverScoreText.setFont(game.font);
		game.gameOverScoreText.setCharacterSize(30);
		game.gameOverScoreText.setFillColor(sf::Color::White);
		game.gameOverScoreText.setString("Your score: " + std::to_string(game.numEatenApples));
		game.gameOverScoreText.setPosition(SCREEN_WIDTH / 2.f - game.controlsHintText.getGlobalBounds().width / 4.f, SCREEN_HEIGHT / 2.f + 50.f);
		
		StartPlayingState(game);
	}

	void UpdateGame(Game& game, float deltaTime)
	{
		// Update game state
		if (!game.isGameFinished)
		{
			UpdatePlayingState(game, deltaTime);
		}
		else
		{
			UpdateGameoverState(game, deltaTime);
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window)
	{
		window.draw(game.background);
		DrawPlayer(game.player, window);
		
		for (const auto apples : APPLES)
		{
			DrawApple(game.apples[apples], window);
		}

		for (const auto rocks : ROCKS)
		{
			DrawRock(game.rocks[rocks], window);
		}

		// Draw texts
		if (!game.isGameFinished)
		{
			window.draw(game.scoreText);
			window.draw(game.controlsHintText);
		}
		else
		{
			window.draw(game.gameOverText);
			window.draw(game.gameOverScoreText);
		}
	}

	void DeinializeGame(Game& game)
	{

	}
}