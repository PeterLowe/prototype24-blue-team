#include "Instructions.h"
#include <iostream>

Instructions::Instructions()
{
	loadInstructions();
}

void Instructions::loadInstructions()
{
	if (!m_controlsFont.loadFromFile("ASSETS\\FONTS\\GregorFont.ttf"))
	{
		std::cout << "Error loading controls font" << std::endl;
	}
	m_controlsText.setFont(m_controlsFont);
	m_controlsText.setOutlineColor(sf::Color::Black);
	m_controlsText.setOutlineThickness(2);
	m_controlsText.setCharacterSize(45);
	m_controlsText.setPosition(150, 630);
	m_controlsText.setString(" Click once on small apples to deflect them \n\n Double click on big apples to deflect them \n small apples deal 1 heart of damage while big apples deal 2");

	if (!m_storyFont.loadFromFile("ASSETS\\FONTS\\GregorFont.ttf"))
	{
		std::cout << "Error loading controls font" << std::endl;
	}
	m_storyText.setFont(m_storyFont);
	m_storyText.setOutlineColor(sf::Color::Black);
	m_storyText.setOutlineThickness(2);
	m_storyText.setCharacterSize(43);
	m_storyText.setPosition(10, 25);
	m_storyText.setString(" As Gregor Samsa awoke one day from uneasy dreams he found himself transformed \n in his bed into a gigantic insect. His family, initially shocked by his metamorphosis, \n gradually became accustomed to his new form, yet their acceptance was short - lived.\n \"Mother has been fainting.She's better now. Gregor's broken loose.\" \n \"Just what I expected,\"  said his father. Truly, this was not the father Gregor had \n imagined to himself; admittedly he had been too absorbed of late in his new \n recreation of crawling over the ceiling - suddenly something lightly flung \n landed close behind him and rolled before him. It was an apple; \n a second apple followed immediately.\n Your goal now is to save Gregor from the apples thrown at him. ");

	if (!m_smallAppleExample.loadFromFile("ASSETS\\IMAGES\\smallApple.png"))
	{
		std::cout << "Error loading small example apple" << std::endl;
	}
	m_smallAppleExampleSprite.setTexture(m_smallAppleExample);
	m_smallAppleExampleSprite.setScale(0.1, 0.1);
	m_smallAppleExampleSprite.setPosition(40, 620);

	if (!m_bigAppleExample.loadFromFile("ASSETS\\IMAGES\\bigApple.png"))
	{
		std::cout << "Error loading small example apple" << std::endl;
	}
	m_bigAppleExampleSprite.setTexture(m_bigAppleExample);
	m_bigAppleExampleSprite.setScale(0.1, 0.1);
	m_bigAppleExampleSprite.setPosition(40, 750);

	if (!m_homeButtonTexture.loadFromFile("ASSETS\\IMAGES\\home.png"))
	{
		std::cout << "Error loading home button image" << std::endl;
	}
	m_homeButtonSprite.setTexture(m_homeButtonTexture);
	m_homeButtonSprite.setPosition(1090, 790);
}

sf::Text Instructions::getControlsText()
{
	return m_controlsText;
}

sf::Text Instructions::getStoryText()
{
	return m_storyText;
}

sf::Sprite Instructions::getSmallAppleExample()
{
	return m_smallAppleExampleSprite;
}

sf::Sprite Instructions::getBigAppleExample()
{
	return m_bigAppleExampleSprite;
}

sf::Sprite Instructions::getHomeButton()
{
	return m_homeButtonSprite;
}
