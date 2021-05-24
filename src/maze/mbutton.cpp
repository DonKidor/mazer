#include <maze/mbutton.h>
#include <maze/mresources.h>
#include <iostream>

MButton::MButton(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Color backColor) {
	pos=position;
	gsize=size;
	this->text=text;
	color=backColor;
	hColor=sf::Color::Green;
	font=MResources::getFont();
	high=false;
	sText.setFont(font);
	sText.setStyle(sf::Text::Bold);
	sText.setCharacterSize(20);
	sText.setFillColor(sf::Color::Blue);
}

void MButton::draw(sf::RenderWindow &window) {
	sf::RectangleShape rect;
	rect.setPosition(pos);
	rect.setSize(gsize);
	rect.setFillColor(high?hColor:color);
	sText.setPosition(pos+sf::Vector2f((gsize.x/2)-sText.getGlobalBounds().width/2,(gsize.y/2)-sText.getGlobalBounds().height));
	sText.setString(text);
	window.draw(rect);
	window.draw(sText);
	if(!isContain(sf::Vector2f(sf::Mouse::getPosition(window)))) high=false;
}

void MButton::onMouseMove(sf::Event &ev) {
	high=true;
}
