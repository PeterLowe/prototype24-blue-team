// Authors: Leo Bolaks, Elisabeth Sykorova

#include "Instructions.h"
#include <iostream>

Instructions::Instructions()
{
	loadInstructions();
}

void Instructions::loadInstructions()
{
	if (!m_controlsFont.loadFromFile("ASSETS/FONTS/GregorFont.ttf"))
	{
		std::cout << "Error loading controls font" << std::endl;
	}
	m_controlsText.setFont(m_controlsFont);
	m_controlsText.setCharacterSize(30);
	m_controlsText.setPosition(120, 630);
	m_controlsText.setString(" Click once on small apples to deflect them \n\n Double click on big apples to deflect them \n\n Small apples deal 1 heart of damage; Big apples deal 2 hearts of damage. ");

	if (!m_storyFont.loadFromFile("ASSETS/FONTS/GregorFont.ttf"))
	{
		std::cout << "Error loading controls font" << std::endl;
	}
	m_storyText.setFont(m_storyFont);
	m_storyText.setCharacterSize(28);
	m_storyText.setPosition(35, 25);
	m_storyText.setString("As Gregor Samsa awoke one day from uneasy dreams he found himself transformed in his bed into a gigantic insect.\n\nHis family, initially shocked by his metamorphosis, gradually became accustomed to his new form, yet their acceptance was short-lived.\n\n\"Mother has been fainting. She's better now. Gregor's broken loose.\" \n\"Just what I expected,\"  said his father.\n\nTruly, this was not the father Gregor had imagined to himself;\nadmittedly he had been too absorbed of late in his new recreation of crawling over the ceiling\n- suddenly something lightly flung landed close behind him and rolled before him. \n\nIt was an apple; a second apple followed immediately.\n\nY o u r   g o a l   n o w   i s   t o   s a v e   G r e g o r   f r o m   t h e   a p p l e s   t h r o w n   a t   h i m . ");

	if (!m_smallAppleExample.loadFromFile("ASSETS/IMAGES/smallApple.png"))
	{
		std::cout << "Error loading small example apple" << std::endl;
	}
	m_smallAppleExampleSprite.setTexture(m_smallAppleExample);
	m_smallAppleExampleSprite.setScale(0.08, 0.08);
	m_smallAppleExampleSprite.setPosition(40, 600);

	if (!m_bigAppleExample.loadFromFile("ASSETS/IMAGES/bigApple.png"))
	{
		std::cout << "Error loading small example apple" << std::endl;
	}
	m_bigAppleExampleSprite.setTexture(m_bigAppleExample);
	m_bigAppleExampleSprite.setScale(0.09, 0.09);
	m_bigAppleExampleSprite.setPosition(35, 680);

	if (!m_homeButtonTexture.loadFromFile("ASSETS/IMAGES/home.png"))
	{
		std::cout << "Error loading home button image" << std::endl;
	}
	m_homeButtonSprite.setTexture(m_homeButtonTexture);
	m_homeButtonSprite.setScale(0.7, 0.7);
	m_homeButtonSprite.setPosition(1200 - 100, 900 - 100);

	if (!m_heartExample.loadFromFile("ASSETS/IMAGES/hearts_spritesheet.png"))
	{
		std::cout << "Error loading hearts example image" << std::endl;
	}
	m_heartExampleSprite.setTexture(m_heartExample);
	m_heartExampleSprite.setTextureRect(sf::IntRect(0, 0, 252, 275));
	m_heartExampleSprite.setScale(0.25, 0.25);
	m_heartExampleSprite.setPosition(45, 785);
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

sf::Sprite Instructions::getHeartExample()
{
	return m_heartExampleSprite;
}
