#include <maze/mresources.h>
#include <iostream>

sf::Font MResources::font;
std::string MResources::path;
sf::Image MResources::icon;

MResources::MResources(std::string npath) {
	int b=npath.rfind("bin");
	if(b<npath.length())
		path = npath.substr(0,npath.rfind("bin"))+"res/";
	else
		path="../res/";
	
	font.loadFromFile(path+"arial.ttf");
	icon.loadFromFile(path+"icon.png");
}
std::string MResources::getResPath() {
	return MResources::path;
}
sf::Font& MResources::getFont() {
	return MResources::font;
}
sf::Image& MResources::getIcon() {
	return MResources::icon;
}
