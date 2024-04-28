/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1200U, 900U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupMouseDot();
	loadBackground();
	loadSound();

	for (int index = 0; index < MAX_SMALL_APPLES; index++)
	{
		smallApples[index].spawn();
		smallApples[index].setLine(gregor.getGregor().getPosition());
	}
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	srand((int)time(nullptr)); // set the seed once
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseMoved == newEvent.type) // user pressed a mouse button 
		{
			processMouseMove(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseReleased();
			if (m_gameState == GameStates::Menu)
			{
				soundButtonCollision();
				menuCollisions();
			}
		}
		
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	if (m_gameState == GameStates::Game)
	{
		updateTime();

		if (m_backgroundMusic.getStatus() != sf::Sound::Stopped) // later swap for a different sound
		{
			m_backgroundMusic.stop();
		}

		if (!m_gamePlayed)
		{
			m_gamePlayed = true;
		}
		gregorCheck();
		gregor.update();
		smallAppleCollisions();
		bigAppleCollisions();
		gregor.animateHearts();
		addEnemies();

		for (int index = 0; index < m_activeSmallApple; index++)
		{
			smallApples[index].update(gregor.getGregor().getPosition());
		}
		for (int i = 0; i < m_activeBigApple; i++)
		{
			bigApples[i].update(gregor.getGregor().getPosition());
		}
	}
	if (m_gameState == GameStates::Menu)
	{
		buttonHovering();

		if (m_backgroundMusic.getStatus() != sf::Sound::Playing && menu.getSoundOn())
		{
			m_backgroundMusic.play();
		}
		else if (m_backgroundMusic.getStatus() != sf::Sound::Paused && !menu.getSoundOn())
		{
			m_backgroundMusic.pause();
		}

		menu.animateSprites();

		if (!m_gamePlayed)
		{
			menu.setStartButtonState(0);
		}
		else
		{
			menu.setStartButtonState(1);
			m_endGameMessage.setString("You kept Gregor alive for " + std::to_string(m_minutes) + " minutes and " + std::to_string(m_seconds) + " seconds and saved him from " + std::to_string(m_deflections) + " apples.");
			m_endGameMessage.setOrigin(m_endGameMessage.getGlobalBounds().width / 2, m_endGameMessage.getGlobalBounds().height / 2);
			m_endGameMessage.setPosition(SCREEN_WIDTH_BIG_APPLE / 2, SCREEN_HEIGHT_BIG_APPLE / 2 + 100);
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	if (m_gameState == GameStates::Menu)
	{
		m_window.draw(m_backgroundSprite);
		m_window.draw(m_instructionsPlaceHolder);
		m_window.draw(menu.getStartGameSprite());
		m_window.draw(menu.getSoundButton());

		if (m_gamePlayed)
		{
			m_window.draw(m_endGameMessage);
		}
	}
	if (m_gameState == GameStates::Game)
	{
		m_window.draw(m_backgroundSprite); // first
		m_window.draw(gregor.getGregor());
		//m_window.draw(gregor.getGregorHitbox());
		for (int index = 0; index < m_activeSmallApple; index++)
		{
			m_window.draw(smallApples[index].getSprite());
		}
		for (int i = 0; i < m_activeBigApple; i++)
		{
			m_window.draw(bigApples[i].getSprite());
		}
		m_window.draw(m_mouseDot);
		m_window.draw(gregor.getGregor());
		m_window.draw(gregor.getHearts());
		m_window.draw(m_timeElapsed);
	}
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_gregorFont.loadFromFile("ASSETS\\FONTS\\GregorFont.ttf"))
	{
		std::cout << "problem loading gregor font" << std::endl;
	}

	m_timeElapsed.setFont(m_gregorFont);
	m_timeElapsed.setString("Time "); // initializing only
	m_timeElapsed.setCharacterSize(50);
	m_timeElapsed.setFillColor(sf::Color(229, 227, 222));
	m_timeElapsed.setPosition(0 + 20, 0 + 20);

	m_endGameMessage.setFont(m_gregorFont);
	m_endGameMessage.setString("Time "); // initializing only
	m_endGameMessage.setCharacterSize(32);
	m_endGameMessage.setFillColor(sf::Color(229, 227, 222));
	m_endGameMessage.setOrigin(m_endGameMessage.getGlobalBounds().width / 2, m_endGameMessage.getGlobalBounds().height / 2);
	m_endGameMessage.setPosition(SCREEN_WIDTH_BIG_APPLE/2, SCREEN_HEIGHT_BIG_APPLE/2 + 100);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>

void Game::setupMouseDot()
{
	m_mouseDot.setRadius(1.0);
	m_mouseDot.setOrigin(0.5, 0.5);
	m_mouseDot.setFillColor(sf::Color::Black);
}

void Game::loadBackground()
{
	if (!m_startBg.loadFromFile("ASSETS\\IMAGES\\bg.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading start bg" << std::endl;
	}

	if (!m_gameplayBg.loadFromFile("ASSETS\\IMAGES\\tiles_lighter.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading game bg" << std::endl;
	}

	m_backgroundSprite.setTexture(m_startBg);

	m_instructionsPlaceHolder.setSize(sf::Vector2f{ 50, 50 });
	m_instructionsPlaceHolder.setFillColor(sf::Color::Transparent);
	m_instructionsPlaceHolder.setOutlineColor(sf::Color::Red);
	m_instructionsPlaceHolder.setOutlineThickness(5);
	m_instructionsPlaceHolder.setPosition(550, 550);
}

void Game::processMouseMove(sf::Event t_event)
{
	m_mouseEndVector.x = static_cast<float>(t_event.mouseMove.x);
	m_mouseEndVector.y = static_cast<float>(t_event.mouseMove.y);
	m_mouseDot.setPosition(m_mouseEndVector); // circle shape with the location of mouse to use for intersecting
}

void Game::processMouseReleased()
{
	for (int index = 0; index < MAX_SMALL_APPLES; index++)
	{
		if (m_mouseDot.getGlobalBounds().intersects(smallApples[index].getSprite().getGlobalBounds()))
		{
			if (!smallApples[index].checkDeflected())
			{
				m_deflections++;
			}
			smallApples[index].setReflectTrue();

			if (menu.getSoundOn())
			{
				m_appleClickedSound.play();
			}
			
		}
		
	}
	for (int i = 0; i < MAX_BIG_APPLES; i++)
	{
		if (m_mouseDot.getGlobalBounds().intersects(bigApples[i].getSprite().getGlobalBounds()))
		{
			bigApples[i].deflectCounter();
			
			if (bigApples[i].checkDeflected() && !bigApples[i].getCountedReflection()) // if big apple is deflected but it was not counter yet
			{
				m_deflections++;
				bigApples[i].countReflection(); // count it (once)
			}

			if (menu.getSoundOn())
			{
				m_appleClickedSound.play();
			}
		}
	}
}

void Game::smallAppleCollisions()
{
	for (int i = 0; i < MAX_SMALL_APPLES; i++)
	{
		if (smallApples[i].getSprite().getGlobalBounds().intersects(gregor.getGregorHitbox().getGlobalBounds()))
		{
			smallApples[i].setAliveFalse();
			gregor.takeAwayLife();

			if (menu.getSoundOn())
			{
				m_hitSound.play();
			}
		}
	}
}

void Game::bigAppleCollisions()
{
	for (int i = 0; i < MAX_BIG_APPLES; i++)
	{
		if (bigApples[i].getSprite().getGlobalBounds().intersects(gregor.getGregorHitbox().getGlobalBounds()))
		{
			bigApples[i].setAliveFalse();
			gregor.takeAway2Lives();

			if (menu.getSoundOn())
			{
				m_hitSound.play();
			}
		}
	}
}

void Game::menuCollisions()
{
	if (m_mouseDot.getGlobalBounds().intersects(menu.getStartGameSprite().getGlobalBounds()))
	{
		if (menu.getSoundOn())
		{
			m_buttonClickSound.play();
		}
		gameReset();
		m_gameState = GameStates::Game;
		m_backgroundSprite.setTexture(m_gameplayBg);
	}

}

void Game::buttonHovering()
{
	if (m_mouseDot.getGlobalBounds().intersects(menu.getStartGameSprite().getGlobalBounds()))
	{
		menu.changeToRed();
	}
	else
	{
		menu.changeToWhite();
	}
}

void Game::soundButtonCollision()
{
	if (m_mouseDot.getGlobalBounds().intersects(menu.getSoundButton().getGlobalBounds())) // if mouse intersects sound button
	{
		gregor.soundIsOn(!menu.getSoundOn());
		menu.soundIsOn(!menu.getSoundOn()); // has to be last if negating 
	}
}

void Game::gregorCheck()
{
	if (!gregor.checkGregorAlive())
	{
		m_gameState = GameStates::Menu; 
		m_backgroundSprite.setTexture(m_startBg);
		
	}
}

void Game::addEnemies()
{
	if (m_deflections == 2)
	{
		m_activeSmallApple = 2;
	}
	else if (m_deflections == 8)
	{
		m_activeBigApple = 1;
	}
	else if (m_deflections == 16)
	{
		m_activeSmallApple = 3;
	}
	else if (m_deflections == 25)
	{
		m_activeSmallApple = 4;
	}
	else if (m_deflections == 36)
	{
		m_activeBigApple = 2;
	}
}

void Game::updateTime()
{
	std::string m_timeString;
	std::string null = ""; // placeholder for double digit seconds
	std::string divider = ":"; // divider between minutes and seconds
	m_secondsCounter += 1 / 60.0f; // update every 1/60th of a second
	m_seconds = static_cast<int>(m_secondsCounter);

	if (m_seconds % 60 == 0 && m_seconds != m_secondsLastChecked) // if the seconds are divisible by 60, it means a minute has passed - this has to be updated once only
	{
		m_minutes++;
		m_secondsCounter = 0.0f;
		m_seconds = 0;
		m_secondsLastChecked = m_seconds;
	}

	if (m_seconds < 10) // placeholder zero
	{
		null = "0";
	}

	m_timeString = std::to_string(m_minutes) + divider + null + std::to_string(m_seconds);
	m_timeElapsed.setString(m_timeString);
}

void Game::gameReset()
{
	m_deflections = 0;
	m_activeSmallApple = 1;
	m_activeBigApple = 0;

	for (int i = 0; i < MAX_BIG_APPLES; i++)
	{
		bigApples[i].spawn();
	}
	for (int i = 0; i < MAX_SMALL_APPLES; i++)
	{
		smallApples[i].spawn();
	}

	gregor.gregorReset();

	m_secondsCounter = 0.0f;
	m_seconds = 0;
	m_minutes = 0;
	m_secondsLastChecked = m_seconds;

}

void Game::loadSound()
{
	if (!m_buttonClickBuffer.loadFromFile("ASSETS/AUDIO/page_turn.wav"))
	{
		std::cout << "Error button click sound" << std::endl;
	}
	m_buttonClickSound.setBuffer(m_buttonClickBuffer);
	m_buttonClickSound.setVolume(60);

	if (!m_appleClickedBuffer.loadFromFile("ASSETS/AUDIO/reflect.wav"))
	{
		std::cout << "Error reflect sound" << std::endl;
	}
	m_appleClickedSound.setBuffer(m_appleClickedBuffer);

	if (!m_hitBuffer.loadFromFile("ASSETS/AUDIO/hit.wav"))
	{
		std::cout << "Error hit sound" << std::endl;
	}
	m_hitSound.setBuffer(m_hitBuffer);

	if (!m_menuMusicBuffer.loadFromFile("ASSETS/AUDIO/menu_music.wav"))
	{
		std::cout << "Error menu music " << std::endl;
	}
	m_backgroundMusic.setBuffer(m_menuMusicBuffer);
	m_backgroundMusic.setVolume(60);
	m_backgroundMusic.setLoop(true);

}

