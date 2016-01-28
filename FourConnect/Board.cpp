#include "Board.h"
#include <windows.h>
#include "Node.h"

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
	m_startNode = new Node(0);
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

	// Horizontal win conditions
	for (auto row = 0; row < m_rows; ++row)
	{
		for (auto col = 0; col < 4; ++col)
		{			
			auto pos1 = m_rows * (col + 0) + row;
			auto pos2 = m_rows * (col + 1) + row;
			auto pos3 = m_rows * (col + 2) + row;
			auto pos4 = m_rows * (col + 3) + row;
			std::vector<int> wins;
			wins.push_back(pos1);
			wins.push_back(pos2);
			wins.push_back(pos3);
			wins.push_back(pos4);
			m_winConditions.push_back(wins);
		}
	}

	// Vertical win conditions
	for (auto col = 0; col < m_columns; ++col)
	{
		for (auto row = 0; row < 3; ++row)
		{
			auto pos1 = m_rows * col + row + 0;
			auto pos2 = m_rows * col + row + 1;
			auto pos3 = m_rows * col + row + 2;
			auto pos4 = m_rows * col + row + 3;
			std::vector<int> wins;
			wins.push_back(pos1);
			wins.push_back(pos2);
			wins.push_back(pos3);
			wins.push_back(pos4);
			m_winConditions.push_back(wins);
		}
	}

	// Diagonal win conditions
	DiagonalCheck1(3); 
	DiagonalCheck1(4); DiagonalCheck1(9);
	DiagonalCheck1(5); DiagonalCheck1(10); DiagonalCheck1(15);
	DiagonalCheck1(11); DiagonalCheck1(16); DiagonalCheck1(21);
	DiagonalCheck1(17); DiagonalCheck1(22);
	DiagonalCheck1(23);

	DiagonalCheck2(23);
	DiagonalCheck2(29); DiagonalCheck2(22);
	DiagonalCheck2(35); DiagonalCheck2(28); DiagonalCheck2(21);
	DiagonalCheck2(41); DiagonalCheck2(34); DiagonalCheck2(27);
	DiagonalCheck2(40); DiagonalCheck2(33);
	DiagonalCheck2(39);
	return true;
}

void Board::Update()
{
	//MinMax(m_board, 1, 0);
	MiniMax(m_board, 1, m_startNode, 0);
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

int Board::MinMax(std::vector<std::vector<int>> board, int player, int horizont)
{
	if (horizont >= 5)
	{
		return 0;
	}

	auto winner = HasWon(board);
	if (winner != 0)
		return winner * player;

		auto move = -1;
	int score = -2;

	for (auto col = 0; col < m_columns; ++col)
	{
		auto &column = board.at(col);
		for (auto row = 0; row < m_rows; ++row)
		{
			auto &token = column.at(row);
			if (token == 0)
			{
				token = player;
				auto thisScore = MinMax(board, player * -1, horizont);
				if (thisScore > score)
				{
					score = thisScore;
					move = col * m_columns + row;
				}
				//RenderBoard(board);				
				token = 0;				
				break;
			}
		}
				
	}

	if (move == -1) return 0;
	return score;
}


void Board::MiniMax(std::vector<std::vector<int>> board, int player, Node* node, int horizont)
{
	auto winner = HasWon(board);
	
	//if (winner != 0)
	//{
		node->SetWeight(winner);
		//return;
	//}

	if (horizont >= 4)
	{
		return;
	}	

	horizont++;

	for (auto col = 0; col < m_columns; ++col)
	{
		auto &column = board.at(col);
		for (auto row = 0; row < m_rows; ++row)
		{
			auto &token = column.at(row);
			if (token == 0)
			{
				auto edge = new Edge();
				edge->SetStartNode(node);

				auto targetNode = new Node(horizont);
				edge->SetTargetNode(targetNode);

				node->AddEdge(edge);

				token = player;
				MiniMax(board, player * -1, targetNode, horizont);
				token = 0;
				break;
			}
		}
	}
}

sf::CircleShape Board::Circle(sf::Color color, sf::Vector2f pos)
{
	auto token = sf::CircleShape(m_tokenRadius);
	token.setPosition(pos);
	token.setOrigin(m_tokenRadius, m_tokenRadius);
	token.setFillColor(color);
	
	return token;
}

int Board::HasWon(std::vector<std::vector<int>> board)
{
	auto raiting = 0;
	for (auto &condition : m_winConditions)
	{
		auto winCounter = 0;
		for (auto field : condition)
		{
			auto col = field / m_rows;
			int row;
			if (col == 0)
			{
				row = field;
			}
			else
			{
				row = field % (col * m_rows);
			}
			
			if (!board[col][row] == 0)
			{
				winCounter += board[col][row];
			}			
		}

		if (winCounter == 3 || winCounter == -3)
		{
			raiting += 3;
		}
		else if (winCounter == 2 || winCounter == -2)
		{
			raiting += 2;
		}
		else if (winCounter == 1 || winCounter == -1)
		{
			raiting++;
		}
		
		if (winCounter <= -4 )
		{
			return -100;
		}
		if (winCounter >= 4)
		{
			return 100;
		}		
	}

	return raiting;
}

void Board::DiagonalCheck1(int start)
{
	std::vector<int> wins;
	for (auto i = 0; i < 4; ++i)
	{
		wins.push_back(start + i * 5);
	}
	m_winConditions.push_back(wins);
}

void Board::DiagonalCheck2(int start)
{
	std::vector<int> wins;
	for (auto i = 0; i < 4; ++i)
	{
		wins.push_back(start + i * -7);
	}
	m_winConditions.push_back(wins);
}