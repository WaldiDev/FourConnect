#pragma once
#include "SFML/Graphics.hpp"

enum TileState
{
	Empty = 0,
	Player1 = 1,
	Player2 = -1
};

class Board
{
public:
	Board(int columns, int rows, float width, float height, sf::RenderWindow &window);
	~Board();

	bool Initialize();
	void Update();
	void Render(sf::RenderWindow &window);

	void OnMouseMoved(sf::Vector2f mouseCoord);
	void OnMouseButtonPressed(sf::Vector2f mouseCoord, int button);
	void ChangePlayer();

	void ComputeNextTurn(int stage);
	void RenderBoard(std::vector<std::vector<int>> board);
	int MinMax(std::vector<std::vector<int>> board, int player);

	sf::CircleShape Circle(sf::Color color, sf::Vector2f pos);
private:	
	sf::RenderWindow& m_window;
	int m_columns;
	int m_rows;
	float m_width;
	float m_height;

	float m_tokenRadius;

	sf::Color m_boardColor;

	//sf::RectangleShape* m_board;
	std::vector<sf::RectangleShape> m_boardPieces;
	std::vector<std::vector< sf::CircleShape>> m_tokens;
	std::vector<std::vector< int>> m_board;

};

