#pragma once

#include <maze/mgraph.h>
#include <string>

class MTextbox : public MGraph {
	public:
		MTextbox(sf::Vector2f pos, sf::Vector2f size, sf::Color backColor);
		void onText(sf::Event &ev) override;
		void draw(sf::RenderWindow &window) override;
		void onFocused(bool f) override;
		std::string getText() { return text;};
		void setText(std::string txt) { text=txt;};
		void setOnlyDigits(bool on, int maxDigit);
	private:
		int maxDigit;
		bool onlyDigits;
		int flashCounter;
		std::string text;
		sf::Text sText;
		sf::Color bColor;
};
