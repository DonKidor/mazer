#pragma once

#include <string>
#include <maze/mgraph.h>

class MButton : public MGraph {
	public:
		MButton(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Color backColor);
		void draw(sf::RenderWindow &window) override;
		void onMouseMove(sf::Event &ev) override;
	private:
		bool high;
		sf::Text sText;
		sf::Font font;
		std::string text;
		sf::Color color;
		sf::Color hColor;
};
