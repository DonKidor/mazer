#include <maze/mtextbox.h>
#include <iostream>
#include <maze/mresources.h>

MTextbox::MTextbox(sf::Vector2f pos, sf::Vector2f size, sf::Color backColor) {
	onlyDigits=false;
	bColor=backColor;
	this->pos=pos;
	gsize=size;
	sText.setFont(MResources::getFont());
	sText.setStyle(sf::Text::Bold);
	sText.setCharacterSize(20);
	sText.setFillColor(sf::Color::Blue);
	text="";
	flashCounter=0;
}

void MTextbox::setOnlyDigits(bool on, int maxDigit=10) {
	onlyDigits=on;
	this->maxDigit=maxDigit;
	if(on && text.size()==0) text="0";
}

void MTextbox::onText(sf::Event &ev) {
	unsigned int t=ev.text.unicode;
	if(onlyDigits) {
		if(!(t>='0'&&t<='9') && t!=8 && t!=13) return;
	}
	if(t==13) return;
	if(t==8) {
		if(text.size()>0)
			text=text.substr(0,text.size()-1);
	} else if(onlyDigits && text.size()<std::to_string(maxDigit).size()) text+=(char)t;
	if(onlyDigits && text.size()>0 && std::stoi(text)>maxDigit) text=std::to_string(maxDigit);

}

void MTextbox::onFocused(bool f) {
	if(!f && onlyDigits && text.size()==0) text="0";
}

void MTextbox::draw(sf::RenderWindow &window) {
	if(focused) flashCounter=(flashCounter+1)%60;
	sf::RectangleShape rect;
	rect.setPosition(pos);
	rect.setSize(gsize);
	rect.setFillColor(bColor);
	
	sText.setString("A");
	const float height=sText.getGlobalBounds().height;
	sText.setString(text);
	sText.setPosition(pos+sf::Vector2f((gsize.x/2)-sText.getGlobalBounds().width/2,(gsize.y/2)-height));
	
	
	sf::RectangleShape textRect;
	textRect.setPosition(pos+sf::Vector2f(5,(gsize.y/2)-12));
	textRect.setSize(sf::Vector2f(gsize.x-10,22));
	textRect.setFillColor(sf::Color::White);
	
	
	window.draw(rect);
	window.draw(textRect);
	window.draw(sText);
	if(focused && flashCounter>30) {
		sText.setPosition(sf::Vector2f(sText.findCharacterPos(text.size()).x,pos.y+(gsize.y/2)-height));
		sText.setString("_");
		window.draw(sText);
	}
}
