#pragma once
#include "SFML/Graphics.hpp"

class Board
{
public:
	Board(int columns, int rows, float width, float height);
	~Board();

	bool Initialize();
	void Update();
	void Render(sf::RenderWindow &window);

	void OnMouseMoved(sf::Vector2f mouseCoord);
	void OnMouseButtonPressed(sf::Vector2f mouseCoord, int button);

private:	
	int m_columns;
	int m_rows;
	float m_width;
	float m_height;

	float m_tokenRadius;

	sf::Color m_boardColor;

	sf::RectangleShape* m_board;
	std::vector<sf::RectangleShape> m_boardPieces;
	std::vector<std::vector< sf::CircleShape>> m_tokens;

	void CreateTokenElement(sf::Vector2f position);

};

