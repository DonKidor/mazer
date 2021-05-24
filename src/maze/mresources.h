#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MResources {
	public:
		MResources(std::string npath);
		static std::string getResPath();
		static sf::Font& getFont();
		static sf::Image& getIcon();
	protected:
		static sf::Image icon;
		static std::string path;
		static sf::Font font;
};
