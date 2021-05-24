#include <maze/maze.h>
#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;

Maze::Maze(int size, sf::Vector2f position) {
	this->size=size;
	pos=position;
	nodes.resize(size+1,vector<node>(size+1));
	nodeSize=20;
	gsize=sf::Vector2f(nodeSize*size,nodeSize*size);
	for(int i=0;i<size+1;++i) nodes[0][i].up=false;
	for(int i=0;i<size+1;++i) nodes[i][size].right=false;
	bgnd[0]=sf::Vector2i(0,0);
	bgnd[1]=sf::Vector2i(0,0);
}

void Maze::editMaze(sf::Vector2f rpos, bool lfrg) {
	int x,y;
	x=rpos.x/nodeSize;
	y=rpos.y/nodeSize;
	if(!(x>=0 && y>=0 && x<size && y<size)) return;
	while(rpos.x>=nodeSize) rpos.x-=nodeSize;
	while(rpos.y>=nodeSize) rpos.y-=nodeSize;
	if(rpos.y>rpos.x) {
		if(rpos.y< nodeSize-rpos.x ) {
			if(rpos.x <nodeSize/4)
				nodes[x][y].right=lfrg;
		}
		else if(rpos.y >nodeSize/4) {
			nodes[x+1][y+1].up=lfrg;
		}
	} else {
		if(rpos.y< nodeSize-rpos.x) {
			if(rpos.y < nodeSize/4)
				nodes[x+1][y].up=lfrg;
		}
		else if(rpos.x>nodeSize/4) {
			nodes[x+1][y].right=lfrg;
		}
	}
}

void Maze::onMouseMove(sf::Event &ev) {
	bool lfrg;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) lfrg=true;
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) lfrg=false;
	else return;
	sf::Vector2f rpos= sf::Vector2f(ev.mouseMove.x, ev.mouseMove.y) - pos;
	editMaze(rpos,lfrg);
}

void Maze::onClick(sf::Event &ev) {
	bool lfrg;
	if(ev.mouseButton.button==sf::Mouse::Button::Left) lfrg=true;
	else if(ev.mouseButton.button==sf::Mouse::Button::Right) lfrg=false;
	else return;
	sf::Vector2f rpos= sf::Vector2f(ev.mouseButton.x, ev.mouseButton.y) - pos;
	editMaze(rpos,lfrg);
}

void Maze::resize(int nsize) {
	if(nsize==size) return;
	size=nsize;
	nodes.resize(size+1);
	for(int i=0;i<size+1;++i) nodes[i].resize(size+1);
	gsize=sf::Vector2f(nodeSize*size,nodeSize*size);
	for(int i=0;i<size+1;++i) nodes[0][i].up=false;
	for(int i=0;i<size+1;++i) nodes[i][size].right=false;
	bgnd[0]=sf::Vector2i(0,0);
	bgnd[1]=sf::Vector2i(0,0);
	reset();
	randomMaze();
}

void Maze::reset() {
	for(int i=0;i<size+1;++i)
		for(int j=0;j<size+1;++j) {
			nodes[i][j].up=true;
			nodes[i][j].right=true;
			nodes[i][j].color=sf::Color(100,100,100);
		}
	for(int i=0;i<size+1;++i) nodes[0][i].up=false;
	for(int i=0;i<size+1;++i) nodes[i][size].right=false;
}



void Maze::randomMaze() {
	int x,y;
	x=0;
	y=0;
	bool visited[size][size];
	for(int i=0;i<size;++i)
		for(int j=0;j<size;++j)
			visited[i][j]=false;
	stack<sf::Vector2i> q;
	q.push(sf::Vector2i(x,y));
	while(q.size()>0) {
		x=q.top().x;
		y=q.top().y;
		visited[x][y]=true;
		vector<sf::Vector2i> var;
		if(x>0 && !visited[x-1][y]) var.push_back(sf::Vector2i(x-1,y));
		if(y>0 && !visited[x][y-1]) var.push_back(sf::Vector2i(x,y-1));
		if(x<size-1 && !visited[x+1][y]) var.push_back(sf::Vector2i(x+1,y));
		if(y<size-1 && !visited[x][y+1]) var.push_back(sf::Vector2i(x,y+1));
		if(var.size()==0) {
			q.pop();
		} else {
			sf::Vector2i np=var[rand()%var.size()];
			q.push(np);
			if(y>np.y) nodes[x+1][y].up=false;
			if(y<np.y) nodes[np.x+1][np.y].up=false;
			if(x<np.x) nodes[x+1][y].right=false;
			if(x>np.x) nodes[np.x+1][np.y].right=false;
		}
		
	}
	for(int i=0;i<size;++i) {
		bool flag=true;
		while(flag) {
			x=rand()%size;
			y=rand()%size;
			switch(rand()%2) {
				case 0:
					if(x<size-1 && nodes[x+1][y].right) {
						nodes[x+1][y].right=false;
						flag=false;
					}
					break;
				case 1:
					if(y>0 && nodes[x+1][y].up) {
						nodes[x+1][y].up=false;
						flag=false;
					}
					break;
			}
			
		}
	}
	for(int i=0;i<2;++i) {
		bool flag=false;
		do {
			flag=false;
			int r=rand()%size;
			switch(rand()%4) {
				case 0:
					if(nodes[0][r].right) {
						nodes[0][r].right=false;
						nodes[1][r].color=sf::Color::Red;
						bgnd[i]=sf::Vector2i(0,r);
						break;
					}
				case 1:
					if(nodes[1+r][0].up) {
						nodes[1+r][0].up=false;
						nodes[1+r][0].color=sf::Color::Red;
						bgnd[i]=sf::Vector2i(r,0);
						break;
					}
				case 2:
					if(nodes[size][r].right) {
						nodes[size][r].right=false;
						nodes[size][r].color=sf::Color::Red;
						bgnd[i]=sf::Vector2i(size-1,r);
						break;
					}
				case 3:
					if(nodes[1+r][size].up) {
						nodes[1+r][size].up=false;
						nodes[1+r][size-1].color=sf::Color::Red;
						bgnd[i]=sf::Vector2i(r,size-1);
						break;
					}
					flag=true;
			}
		} while(flag);
	}
}


void Maze::draw(sf::RenderWindow &window) {
	sf::RectangleShape back(pos);
	back.setSize(sf::Vector2f(-nodeSize,nodeSize));
	
	
	
	sf::RectangleShape rectV(pos);
	rectV.setSize(sf::Vector2f(-4,nodeSize+4));
	rectV.setFillColor(sf::Color::Black);
	sf::RectangleShape rectH(pos);
	rectH.setSize(sf::Vector2f(-nodeSize-4,-4));
	rectH.setFillColor(sf::Color::Black);
	for(int i=0;i<nodes.size();++i) {
		for(int j=0;j<nodes[i].size();++j) {
			rectV.setPosition(pos+sf::Vector2f(i*nodeSize,j*nodeSize-4));
			rectH.setPosition(pos+sf::Vector2f(i*nodeSize,j*nodeSize));
			back.setFillColor(nodes[i][j].color);
			back.setPosition(pos+sf::Vector2f(i*nodeSize,j*nodeSize));
			if(i>0 && j < size) window.draw(back);
			if(nodes[i][j].right)window.draw(rectV);
			if(nodes[i][j].up)window.draw(rectH);
		}
	}
}
