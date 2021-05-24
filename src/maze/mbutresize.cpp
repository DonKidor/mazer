#include <maze/mbutresize.h>
#include <string>

MButresize::MButresize(sf::Vector2f pos, sf::Vector2f size, Maze &maze, MTextbox &text) : MButton(pos, size, "resize", sf::Color(100,100,100)), maze(maze), text(text){
}


void MButresize::onClick(sf::Event &ev) {
	int t=0;
	try{
		t=std::stoi(text.getText());
	} catch(std::invalid_argument& ia) {
		return;
	}
	if(t>3) maze.resize(t);
}
