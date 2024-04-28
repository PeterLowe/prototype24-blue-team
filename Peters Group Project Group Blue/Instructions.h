#ifndef Instructions_HPP
#define Instructions_HPP

#include <SFML/Graphics.hpp>

class Instructions
{
	sf::Font m_storyFont; // font for story
	sf::Text m_storyText; // text for story
	sf::Font m_controlsFont; // font for instructions
	sf::Text m_controlsText; // text for instructions

	sf::Texture m_smallAppleExample; // set up for small apple example image
	sf::Sprite m_smallAppleExampleSprite;
	sf::Texture m_bigAppleExample; // set up for big apple example image
	sf::Sprite m_bigAppleExampleSprite;

public:
	Instructions();

	void loadInstructions();

	sf::Text getControlsText();
};
#endif