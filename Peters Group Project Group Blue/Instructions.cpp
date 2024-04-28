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
	m_controlsText.setCharacterSize(55);
	m_controlsText.setPosition(500, 350);
	m_controlsText.setString("Click once on small apples to deflect them \n \n Double click on big apples to deflect them \n \n small apples deal 1 heart of damage while big apples deal 2");
}

sf::Text Instructions::getControlsText()
{
	return m_controlsText;
}
