#pragma once
#include "SFML/Graphics.hpp"
#include "MenueButton.h"


class Menue
{
public:
	Menue();
	~Menue();

	bool Initialize();
	void Update();
	void Render(sf::RenderWindow &window) const;

	bool IsActive() const { return m_isActive; }

private:

	const std::string FontFileName = "arial.ttf";
	
	bool m_isActive;
	sf::Font m_font;

	MenueButton* m_playButton;
	MenueButton* m_playerStartButton;
	MenueButton* m_aiStartButton;
	MenueButton* m_algo1Button;
	MenueButton* m_algo2Button;
	MenueButton* m_algo3Button;

};

