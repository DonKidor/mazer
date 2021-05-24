#pragma once

#include <maze/maze.h>
#include <maze/mbutton.h>
#include <maze/mtextbox.h>

class MButresize : public MButton {
	public:
		MButresize(sf::Vector2f pos, sf::Vector2f size, Maze &maze, MTextbox &text);
		void onClick(sf::Event &ev) override;
	private:
		Maze &maze;
		MTextbox &text;
};
