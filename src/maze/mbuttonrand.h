#pragma once

#include <maze/mbutton.h>
#include <maze/maze.h>

class MButtonRand : public MButton {
	public:
		MButtonRand(sf::Vector2f pos, sf::Vector2f size, Maze &maze);
		void onClick(sf::Event &ev) override;
	private:
		Maze &maze;
};
