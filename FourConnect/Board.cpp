#include "Board.h"
#include <windows.h>

Board::Board(int columns, int rows, float width, float height, sf::RenderWindow &window) :
	m_columns(columns),
	m_rows(rows),	
	m_width(width),
	m_height(height),
	m_boardColor(sf::Color::Blue),
	m_tokenRadius(40.f),
	m_window(window)
{
	m_boardPieces.resize(m_columns);
	m_tokens.resize(m_columns);
}

Board::~Board()
{
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

	m_board.resize(m_columns);
	for (auto col = 0; col < m_columns; ++col)
	{
		std::vector<int> column;
		column.resize(m_rows);
		for (auto row = 0; row < m_rows; ++row)
		{
			column.at(row) = 0;
		}

		m_board.at(col) = column;
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
	MinMax(m_board, 1);
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

void Board::ChangePlayer()
{

}

void Board::ComputeNextTurn(int stage)
{
	for (auto &column : m_board)
	{
		for (auto &token : column)
		{
			if (token == Empty)
			{
				break;
			}
		}
	}
}

void Board::RenderBoard(std::vector<std::vector<int>> board)
{
	sf::Vector2f boardStartPos(50.f, 50.f);
	sf::Vector2f tokenStartPos(50.f, m_height + 50.f);
	auto tokenOffset = 10.f;

	m_window.clear(sf::Color::Cyan);
	for (auto &boardRect : m_boardPieces)
	{
		m_window.draw(boardRect);
	}

	for (auto col = 0; col < m_columns; ++col)
	{
		for (auto row = 0; row < m_rows; ++row)
		{
			// Calculate token position
			auto position = sf::Vector2f();
			position.x = tokenStartPos.x + tokenOffset + m_tokenRadius + col * m_tokenRadius * 2 + col * tokenOffset * 2;
			position.y = tokenStartPos.y - tokenOffset - m_tokenRadius - row * m_tokenRadius * 2 - row * tokenOffset * 2;


			if (board[col][row] == 0)
			{
				auto circle = Circle(sf::Color::White, position);
				m_window.draw(circle);
			}
			else if (board[col][row] == 1)
			{
				auto circle = Circle(sf::Color::Red, position);
				m_window.draw(circle);
			}
			else if (board[col][row] == -1)
			{
				auto circle = Circle(sf::Color::Yellow, position);
				m_window.draw(circle);
			}			
		}
	}
	m_window.display();

}

int Board::MinMax(std::vector<std::vector<int>> board, int player)
{
	for (auto col = 0; col < m_columns; ++col)
	{
		auto &column = board.at(col);
		for (auto row = 0; row < m_rows; ++row)
		{
			auto &token = column.at(row);
			if (token == 0)
			{
				token = player;
				RenderBoard(board);
				while (!sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
				}
				while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
				}

				MinMax(board, player * -1);
				
				token = 0;
				break;
			}
		}
				
	}
	return 0;
}

sf::CircleShape Board::Circle(sf::Color color, sf::Vector2f pos)
{
	auto token = sf::CircleShape(m_tokenRadius);
	token.setPosition(pos);
	token.setOrigin(m_tokenRadius, m_tokenRadius);
	token.setFillColor(color);

	return token;
}
