#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <maze/mgraph.h>

using namespace std;

struct node {
	node() {
		up=true;
		right=true;
		color=sf::Color(100,100,100);
	}
	node(bool u, bool r) {
		up=u;
		right=r;
		color=sf::Color(100,100,100);
	}
	bool up;
	bool right;
	sf::Color color;
};

class Maze : public MGraph {
	public:
		Maze(int size, sf::Vector2f position);
		void draw(sf::RenderWindow &window) override;
		void randomMaze();
		void reset();
		void resize(int nsize);
		void onClick(sf::Event &ev) override;
		void onMouseMove(sf::Event &ev) override;
		sf::Vector2i bgnd[2];
		vector<vector<node> > nodes;
		int getSize() {return size;};
	private:
		void editMaze(sf::Vector2f rpos, bool lfrg);
		float nodeSize;
		int size;
};
