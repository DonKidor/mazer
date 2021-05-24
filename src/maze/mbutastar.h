#pragma once
#include <maze/maze.h>
#include <maze/mbutton.h>


class MBut_Astar : public MButton {
	public:
		MBut_Astar(sf::Vector2f position, sf::Vector2f size, Maze &maze);
		void onClick(sf::Event &ev) override;
	private:
		Maze &maze;
};
