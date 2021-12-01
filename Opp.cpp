#include "Opp.h"
#include <iostream>
Opp::Opp( float posx, float posy)
{ //inicjuje drona na konkretnej pozycji na ekranie
	this->init();
	this->sprite.setPosition(posx, posy);
}

Opp::~Opp()
{
}

void Opp::init()
{ //wczytywanie tekstury i ustawianie statystyk drona
	if (this->texture.loadFromFile("textures/opps.png") == false)
	{
		std::cout << "nie zaladowano tekstury gracza" << std::endl;
	}

	this->currentframe = sf::IntRect(0, 0, 64, 64);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(currentframe);
	texture.setSmooth(true);
	
	
	this->hp = rand()% 10 + 1;
	this->dmg = 1;
	this->points = this->hp;
}

void Opp::update()
{ //aktualizowanie stanu drona
	this->sprite.move(-5.f, 0.f);
}

const sf::FloatRect Opp::getBounds() const
{ //getter pozycji na ekranie
	return this->sprite.getGlobalBounds();
}

const int& Opp::getPoints() const
{
	return this->points;
}

const int& Opp::getdmg() const
{
	return this->dmg;
}


void Opp::render(sf::RenderTarget * target)
{//rysowanie drona
	target->draw(this->sprite);
}
