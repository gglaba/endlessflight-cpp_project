#include "Building.h"
#include <iostream>

Building::Building(float posx, float posy, int frame)
{
	this->init(frame);
	this->sprite.setPosition(posx, 768 - this->sprite.getGlobalBounds().height );
}

Building::~Building()
{


}


void Building::init(int frame)
{
	/*if (this->texture.loadFromFile("textures/buildings.png") == false)
	{
		std::cout << "nie zaladowano tekstury gracza" << std::endl;
	}*/

	if (frame == 1)
	{
		if (this->texture.loadFromFile("textures/b1.png") == false)
		{
			std::cout << "nie zaladowano tekstury budynku" << std::endl;
		}
		this->currentframe = sf::IntRect(0, 0, 181, 317);
	}

	else if (frame == 2)
	{
		if (this->texture.loadFromFile("textures/b3.png") == false)
		{
			std::cout << "nie zaladowano tekstury budynku" << std::endl;
		}
		this->currentframe = sf::IntRect(0, 0, 112, 491);
	}

	else if (frame == 3)
	{
		if (this->texture.loadFromFile("textures/b4.png") == false)
		{
			std::cout << "nie zaladowano tekstury budynku" << std::endl;
		}
		this->currentframe = sf::IntRect(0, 0, 137, 396);
	}
	else if (frame == 4)
	{
		if (this->texture.loadFromFile("textures/b5.png") == false)
		{
			std::cout << "nie zaladowano tekstury budynku" << std::endl;
		}
		this->currentframe = sf::IntRect(0, 0, 222, 463);
	}

	else if (frame == 5)
	{
		if (this->texture.loadFromFile("textures/b6.png") == false)
		{
			std::cout << "nie zaladowano tekstury budynku" << std::endl;
		}
		this->currentframe = sf::IntRect(0, 0, 221, 317);
	}
	
	//this->currentframe = sf::IntRect(0, 0, 64, 64);
	
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