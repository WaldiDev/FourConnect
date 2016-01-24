#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>
#include "Menue.h"

int main()
{		
	auto boardColumns = 7;
	auto boardRows = 6;
	auto boardWidth = boardColumns * 100.f;
	auto boardHeight = boardRows * 100.f;

	auto windowWidth = boardColumns * 100 + 100;
	auto windowHeight = boardRows * 100 + 100;


	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Four Connect");
	
	Menue menue;
	if (!menue.Initialize())
	{
		std::cout << "Initialize menue failed!" << std::endl;
		return -1;
	}

	Board board(boardColumns, boardRows, boardWidth, boardHeight);
	if (!board.Initialize())
	{
		std::cout << "Initialize board failed!" << std::endl;
		return -1;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color::Cyan);
		if (menue.IsActive())
		{
			menue.Render(window);
		} 
		else
		{
			window.draw(*board.GetDrawableBoard());
		}
		
		window.display();
	}

	return 0;
}
