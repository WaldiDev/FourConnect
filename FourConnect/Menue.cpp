#include "Menue.h"
#include <windows.h>
#include <iostream>


Menue::Menue() :
	m_isActive(true)
{
}


Menue::~Menue()
{
}

bool Menue::Initialize()
{
	OutputDebugString(L"Initialize Menue\n");

	// Load font
	if (!m_font.loadFromFile(FontFileName))
	{
		std::cout << "File \"" << FontFileName << "\" couldn't be loaded" << std::endl;
	}

	sf::Vector2f largeSize(300.f, 50.f);
	sf::Vector2f smallSize(150.f, 50.f);
		
	m_algo1Button = new MenueButton(largeSize, sf::Vector2f(250.f, 200.f), &m_font, sf::Color::White, "Negamax unlimited");
	m_algo2Button = new MenueButton(largeSize, sf::Vector2f(250.f, 300.f), &m_font, sf::Color::White, "Negamax with horizon");
	m_algo3Button = new MenueButton(largeSize, sf::Vector2f(250.f, 400.f), &m_font, sf::Color::White, "Alpha-Beta pruning");
	m_aiStartButton = new MenueButton(smallSize, sf::Vector2f(625.f, 200.f), &m_font, sf::Color::White, "AI");;
	m_playerStartButton = new MenueButton(smallSize, sf::Vector2f(625.f, 300.f), &m_font, sf::Color::White, "Player");
	m_playButton = new MenueButton(smallSize, sf::Vector2f(625.f, 400.f), &m_font, sf::Color::White, "Start Game");
	
	return true;
}

void Menue::Render(sf::RenderWindow& window) const
{
	m_algo1Button->Render(window);
	m_algo2Button->Render(window);
	m_algo3Button->Render(window);
	m_aiStartButton->Render(window);
	m_playerStartButton->Render(window);
	m_playButton->Render(window);
}
