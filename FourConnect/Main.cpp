#include "TGUI/TGUI.hpp"
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
	tgui::Gui gui(window);
	auto button = std::make_shared<tgui::Button>();
	gui.add(button);
	//Menue menue;
	/*if (!menue.Initialize())
	{
		std::cout << "Initialize menue failed!" << std::endl;
		return -1;
	}*/

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
			else if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
				auto mouseCoord = window.mapPixelToCoords(mousePos);
				board.OnMouseMoved(mouseCoord);
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
				auto mouseCoord = window.mapPixelToCoords(mousePos);
				board.OnMouseButtonPressed(mouseCoord, event.mouseButton.button);
			}
			/*else if (event.type == sf::Event::MouseButtonPressed)
			{
				auto mousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
				auto mouseCoord = window.mapPixelToCoords(mousePos);
				if (menue.IsActive())
				{
					menue.CheckClickEvent(mouseCoord);
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				auto mousePos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
				auto mouseCoord = window.mapPixelToCoords(mousePos);
				if (menue.IsActive())
				{
					menue.CheckReleaseEvent(mouseCoord);
				}
			}*/
			gui.handleEvent(event);
		}

		window.clear(sf::Color::Cyan);
		/*if (menue.IsActive())
		{
			menue.Render(window);
		} 
		else
		{
			window.draw(*board.GetDrawableBoard());
		}*/
		
		//gui.draw();
		board.Render(window);
		window.display();
	}

	return 0;
}
