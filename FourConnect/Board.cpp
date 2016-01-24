#include "Board.h"
#include <windows.h>

Board::Board(int columns, int rows, float width, float height) :
	m_columns(columns),
	m_rows(rows),	
	m_width(width),
	m_height(height),
	m_boardColor(sf::Color::Blue),
	m_board(nullptr)
{
	m_tokens.reserve(m_rows * m_columns);
}

Board::~Board()
{
	delete m_board;
}

bool Board::Initialize()
{
	// Initialize Board
	OutputDebugString(L"Initialize Board\n");
	m_board = new sf::RectangleShape(sf::Vector2f(m_width, m_height));
	m_board->setFillColor(m_boardColor);
	m_board->setOrigin(0.f, 0.f);
	m_board->setPosition(50.f, 50.f);

	return true;
}
