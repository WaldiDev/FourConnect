#include "MenueButton.h"


MenueButton::MenueButton(sf::Vector2f size, sf::Vector2f position, sf::Font* font, sf::Color btnFillcolor, std::string text)
{
	m_shape.setSize(size);
	m_shape.setPosition(position);
	m_shape.setFillColor(btnFillcolor);
	m_shape.setOutlineThickness(1.f);
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setOrigin(size / 2.f);

	m_text.setFont(*font);
	m_text.setString(text);
	m_text.setCharacterSize(24);
	m_text.setColor(sf::Color::Black);
	CenterText();
}


MenueButton::~MenueButton()
{
}

void MenueButton::Render(sf::RenderWindow& window) const
{
	window.draw(m_shape);
	window.draw(m_text);
}

void MenueButton::CenterText()
{
	auto textRect = m_text.getGlobalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	m_text.setPosition(m_shape.getPosition());
}
