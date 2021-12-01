#include "Shoot.h"

Shoot::Shoot(sf::Texture* texture,float px,float py, float dx, float dy, float vel)
{//tworzenie pociskow
	this->texture = texture;
	this->shape.setTexture(*texture);
	this->shape.scale(.2f, .2f);
	this->shape.setPosition(px, py);
	this->dir.x = dx;
	this->dir.y = dy;
	this->vel = vel;

}


void Shoot::update()
{//aktualizowanie pociskow
	this->shape.move(this->vel * this->dir);
}

void Shoot::render(sf::RenderTarget* target)
{//rysowanie pociskow
	target->draw(this->shape);
}

const sf::FloatRect Shoot::getBounds() const
{
	return this->shape.getGlobalBounds();
}
