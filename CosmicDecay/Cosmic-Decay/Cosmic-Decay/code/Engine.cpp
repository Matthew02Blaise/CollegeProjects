#include "stdafx.h"
#include "Engine.h"
using namespace sf;




Engine::Engine()
{
	//Sounds
	shootBuffer.loadFromFile("sound/shoot.MP3");
	shootSound.setBuffer(shootBuffer);

	reloadBuffer.loadFromFile("sound/reload.WAV");
	reloadSound.setBuffer(reloadBuffer);

	reachedGoalBuffer.loadFromFile("sound/reachgoal.WAV");
	reachedGoalSound.setBuffer(reachedGoalBuffer);

	pickupBuffer.loadFromFile("sound/pickup.WAV");
	pickupSound.setBuffer(pickupBuffer);

	playerHurtBuffer.loadFromFile("sound/playerHurt.WAV");
	playerHurtSound.setBuffer(playerHurtBuffer);

	enemyHurtBuffer.loadFromFile("sound/enemyHurt.WAV");
	enemyHurtSound.setBuffer(enemyHurtBuffer);

	//Score text
	scoreFont.loadFromFile("fonts/KOMIKAP_.ttf");
	scoreText.setFont(scoreFont);
	scoreText.setString("Score = 0");
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(Color::Magenta);
	scoreText.setPosition(1500, 20);
	score = 0;

	//Shop text
	shopText.setFont(scoreFont);
	shopText.setCharacterSize(40);
	shopText.setFillColor(Color::White);
	shopText.setPosition(150, 250);
	std::stringstream shopStream;
	shopStream <<
		"1- Increased rate of fire (10 points)" <<
		"\n2- Double clip size (20 points)" <<
		"\n3- Increased sprint speed (15 points)"<<
		"\n4- Exit";
	shopText.setString(shopStream.str());

	//Invincibility timer to stop multiple collisions
	m_InvincibleTime = 0;

	// Ammo
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::Magenta);
	ammoText.setPosition(200, 20);

	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	state = State::MAIN_MENU;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Cosmic Decay",
		Style::Fullscreen);
