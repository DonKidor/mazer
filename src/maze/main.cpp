#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <maze/mresources.h>
#include <maze/maze.h>
#include <maze/mbutastar.h>
#include <maze/mbuttonrand.h>
#include <maze/mtextbox.h>
#include <maze/mbutdijk.h>
#include <maze/mbutresize.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main(int argv, char* arg[]) {
	MResources(std::string(arg[0]));
	srand(time(0));
	vector<MGraph*> vis;
	int focused=-1;
	
	
	sf::RenderWindow window(sf::VideoMode(800, 620), "Maze solver",sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	sf::Image icon=MResources::getIcon();
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
	Maze maze(26,sf::Vector2f(20,40));
	vis.push_back(&maze);
	
	MBut_Astar but(sf::Vector2f(600,50),sf::Vector2f(150,50), maze);
	vis.push_back(&but);
	
	MButtonRand brand(sf::Vector2f(600,190), sf::Vector2f(150,50), maze);
	vis.push_back(&brand);
	
	MBut_Dijkstra bijk(sf::Vector2f(600,120),sf::Vector2f(150,50),maze);
	vis.push_back(&bijk);
	
	MTextbox txt(sf::Vector2f(600,250), sf::Vector2f(60,50),sf::Color(100,100,100));
	txt.setOnlyDigits(true,28);
	vis.push_back(&txt);
	
	MButresize butrz(sf::Vector2f(670,250), sf::Vector2f(80,50), maze, txt);
	vis.push_back(&butrz);
	
	maze.randomMaze();
	
	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
        	
        	if(event.type==sf::Event::MouseButtonPressed) {
        		if(focused>=0) vis[focused]->setFocused(false);
        		focused=-1;
        		for(int i=0;i<vis.size();++i) {
	        		if(vis[i]->isContain(sf::Vector2f(event.mouseButton.x,event.mouseButton.y))) {
	        			focused=i;
						vis[i]->onClick(event);
						vis[i]->setFocused(true);
					}
        		}
			}
			if(event.type==sf::Event::MouseMoved) {
        		for(int i=0;i<vis.size();++i) {
	        		if(vis[i]->isContain(sf::Vector2f(event.mouseMove.x,event.mouseMove.y))) vis[i]->onMouseMove(event);
        		}
			}
			if(event.type==sf::Event::KeyPressed) {
				if(focused>=0) vis[focused]->onKeyPress(event);
			}
			if(event.type==sf::Event::TextEntered) {
				if(focused>=0) vis[focused]->onText(event);
			}
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        
        for(int i=0;i<vis.size();++i)
        	vis[i]->draw(window);
        window.display();
    }
	return 0;
}
