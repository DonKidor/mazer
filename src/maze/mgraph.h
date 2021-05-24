#pragma once
#include <SFML/Graphics.hpp>


class MGraph {
	public:
		virtual bool isContain(sf::Vector2f p);
		void setPosition(sf::Vector2f position);
		virtual void draw(sf::RenderWindow &window) = 0;
		virtual void onClick(sf::Event &ev) {};
		virtual void onMouseMove(sf::Event &ev) {};
		virtual void onKeyPress(sf::Event &ev) {};
		virtual void onText(sf::Event &ev) {};
		void setFocused(bool f) { focused=f; onFocused(f);};
		virtual void onFocused(bool f) {};
	protected:
		bool focused=false;
		sf::Vector2f pos;
		sf::Vector2f gsize;
};