//	m_Window.setFramerateLimit(30);
	//sf::Window::setFramerateLimit(unsigned int 	limit)


	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_MainView.setCenter(resolution.x / 2, resolution.y / 2);

	// Two lines below used to create zoomed our screenshots for the book
	//m_BGMainView.zoom(2.5);
	m_MainView.zoom(0.3);
	m_HudView.reset(
		FloatRect(0, 0, resolution.x, resolution.y));

	//Create bullet and clip
	currentBullet = 0;
	bulletsSpare = 24;
	bulletsInClip = 6;
	clipSize = 6;
	fireRate = 1;

	

	// Hide the mouse pointer and replace it with crosshair
	m_Window.setMouseCursorVisible(false);
	textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);


	// Can this graphics card use shaders?
	if (!sf::Shader::isAvailable())
	{
		// Time to get a new PC
		m_Window.close();
	}

	m_BackgroundTexture = TextureHolder::GetTexture(
		"graphics/background.png");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	// Load the texture for the background vertex array

	std::string currentLevelFile = m_levelManager.getLevelToLoad();

	cout << currentLevelFile << endl;

	
	m_TextureTiles = TextureHolder::GetTexture(
		"graphics/tiles_sheet.png");
	
	

	//Main menu background
	textureMainMenu = TextureHolder::GetTexture("graphics/cosmicDecayPoster.png");
	spriteMainMenu.setTexture(textureMainMenu);
	spriteMainMenu.setPosition(0, 0);
	spriteMainMenu.setScale(0.4, 0.75);

	//Instructions Image background
	textureInstructions = TextureHolder::GetTexture("graphics/instructionsImage.png");
	spriteInstructions.setTexture(textureInstructions);
	spriteInstructions.setPosition(0, 0);
	spriteInstructions.setScale(0.52, 0.87);

	//Set font
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//main meni text
	mainMenuText.setFont(font);
	mainMenuText.setCharacterSize(80);
	mainMenuText.setFillColor(Color::White);
	mainMenuText.setPosition(150, 50);
	std::stringstream mainMenuStream;
	mainMenuStream <<
		"\n1 - Play Game" <<
		"\n2 - Instructions" <<
		"\n3 - Leaderboard" <<
		"\n4 - Exit";

	mainMenuText.setString(mainMenuStream.str());

	//Leaderboard Text


	// Load the score from a text file/
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		inputFile >> score;
		inputFile.close();
	}


	// Ensure the font is loaded (assuming you have already loaded 'font' elsewhere)
	leaderboardText.setFont(font);
	leaderboardText.setCharacterSize(50);
	leaderboardText.setFillColor(sf::Color::White);
	leaderboardText.setPosition(350, 200);

	
	std::stringstream s;
	s << "Hi Score:" << score;
	leaderboardText.setString(s.str());


	//Leaderboard heading text============================================
	
	leaderboardHeadingText.setFont(font); // Use your loaded font
	leaderboardHeadingText.setCharacterSize(80);
	leaderboardHeadingText.setFillColor(Color::Yellow);
	leaderboardHeadingText.setString("Top 10 Scores");

	// Get the local bounds of the text to center it
	FloatRect textRectHeading = leaderboardHeadingText.getLocalBounds();
	leaderboardHeadingText.setOrigin(textRectHeading.left + textRectHeading.width / 2.0f,
	textRectHeading.top + textRectHeading.height / 2.0f);

	// Position the text: centered horizontally and 90% down from the top of the screen.
	leaderboardHeadingText.setPosition(resolution.x / 4.f, resolution.y * 0.1f);

	//======================================================================================
	
	//Leaderboard Return Text
	leaderboardReturnText.setFont(font); // Use your loaded font
	leaderboardReturnText.setCharacterSize(40);
	leaderboardReturnText.setFillColor(Color::Yellow);
	leaderboardReturnText.setString("Press Escape to return to main menu");

	// Get the local bounds of the text to center it
	FloatRect textRectangle = leaderboardReturnText.getLocalBounds();
	leaderboardReturnText.setOrigin(textRectangle.left + textRectangle.width / 2.0f,
		textRectangle.top + textRectangle.height / 2.0f);

	// Position the text: centered horizontally and 90% down from the top of the screen.
	leaderboardReturnText.setPosition(resolution.x / 4.f, resolution.y * 0.9f);

	//======================================================================================
	// 
	//Return Menu Text
	returnMenuText.setFont(font); // Use your loaded font
	returnMenuText.setCharacterSize(40);
	returnMenuText.setFillColor(Color::Yellow);
	returnMenuText.setString("Press ENTER to return to main menu");

	// Get the local bounds of the text to center it
	FloatRect textRect = returnMenuText.getLocalBounds();
	returnMenuText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	// Position the text: centered horizontally and 90% down from the top of the screen.
	returnMenuText.setPosition(resolution.x / 4.f, resolution.y * 0.9f);

	//======================================================================================
	
	//character selection screen
	charSelectText.setFont(font);
	charSelectText.setCharacterSize(70);
	charSelectText.setFillColor(Color::White);
	charSelectText.setPosition(150, 50);
	std::stringstream charSelectStream;
	charSelectStream <<
		"\nZ - Zach" <<
		"\nS - Szymon" <<
		"\nM - Matthew" <<
		"\nC - Corey";

	charSelectText.setString(charSelectStream.str());

	// pause menu options
	pauseMenuText.setFont(font);
	pauseMenuText.setCharacterSize(80);
	pauseMenuText.setFillColor(Color::White);
	pauseMenuText.setPosition(150, 250);
	std::stringstream pauseMenuStream;
	pauseMenuStream <<
		"Game Paused "<<
		"\nR - Resume" <<
		"\nM - Exit to Menu";

	pauseMenuText.setString(pauseMenuStream.str());
}

//Run the engine
void Engine::run()
{
	// Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		// Update the total game time
		m_GameTimeTotal += dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		if (state == State::PLAYING)
		{
			// Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();

			// Convert mouse position to world coordinates of mainView
			mouseWorldPosition = m_Window.mapPixelToCoords(
				Mouse::getPosition(), m_MainView);

			// Set the crosshair to the mouse world location
			spriteCrosshair.setPosition(mouseWorldPosition);
		}

		input();
		update(dtAsSeconds);
		draw();
	}
}
