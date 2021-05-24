#include <maze/mbuttonrand.h>

MButtonRand::MButtonRand(sf::Vector2f pos, sf::Vector2f size, Maze &maze) : MButton(pos,size,std::string("Random maze"),sf::Color(100,100,100)), maze(maze) {
}

void MButtonRand::onClick(sf::Event &ev) {
	maze.reset();
	maze.randomMaze();
}
