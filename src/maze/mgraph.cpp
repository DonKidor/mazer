#include <maze/mgraph.h>

using namespace std;

bool MGraph::isContain(sf::Vector2f p) {
	return p.x>=pos.x && p.x <=pos.x+gsize.x && p.y >= pos.y && p.y <= pos.y + gsize.y;
}

void MGraph::setPosition(sf::Vector2f position) {
	pos=position;
}

