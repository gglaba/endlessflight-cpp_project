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
	this->infoInit();
	// ustawianie tekstury i rozmiaru sprite'a dla wylosowanego budynku
	if (this->texture.loadFromFile(building_info[frame].filename) == false)
	{
		std::cout << "nie zaladowano tekstury budynku" << std::endl;
	}
	this->currentframe = sf::IntRect(0, 0, building_info[frame].width, building_info[frame].height);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(currentframe);
	texture.setSmooth(true);

}

void Building::update()
{ //ruch budynkow
	this->sprite.move(-5.f,0.f);
}


const sf::FloatRect Building::getBounds() const
{
	return this->sprite.getGlobalBounds();
}


void Building::render(sf::RenderTarget* target)
{//rysowanie budynku
	target->draw(this->sprite);
}


void Building::infoInit()
{ //tworze informacje o budynkach w strukturze a nastepnie tworze z nich wektor 
	b1.width = 170;
	b1.height = 577;
	b1.filename = "textures/b1.png";

	b2.width = 104;
	b2.height = 435;
	b2.filename = "textures/b3.png";

	b3.width = 133;
	b3.height = 468;
	b3.filename = "textures/b4.png";

	b4.width = 232;
	b4.height = 365;
	b4.filename = "textures/b5.png";

	b5.width = 225;
	b5.height = 299;
	b5.filename = "textures/b6.png";

	if (building_info.empty() == true)
	{
		building_info.push_back(b1);
		building_info.push_back(b2);
		building_info.push_back(b3);
		building_info.push_back(b4);
		building_info.push_back(b5);
	}
}