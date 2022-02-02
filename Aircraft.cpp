#include "Aircraft.h"
#include <iostream>

void Aircraft::Spriteinit()
{
	//ustawianie aktualnej klatki sprite'a gracza i skalowanie
	this->currentframe = sf::IntRect(0, 0, 445, 312);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(currentframe);
	texture.setSmooth(true);
	this->sprite.scale(.25f, .25f);


}

//ładowanie tekstury i skalowanie sprita gracza
void Aircraft::Textureinit()
{
	if (this->texture.loadFromFile("textures/spritesheet.png") == false)
	{
		std::cout << "nie zaladowano tekstury gracza" << std::endl;
	}
}



Aircraft::Aircraft()
{ //inicjacja gracza
	this->variablesInit();
	this->Textureinit();
	this->Spriteinit();
}

Aircraft::~Aircraft()
{
}

//rysowanie gracza na ekranie
void Aircraft::render(sf::RenderTarget& target)
{
	if (this->shooting == true) //jezeli gracz strzela zapetlane sa klatki z animacja strzelania
	{
		this->currentframe.left += 886;
		if (this->currentframe.left >= 3544)
		{
			this->currentframe.left = 0;
		}
		this->currentframe.left += 443;
		if (this->currentframe.left >= 2215)
		{
			this->currentframe.left = 0;
		}
		this->sprite.setTextureRect(this->currentframe);
		this->shooting = false;
	}
	else
	{
		this->currentframe.left += 443; //zapetlanie klatek z animacja lotu
		if (this->currentframe.left >= 886)
		{
			this->currentframe.left = 0;
		}
		this->sprite.setTextureRect(this->currentframe);
	}

	target.draw(this->sprite);

}


//poruszanie sie
void Aircraft::move(const float dx, const float dy)
{
	this->sprite.move(this->velocity * dx, this->velocity * dy);

}

//funkcja do zwracania krawedzi sprita
const sf::FloatRect Aircraft::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

//zmienianie pozycji gracza
void Aircraft::setPos(const float x, const float y)
{
	this->sprite.setPosition(x, y);

}

const sf::Vector2f& Aircraft::getPos() const
{

	return this->sprite.getPosition();
}

void Aircraft::isShooting(bool state)
{
	this->shooting = state;
}

//mechanika cooldownu
bool Aircraft::Attack()
{
	if (this->cooldown >= this->cooldownMax)
	{
		this->cooldown = 0.f;
		return true;
	}
	return false;
}

void Aircraft::update()
{
	this->updateCooldown();
}

void Aircraft::updateCooldown()
{
	if (this->cooldown < this->cooldownMax)
	{
		this->cooldown += 1.f;
		std::cout << cooldown << std::endl;
	}
	

}

void Aircraft::variablesInit()
{ //inicjowanie statystyk gracza
	this->maxhp = 50;
	this->velocity = 5.0f;
	this->cooldownMax = 20.f;
	this->cooldown = 0.f;
	this->hp = maxhp;

}

//gettery i settery statystyk
const int& Aircraft::getHp() const
{
	return this->hp;
}

const int& Aircraft::getMaxhp() const
{
	return this->maxhp;
}

void Aircraft::setHp(const int newhp)
{
	this->hp = newhp;
	if (this->hp > this->maxhp)
	{
		this->hp = this->maxhp;
	}
}

void Aircraft::loseHp(const int dmg)
{
	this->hp -= dmg;
	if (this->hp <= 0)
	{
		this->hp = 0;
	}
}


