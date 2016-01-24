#pragma once
#include "SFML/Graphics.hpp"


class MenueButton
{
public:
	MenueButton(sf::Vector2f size, sf::Vector2f position, sf::Font* font, sf::Color btnFillcolor, std::string text);
	~MenueButton();

	void Render(sf::RenderWindow &window) const;

private:
	void CenterText();

	sf::RectangleShape m_shape;
	sf::Text m_text;
};

