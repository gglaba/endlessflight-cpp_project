#include "Aircraft.h"
#include <iostream>

void Aircraft::Spriteinit()
{

	this->currentframe = sf::IntRect(0, 0, 445, 312);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(currentframe);
	texture.setSmooth(true);
	this->sprite.scale(.25f, .25f);


}

//³adowanie tekstury i skalowanie sprita gracza
void Aircraft::Textureinit()
{
	if (this->texture.loadFromFile("textures/spritesheet.png") == false)
	{
		std::cout << "nie zaladowano tekstury gracza" << std::endl;
	}
}



Aircraft::Aircraft()
{
	this->variablesInit();
	this->Textureinit();
	this->Spriteinit();
}


//rysowanie gracza na ekranie
void Aircraft::render(sf::RenderTarget& target)
{
	if (this->shooting == true) //animacja strzalu zalezna od bool isshooting (true gdy gracz wcisnie s)
	{
		this->currentframe.left += 443;
		if (this->currentframe.left >= 2215)
		{
			this->currentframe.left = 0;
		}
		this->sprite.setTextureRect(this->currentframe);
		this->shooting = false;
	}
	else
	{ //animacja ruchu gracza
		this->currentframe.left += 443;
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
	//zwracanie aktualnej pozycji gracza
	return this->sprite.getPosition();
}

void Aircraft::isShooting(bool state)
{
	this->shooting = state;
}

bool Aircraft::Attack()
{ //mechanika cooldownu strzelania
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

	}
}

void Aircraft::variablesInit()
{//inicjowanie statystyk gracza
	this->maxhp = 50;
	this->velocity = 5.0f;
	this->cooldownMax = 25.f;
	this->cooldown = 0.f;
	this->hp = maxhp;

}

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
}

void Aircraft::loseHp(const int dmg)
{
	this->hp -= dmg;
	if (this->hp <= 0)
	{
		this->hp = 0;
	}
}


