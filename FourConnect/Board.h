#pragma once
#include "SFML/Graphics.hpp"

class Board
{
public:
	Board(int columns, int rows, float width, float height);
	~Board();

	bool Initialize();
	sf::Drawable* GetDrawableBoard() const { return m_board; }

private:	
	int m_columns;
	int m_rows;
	float m_width;
	float m_height;

	sf::Color m_boardColor;

	sf::RectangleShape* m_board;
	std::vector<sf::CircleShape*> m_tokens;

};

