// Authors: Leo Bolaks, Elisabeth Sykorova

#include "SmallApple.h"
#include <iostream>
#include <iostream>
#include <cmath>
#include "ctime"
#include "cstdlib"


SmallApple::SmallApple()
{
	loadSmallApple();
	//srand((int)time(nullptr));
}

void SmallApple::loadSmallApple()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/smallAppleAnimated.png"))
	{
		std::cout << "problem loading small apple texture" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(sf::Vector2f(m_texture.getSize().x * m_scale / 2,
									m_texture.getSize().y * m_scale / 2)); // origin in the centre of apple
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_dimensions.x, m_dimensions.y));
	m_sprite.setScale(m_scale, m_scale);
}

sf::Sprite SmallApple::getSprite()
{
	return m_sprite;
}

void SmallApple::spawn()
{
		int side = rand() % 4;
		float xRespawn = 0.0f;
		float yRespawn = 0.0f;

		switch (side)
		{
		case NORTH_SMALL_APPLE: // above screen
		{
			yRespawn = 0 - m_texture.getSize().y * m_scale / 2; // height of apple
			xRespawn = static_cast<float>(rand() % static_cast<int>(SCREEN_WIDTH_SMALL_APPLE)); // random position on x axis
			break;
		}
		case SOUTH_SMALL_APPLE:
		{
			yRespawn = SCREEN_HEIGHT_SMALL_APPLE + m_texture.getSize().y * m_scale / 2;
			xRespawn = static_cast<float>(rand() % static_cast<int>(SCREEN_WIDTH_SMALL_APPLE));
			break;
		}
		case EAST_SMALL_APPLE:
		{
			xRespawn = SCREEN_WIDTH_SMALL_APPLE + m_texture.getSize().x * m_scale / 2;
			yRespawn = static_cast<float>(rand() % static_cast<int>(SCREEN_HEIGHT_SMALL_APPLE));
			break;
		}
		case WEST_SMALL_APPLE:
		{
			xRespawn = 0 - m_texture.getSize().x  * m_scale / 2;
			yRespawn = static_cast<float>(rand() % static_cast<int>(SCREEN_HEIGHT_SMALL_APPLE));
			break;
		}
		}

		m_position = sf::Vector2f(xRespawn, yRespawn);
		m_sprite.setPosition(m_position);

}

void SmallApple::setLine(sf::Vector2f t_gregorPosition)
{

	m_velocity = m_sprite.getPosition() - t_gregorPosition;

	m_lineLength = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y); // pythagoras to get magnitude

	m_velocity /= m_lineLength;

	m_velocity *= m_speed;
}

void SmallApple::move()
{
	if (!m_reflected)
	{
		m_position -= m_velocity;
	}
	else if (m_reflected)
	{
		m_position.x += m_velocity.x * 3;
		m_position.y += m_velocity.y * 3;
	}

	m_sprite.setPosition(m_position);

	if (m_position.x > SCREEN_WIDTH_SMALL_APPLE + 100 || m_position.x < -100 || m_position.y > SCREEN_HEIGHT_SMALL_APPLE + 100 || m_position.y < -100)
	{
		m_smallAppleAlive = false;
	}
}

void SmallApple::animate()
{
	m_lastFrame = m_currentFrame;
	m_frameCounter += m_frameIncrement;
	m_currentFrame = static_cast<int>(m_frameCounter) % NO_FRAMES;

	if (m_lastFrame != m_currentFrame) // animate the button
	{
		m_sprite.setTextureRect(sf::IntRect(m_currentFrame * m_dimensions.x, 0, m_dimensions.x, m_dimensions.y));
	}
}

void SmallApple::setAliveFalse()
{
	m_smallAppleAlive = false;
}

bool SmallApple::checkDeflected()
{
	return m_reflected;
}

void SmallApple::update(sf::Vector2f t_gregorPosition)
{
	move();
	animate();
	if (!m_smallAppleAlive)
	{
		respawn(t_gregorPosition);
	}
}

void SmallApple::respawn(sf::Vector2f t_gregorPosition)
{
	spawn();
	setLine(t_gregorPosition);
	m_smallAppleAlive = true;
	m_reflected = false;
}

void SmallApple::setReflectTrue()
{
	m_reflected = true;
}



