/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>
#include "ctime"
#include"cstdlib"



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
			else if (m_gameState == GameStates::End)
			{
				endCollisions();
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

	if (sf::Keyboard::Num1 == t_event.key.code)
	{
		menu.setStartButtonState(1);
	}
	if (sf::Keyboard::Num0 == t_event.key.code)
	{
		menu.setStartButtonState(0);
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
		m_backgroundSprite.setTexture(m_gameplayBg);
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
		m_backgroundSprite.setTexture(m_startBg);
		menu.animateSprites();
		menu.setStartButtonState(0);
	}
	if (m_gameState == GameStates::End)
	{
		menu.animateSprites();
		menu.setStartButtonState(1);
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
		/*m_window.draw(menu.getSaveGregorText());*/
		m_window.draw(menu.getStartGameSprite());
		m_window.draw(menu.getSoundButton());
	}
	if (m_gameState == GameStates::End)
	{
		m_window.draw(menu.getStartGameSprite());
	}
	if (m_gameState == GameStates::Game)
	{
		m_window.draw(m_backgroundSprite);
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
	}
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

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
		m_gameState = GameStates::Game;
	}

}

void Game::endCollisions()
{
	if (m_mouseDot.getGlobalBounds().intersects(menu.getStartGameSprite().getGlobalBounds()))
	{
		if (menu.getSoundOn())
		{
			m_buttonClickSound.play();
		}
		gameReset();
		m_gameState = GameStates::Game;
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
		m_gameState = GameStates::End;
		menu.setRespawnButton();
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

}

