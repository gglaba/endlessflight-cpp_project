#include "Building.h"
#include <iostream>

Building::Building(float posx, float posy)
{
	this->init();
	this->sprite.setPosition(posx, posy);
}

Building::~Building()
{


}


void Building::init()
{
	if (this->texture.loadFromFile("textures/buildings.png") == false)
	{
		std::cout << "nie zaladowano tekstury gracza" << std::endl;
	}

	int frame = rand() % 8 + 1;

	switch (frame)
	{
	case 1:
		this->currentframe = sf::IntRect(0, 0, 183, 321);
		std::cout << "wylosowalem 1!!!!" << std::endl;
		
	case 2:
		this->currentframe = sf::IntRect(245, 0, 388, 203);
	case 3:
		this->currentframe = sf::IntRect(753, 0, 256, 315);
	case 4:
		this->currentframe = sf::IntRect(1057, 0, 228, 315);
	case 5:
		this->currentframe = sf::IntRect(1387, 0, 138, 315);
	case 6:
		this->currentframe = sf::IntRect(1614, 0, 188, 217);
	case 7:
		this->currentframe = sf::IntRect(1854, 0, 186, 455);
	case 8:
		this->currentframe = sf::IntRect(2080, 0, 277, 410);
	}
	//this->currentframe = sf::IntRect(0, 0, 860, 880);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(currentframe);
	texture.setSmooth(true);

}

void Building::update()
{
	this->sprite.move(-5.f,0.f);
}


const sf::FloatRect Building::getBounds() const
{
	return this->sprite.getGlobalBounds();
}



void Building::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}