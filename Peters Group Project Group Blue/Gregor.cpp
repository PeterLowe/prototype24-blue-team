// Authors: Leo Bolaks, Elisabeth Sykorova

#include "Gregor.h"
#include <iostream>

Gregor::Gregor()
{
	loadGregor();
	loadHearts();
	loadSound();
}

void Gregor::loadGregor()
{
	if (!m_gregorTexture.loadFromFile("ASSETS/IMAGES/gregor.png"))
	{
		std::cout << "Error loading gregor" << std::endl;
	}
	m_gregorSprite.setTexture(m_gregorTexture);
	m_gregorSprite.setOrigin(m_gregorDimensions.x/2, m_gregorDimensions.y/2);
	m_gregorSprite.setScale(0.17, 0.17);
	m_gregorSprite.setPosition(GREGOR_SCREEN_WIDTH/2, GREGOR_SCREEN_HEIGHT/2);
	m_gregorSprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(m_gregorDimensions.x), static_cast<int>(m_gregorDimensions.y)));

	m_gregorHitbox.setSize(sf::Vector2f(70, 70));
	m_gregorHitbox.setOrigin(35, 35);
	m_gregorHitbox.setFillColor(sf::Color::Transparent);
	m_gregorHitbox.setOutlineColor(sf::Color::Green);
	m_gregorHitbox.setOutlineThickness(3);
	m_gregorHitbox.setPosition(m_gregorSprite.getPosition());

}

void Gregor::loadSound()
{
	if (!m_stepsBuffer.loadFromFile("ASSETS/AUDIO/gregor_walk.wav"))
	{
		std::cout << "Error loading gregor walk sound effect" << std::endl;
	}

	m_stepsSound.setBuffer(m_stepsBuffer);
	m_stepsSound.setLoop(true);
	m_stepsSound.setVolume(100);
}

void Gregor::playSound()
{
	if (m_stepsSound.getStatus() != sf::Sound::Playing)
	{
		m_stepsSound.play();
	}
}

void Gregor::soundIsOn(bool t_soundOn)
{
	m_soundOn = t_soundOn;

}

sf::Sprite Gregor::getGregor()
{
	return m_gregorSprite;
}

sf::RectangleShape Gregor::getGregorHitbox()
{
	return m_gregorHitbox;
}

void Gregor::update()
{
	if (m_gregorAlive)
	{
		move();
		animate();
		randomMove();
		lifeCheck();

		if (m_soundOn)
		{
			playSound();
		}
		else
		{
			m_stepsSound.stop();
		}
	}
	else
	{
		m_stepsSound.stop();
	}
}

bool Gregor::checkGregorAlive()
{
	return m_gregorAlive;
}

void Gregor::takeAwayLife()
{
	if (m_lives >= 1)
	{
		m_lives--;
	}
	else
	{
		m_lives = 0;
	}
}

void Gregor::takeAway2Lives()
{
	if (m_lives >= 2) // boundaries so that lives dont go past 0
	{
		m_lives -= 2;
	}
	else
	{
		m_lives = 0;
	}
}

void Gregor::lifeCheck()
{
	if (m_lives <= 0)
	{
		m_gregorAlive = false;
	}
}

void Gregor::move()
{
	m_location = m_gregorSprite.getPosition();

	if (m_direction == NORTH)
	{
		m_gregorSprite.setRotation(0);
		if (m_location.y > 150)
		{
			m_location.y -= m_speed;
		}
	}
	if (m_direction == NW)
	{
		m_gregorSprite.setRotation(-45);
		if (m_location.y > 150)
		{
			m_location.y -= m_speed;
		}
		if (m_location.x > 150)
		{
			m_location.x -= m_speed;
		}
		
	}
	if (m_direction == NE)
	{
		m_gregorSprite.setRotation(45);
		if (m_location.y > 150)
		{
			m_location.y -= m_speed;
		}
		if (m_location.x < GREGOR_SCREEN_WIDTH - 150)
		{
			m_location.x += m_speed;
		}
		
	}
	if (m_direction == SOUTH)
	{
		m_gregorSprite.setRotation(180);
		if (m_location.y < GREGOR_SCREEN_HEIGHT - 150)
		{
			m_location.y += m_speed;
		}
	}
	if (m_direction == SW)
	{
		m_gregorSprite.setRotation(-135);
		if (m_location.y < GREGOR_SCREEN_HEIGHT - 150)
		{
			m_location.y += m_speed;
		}
		if (m_location.x > 150)
		{
			m_location.x -= m_speed;
		}
		
	}
	if (m_direction == SE)
	{
		m_gregorSprite.setRotation(135);
		if (m_location.y < GREGOR_SCREEN_HEIGHT - 150)
		{
			m_location.y += m_speed;
		}
		if (m_location.x < GREGOR_SCREEN_WIDTH - 150)
		{
			m_location.x += m_speed;
		}
		
	}
	if (m_direction == EAST)
	{
		m_gregorSprite.setRotation(90);
		if (m_location.x < GREGOR_SCREEN_WIDTH - 150)
		{
			m_location.x += m_speed;
		}
	}
	if (m_direction == WEST)
	{
		m_gregorSprite.setRotation(-90);
		if (m_location.x > 150)
		{
			m_location.x -= m_speed;
		}
	}
	m_gregorSprite.setPosition(m_location);
	m_gregorHitbox.setPosition(m_gregorSprite.getPosition());
}

