// Authors: Leo Bolaks, Elisabeth Sykorova

#include "BigApple.h"
#include <iostream>
#include <cmath>

BigApple::BigApple()
{
	loadBigApple();
}

void BigApple::loadBigApple()
{
	if (!m_texture.loadFromFile("ASSETS/IMAGES/bigAppleAnimated.png"))
	{
		std::cout << "problem loading small apple texture" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(sf::Vector2f(m_texture.getSize().x * m_scale / 2,
		m_texture.getSize().y * m_scale / 2)); // origin in the centre of apple
	m_sprite.setPosition(m_position);
	m_sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(m_dimensions.x), static_cast<int>(m_dimensions.y)));
	m_sprite.setScale(m_scale, m_scale);
}
/// <summary>
/// returns sprite
/// </summary>
/// <returns></returns>
sf::Sprite BigApple::getSprite()
{
	return m_sprite;
}
/// <summary>
/// update for the big apples function
/// </summary>
/// <param name="t_gregorPosition"></param>
void BigApple::update(sf::Vector2f t_gregorPosition)
{
	move();
	animate();
	if (!m_bigAppleAlive)
	{
		respawn(t_gregorPosition);
	}
}
void BigApple::animate()
{
	m_lastFrame = m_currentFrame;
	m_frameCounter += m_frameIncrement;
	m_currentFrame = static_cast<int>(m_frameCounter) % NO_FRAMES;

	if (m_lastFrame != m_currentFrame) // animate the button
	{
		m_sprite.setTextureRect(sf::IntRect(m_currentFrame * m_dimensions.x, 0, m_dimensions.x, m_dimensions.y));
	}
}

/// <summary>
/// random spawn for big apples, where first it generates the side it spawns on and then it generates a random number 
/// to spawn it along the line on the x or y axis
/// </summary>
void BigApple::spawn()
{
	int side = rand() % 4;
	float xRespawn = 0.0f;
	float yRespawn = 0.0f;

	switch (side)
	{
	case NORTH_BIG_APPLE: // above screen
	{
		yRespawn = 0 - m_texture.getSize().y * m_scale / 2 - 10; // height of apple
		xRespawn = static_cast<float>(rand() % static_cast<int>(SCREEN_WIDTH_BIG_APPLE)); // random position on x axis
		break;
	}
	case SOUTH_BIG_APPLE:
	{
		yRespawn = SCREEN_HEIGHT_BIG_APPLE + m_texture.getSize().y * m_scale / 2 + 10;
		xRespawn = static_cast<float>(rand() % static_cast<int>(SCREEN_WIDTH_BIG_APPLE));
		break;
	}
	case EAST_BIG_APPLE:
	{
		xRespawn = SCREEN_WIDTH_BIG_APPLE + m_texture.getSize().x * m_scale / 2 + 10;
		yRespawn = static_cast<float>(rand() % static_cast<int>(SCREEN_HEIGHT_BIG_APPLE));
		break;
	}
	case WEST_BIG_APPLE:
	{
		xRespawn = 0 - m_texture.getSize().x * m_scale / 2 - 10;
		yRespawn = static_cast<float>(rand() % static_cast<int>(SCREEN_HEIGHT_BIG_APPLE));
		break;
	}
	}

	m_position = sf::Vector2f(xRespawn, yRespawn);
	m_sprite.setPosition(m_position);
}
/// <summary>
/// Draws a line once from the apple to gregor, only called once when the apple is respawned
/// </summary>
/// <param name="t_gregorPosition"></param>
void BigApple::setLine(sf::Vector2f t_gregorPosition)
{
	m_velocity = m_sprite.getPosition() - t_gregorPosition;

	m_lineLength = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y); // pythagoras to get magnitude

	m_velocity /= m_lineLength;

	m_velocity *= m_speed;
}
/// <summary>
/// moves apple and reverses its tragectory if it is reflected, constantly called in update
/// </summary>
void BigApple::move()
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

	if (m_position.x > SCREEN_WIDTH_BIG_APPLE + 150 || m_position.x < -150 || m_position.y > SCREEN_HEIGHT_BIG_APPLE + 150 || m_position.y < -150)
	{
		m_bigAppleAlive = false;
	}
}
/// <summary>
/// if the apple reaches edge of screen it will die and then respawn
/// </summary>
/// <param name="t_gregorPosition"></param>
void BigApple::respawn(sf::Vector2f t_gregorPosition)
{
	spawn();
	setLine(t_gregorPosition);
	m_bigAppleAlive = true;
	m_reflected = false;
	m_countedReflection = false;
	m_counter = 0;
}
/// <summary>
/// sets alive to false
/// </summary>
void BigApple::setAliveFalse()
{
	m_bigAppleAlive = false;
}
/// <summary>
/// acts as a double click and will only set reflected to true if user clicks 2 times in total
/// </summary>
void BigApple::deflectCounter()
{
	m_counter++;
	if (m_counter == 2)
	{
		m_reflected = true;
	}
}

bool BigApple::checkDeflected()
{
	return m_reflected;
}

void BigApple::countReflection()
{
	m_countedReflection = true;
}

bool BigApple::getCountedReflection()
{
	return m_countedReflection;
}
