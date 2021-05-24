#include <maze/mbutdijk.h>
#include <iostream>
#include <vector>

MBut_Dijkstra::MBut_Dijkstra(sf::Vector2f pos, sf::Vector2f size, Maze &maze) : MButton(pos,size, std::string("Dijkstra solve"), sf::Color(100,100,100)) , maze(maze) {
	
}

void MBut_Dijkstra::onClick(sf::Event &ev) {
	int size=maze.getSize();
	for(int i=0;i<size;++i)
		for(int j=0;j<size;++j)
			maze.nodes[i+1][j].color=sf::Color(100,100,100);
	std::vector<std::vector<sf::Vector2i> > parent(size,std::vector<sf::Vector2i>(size,sf::Vector2i(-1,-1)));
	std::vector<std::vector<int> > g(size,std::vector<int>(size,-1));
	sf::Vector2i bgnd[2];
	bgnd[0]=maze.bgnd[0];
	bgnd[1]=maze.bgnd[1];
	g[bgnd[0].x][bgnd[0].y]=0;
	int x,y;
	while(true) {
		x=-1;
		y=-1;
		for(int i=0;i<size;++i) {
			for(int j=0;j<size;++j) {
				if(g[i][j]>=0 && (x==-1 || g[i][j]<g[x][y])) {
					x=i;
					y=j;
				}
			}
		}
		if(x==-1 || y==-1) break;
		if(x==bgnd[1].x && y==bgnd[1].y) break;
		int nval=g[x][y]+1;
		if(x>0 && !maze.nodes[x][y].right && (g[x-1][y]==-1 || g[x-1][y]>nval)) {
			g[x-1][y]=nval;
			parent[x-1][y]=sf::Vector2i(x,y);
		}
		if(y>0 && !maze.nodes[x+1][y].up && (g[x][y-1]==-1 || g[x][y-1]>nval)) {
			g[x][y-1]=nval;
			parent[x][y-1]=sf::Vector2i(x,y);
		}
		if(x<size-1 && !maze.nodes[x+1][y].right && (g[x+1][y]==-1 || g[x+1][y]>nval)) {
			g[x+1][y]=nval;
			parent[x+1][y]=sf::Vector2i(x,y);
		}
		if(y<size-1 && !maze.nodes[x+1][y+1].up && (g[x][y+1]==-1 || g[x][y+1]>nval)) {
			g[x][y+1]=nval;
			parent[x][y+1]=sf::Vector2i(x,y);
		}
		maze.nodes[x+1][y].color=sf::Color::Yellow;
		g[x][y]=-2;
	}
	if(parent[bgnd[1].x][bgnd[1].y].x>=0) {
		sf::Vector2i p=bgnd[1];
		maze.nodes[p.x+1][p.y].color=sf::Color::Green;
		while(p!=bgnd[0]) {
			p=parent[p.x][p.y];
			maze.nodes[p.x+1][p.y].color=sf::Color::Green;
		}
	}
}