void Gregor::randomMove()
{
	if (m_countdown != COUNTDOWN_DURATION) // constant is set to 30 to have a 0.5 second timer
	{
		m_countdown++;
	}
	else
	{

		m_direction = (rand() % 8) + 1; // generates a random number between 1 and 12
		m_countdown = 0; // sets countdown to 0
	}

}

void Gregor::animate()
{
	m_lastFrame = m_currentFrame;
	m_frameCounter += m_frameIncrement;
	m_currentFrame = static_cast<int>(m_frameCounter) % NO_FRAMES;

	if (m_lastFrame != m_currentFrame) // animate the button
	{
		m_gregorSprite.setTextureRect(sf::IntRect(m_currentFrame * m_gregorDimensions.x, 0, m_gregorDimensions.x, m_gregorDimensions.y));
	}
}

void Gregor::gregorReset()
{
	m_lives = 3;
	m_gregorSprite.setPosition(600, 450);
	m_gregorAlive = true;
}

void Gregor::loadHearts()
{
	if (!m_heartsTexture.loadFromFile("ASSETS/IMAGES/hearts_spritesheet.png"))
	{
		std::cout << "Error loading hearts" << std::endl;
	}

	m_heartsSprite.setTexture(m_heartsTexture);
	m_heartsSprite.setScale(m_scaleHearts, m_scaleHearts);
	m_heartsSprite.setPosition(15, GREGOR_SCREEN_HEIGHT - 60); // corner of the screen
	m_heartsSprite.setTextureRect(sf::IntRect(0, 0, 760, 275));


}

sf::Sprite Gregor::getHearts()
{
	return m_heartsSprite;
}

void Gregor::animateHearts()
{
	switch (m_lives)
	{
	case 3:
	{
		m_hFrameIncrement = 0.2f; // changes speed of animation based on health state

		m_hLastFrame = m_hCurrentFrame;
		m_hFrameCounter += m_hFrameIncrement;
		m_hCurrentFrame = static_cast<int>(m_hFrameCounter) % NO_HEART_FRAMES;

		if (m_hLastFrame != m_hCurrentFrame)
		{
			m_heartsSprite.setTextureRect(sf::IntRect(m_hCurrentFrame * m_heartDimensions.x, 0, m_heartDimensions.x, m_heartDimensions.y));
		}
		break;
	}
	case 2:
	{
		m_hFrameIncrement = 0.4f;

		m_hLastFrame = m_hCurrentFrame;
		m_hFrameCounter += m_hFrameIncrement;
		m_hCurrentFrame = static_cast<int>(m_hFrameCounter) % NO_HEART_FRAMES;

		if (m_hLastFrame != m_hCurrentFrame)
		{
			m_heartsSprite.setTextureRect(sf::IntRect(m_hCurrentFrame * m_heartDimensions.x, 275, m_heartDimensions.x, m_heartDimensions.y));
		}

		break;
	}
	case 1:
	{
		m_hFrameIncrement = 0.6f;

		m_hLastFrame = m_hCurrentFrame;
		m_hFrameCounter += m_hFrameIncrement;
		m_hCurrentFrame = static_cast<int>(m_hFrameCounter) % NO_HEART_FRAMES;

		if (m_hLastFrame != m_hCurrentFrame)
		{
			m_heartsSprite.setTextureRect(sf::IntRect(m_hCurrentFrame * m_heartDimensions.x, 550, m_heartDimensions.x, m_heartDimensions.y));
		}

		break;
	}
	case 0:
	{
		m_hFrameIncrement = 0.4;

		m_hLastFrame = m_hCurrentFrame;
		m_hFrameCounter += m_hFrameIncrement;
		m_hCurrentFrame = static_cast<int>(m_hFrameCounter) % NO_HEART_FRAMES;

		if (m_hLastFrame != m_hCurrentFrame)
		{
			m_heartsSprite.setTextureRect(sf::IntRect(m_hCurrentFrame * m_heartDimensions.x, 825, m_heartDimensions.x, m_heartDimensions.y));
		}

		break;
	}
	}

	

	// BUG NOTE: SOME STATES TEXTURE RECTS DO NOT WORK PROPERLY - IT SHOULD ALWAYS ONLY SHOW ONE ROW
}
