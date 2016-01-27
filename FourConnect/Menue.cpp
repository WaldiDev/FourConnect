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

	m_textGameMode.setFont(m_font);
	m_textGameMode.setString("Game mode: Negamax unlimited");
	m_textGameMode.setPosition(100.f, 450.f);
	m_textGameMode.setColor(sf::Color::Black);

	m_textStarter.setFont(m_font);
	m_textStarter.setString("Starter: AI");
	m_textStarter.setPosition(100.f, 500.f);
	m_textStarter.setColor(sf::Color::Black);

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
	window.draw(m_textGameMode);
	window.draw(m_textStarter);
}

void Menue::CheckClickEvent(sf::Vector2f mouseCoord)
{
	if (m_algo1Button->CheckClick(mouseCoord))
	{
		OutputDebugString(L"Algo1 Button\n");
		m_algo1Button->OnClick();
		m_textGameMode.setString("Game mode: Negamax unlimited");
	}
	else if (m_algo2Button->CheckClick(mouseCoord))
	{
		OutputDebugString(L"Algo2 Button\n");
		m_algo2Button->OnClick();
		m_textGameMode.setString("Game mode: Negamax with horizon");
	}
	else if (m_algo3Button->CheckClick(mouseCoord))
	{
		OutputDebugString(L"Algo3 Button\n");
		m_algo3Button->OnClick();
		m_textGameMode.setString("Game mode: Alpha-Beta pruning");
	}
	else if (m_aiStartButton->CheckClick(mouseCoord))
	{
		OutputDebugString(L"AI Start Button\n");
		m_aiStartButton->OnClick();
		m_textStarter.setString("Starter: AI");
	}
	else if (m_playerStartButton->CheckClick(mouseCoord))
	{
		OutputDebugString(L"Player Start Button\n");
		m_playerStartButton->OnClick();
		m_textStarter.setString("Starter: Player");
	}
	else if (m_playButton->CheckClick(mouseCoord))
	{
		OutputDebugString(L"Play Button\n");
		m_playButton->OnClick();
	}
}

void Menue::CheckReleaseEvent(sf::Vector2f mouseCoord)
{
	if (m_algo1Button->CheckClick(mouseCoord))
	{
		m_algo1Button->OnRelease();
	}
	else if (m_algo2Button->CheckClick(mouseCoord))
	{
		m_algo2Button->OnRelease();
	}
	else if (m_algo3Button->CheckClick(mouseCoord))
	{
		m_algo3Button->OnRelease();
	}
	else if (m_aiStartButton->CheckClick(mouseCoord))
	{
		m_aiStartButton->OnRelease();
	}
	else if (m_playerStartButton->CheckClick(mouseCoord))
	{
		m_playerStartButton->OnRelease();
	}
	else if (m_playButton->CheckClick(mouseCoord))
	{
		m_playButton->OnRelease();
	}
}
