// Authors: Leo Bolaks, Elisabeth Sykorova

#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	loadMenu();
	loadSprites();
	loadSoundButton();
}

void Menu::loadMenu()
{
	if (!m_saveGregorFont.loadFromFile("ASSETS/FONTS/GregorFont.ttf"))
	{
		std::cout << "Error loading gregor font" << std::endl;
	}
	m_saveGregorText.setFont(m_saveGregorFont);
	m_saveGregorText.setCharacterSize(50);
	m_saveGregorText.setFillColor(sf::Color::Black);
	m_saveGregorText.setString("Save Gregor");
	m_saveGregorText.setPosition(500, 450);

}

void Menu::loadSoundButton()
{
	if (!m_soundOnTexture.loadFromFile("ASSETS/IMAGES/music_on.png"))
	{
		std::cout << "Error loading sounds on" << std::endl;
	}
	if (!m_soundOffTexture.loadFromFile("ASSETS/IMAGES/music_off.png"))
	{
		std::cout << "Error loading sounds off" << std::endl;
	}

	m_soundButton.setTexture(m_soundOnTexture);
	m_soundButton.setScale(0.6, 0.6);
	m_soundButton.setPosition(0 + 25, MENU_SCREEN_HEIGHT - m_soundButton.getGlobalBounds().width - 25);
}

sf::Sprite Menu::getSoundButton()
{
	return m_soundButton;
}

void Menu::loadSprites()
{
	if (!m_startGameTexture.loadFromFile("ASSETS/IMAGES/start_game_button.png"))
	{
		std::cout << "Error loading start button textures" << std::endl;
	}

	m_startGameSprite.setTexture(m_startGameTexture);
	m_startGameSprite.setOrigin(m_saveGregorXY.x/2, m_saveGregorXY.y/2);
	m_startGameSprite.setPosition(MENU_SCREEN_WIDTH/2, MENU_SCREEN_HEIGHT/2);
	m_startGameSprite.setScale(0.5, 0.5);

	m_currentStartButton = START_GAME;
	m_newStartButton = START_GAME;
	m_startGameSprite.setTextureRect(sf::IntRect(0, 0, m_startButtonXY.x, m_startButtonXY.y));
}

sf::Sprite Menu::getStartGameSprite()
{
	return m_startGameSprite;
}

void Menu::animateSprites()
{
	if (m_currentStartButton != m_newStartButton) // if the start button state has been changed
	{
		if(m_newStartButton == START_GAME)
		{
			m_startButtonXY = m_saveGregorXY; // start button says save gregor (start state)
			m_startGameSprite.setOrigin(m_saveGregorXY.x / 2, m_saveGregorXY.y / 2);
		}
		else
		{
			m_startButtonXY = m_tryAgainXY; // start button says try again (restart state)
			m_startGameSprite.setOrigin(m_tryAgainXY.x / 2, m_tryAgainXY.y / 2);
		}

		m_currentStartButton = m_newStartButton;
	}
	m_lastFrame = m_currentFrame;
	m_frameCounter += m_frameIncrement;
	m_currentFrame = static_cast<int>(m_frameCounter) % NO_BUTTON_FRAMES;

	if (m_lastFrame != m_currentFrame) // animate the button
	{
		m_startGameSprite.setTextureRect(sf::IntRect(m_currentFrame * m_startButtonXY.x, 0 + m_currentStartButton * m_startButtonXY.y, m_startButtonXY.x, m_startButtonXY.y));
	}

}

void Menu::changeToRed()
{
	m_startGameSprite.setColor(sf::Color(232, 37, 37));
}

void Menu::changeToWhite()
{
	m_startGameSprite.setColor(sf::Color::White);
}

/// <summary>
/// set the state of the start button, 0 = START GAME, 1 = RESTART GAME
/// </summary>
void Menu::setStartButtonState(int t_startButtonState)
{
	m_newStartButton = t_startButtonState;
}

void Menu::setRespawnButton()
{
	m_newStartButton == RESTART_GAME;
}

sf::Text Menu::getSaveGregorText()
{
	return m_saveGregorText;
}

void Menu::soundIsOn(bool t_soundOn)
{
	if (t_soundOn)
	{
		m_soundButton.setTexture(m_soundOnTexture);
		m_textureOn = true;
	}
	else
	{
		m_soundButton.setTexture(m_soundOffTexture);
		m_textureOn = false;
	}
}

bool Menu::getSoundOn()
{
	return m_textureOn;
}
