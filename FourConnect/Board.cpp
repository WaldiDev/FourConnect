#include "Board.h"
#include <windows.h>

Board::Board(int columns, int rows, float width, float height) :
	m_columns(columns),
	m_rows(rows),	
	m_width(width),
	m_height(height),
	m_boardColor(sf::Color::Blue),
	m_board(nullptr),
	m_tokenRadius(40.f)
{
	m_boardPieces.resize(m_columns);
	m_tokens.resize(m_columns);
}

Board::~Board()
{
	delete m_board;
}

bool Board::Initialize()
{
	// Initialize Board
	OutputDebugString(L"Initialize Board\n");
		sf::Vector2f boardStartPos(50.f, 50.f);
	sf::Vector2f tokenStartPos(50.f, m_height + 50.f);
	auto tokenOffset = 10.f;

	for (auto col = 0; col < m_columns; ++col)
	{
		auto size = sf::Vector2f();
		size.x = 2 * (m_tokenRadius + tokenOffset);
		size.y = 2 * (m_tokenRadius + tokenOffset) * m_rows;
		auto boardRect = sf::RectangleShape(size);
		boardRect.setFillColor(m_boardColor);
		boardRect.setPosition(boardStartPos.x + size.x * col, boardStartPos.y);
		m_boardPieces.at(col) = boardRect;
		
	}

	// Initialize Tokens
	OutputDebugString(L"Initialize Tokens\n");	
	for (auto col = 0; col < m_columns; ++col)
	{
		std::vector<sf::CircleShape> tokens;
		tokens.resize(m_rows);
		for (auto row = 0; row < m_rows; ++row)
		{
			// Calculate token position
			auto position = sf::Vector2f();
			position.x = tokenStartPos.x + tokenOffset + m_tokenRadius + col * m_tokenRadius * 2 + col * tokenOffset * 2;
			position.y = tokenStartPos.y - tokenOffset - m_tokenRadius - row * m_tokenRadius * 2 - row * tokenOffset * 2;

			auto token = sf::CircleShape(m_tokenRadius);
			token.setPosition(position);
			token.setOrigin(m_tokenRadius, m_tokenRadius);

			tokens.at(row) = token;
		}
		m_tokens.at(col) = tokens;
	}

	return true;
}

void Board::Update()
{	
}

void Board::Render(sf::RenderWindow& window)
{
	for (auto &boardRect : m_boardPieces)
	{
		window.draw(boardRect);
	}

	for (auto &tokenCol : m_tokens)
	{
		for (auto &token : tokenCol)
		{
			window.draw(token);
		}		
	}
}

void Board::OnMouseMoved(sf::Vector2f mouseCoord)
{
	for (auto &boardRect : m_boardPieces)
	{
		auto rect = boardRect.getGlobalBounds();
		if (rect.contains(mouseCoord))
		{
			boardRect.setFillColor(sf::Color(0, 0, 139));
		}
		else
		{
			boardRect.setFillColor(m_boardColor);
		}
	}
}

void Board::OnMouseButtonPressed(sf::Vector2f mouseCoord, int button)
{
	if (button != 0)
	{
		return;
	}

	auto i = 0;
	for (auto &boardRect : m_boardPieces)
	{		
		auto rect = boardRect.getGlobalBounds();
		if (rect.contains(mouseCoord))
		{
			for (auto &token : m_tokens.at(i))
			{
				if (token.getFillColor() == sf::Color::White)
				{
					token.setFillColor(sf::Color::Red);
					return;
				}
			}
		}
		i++;
	}
}

