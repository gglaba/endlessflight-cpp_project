#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Shoot
{
public:
	Shoot(sf::Texture* texture, float px, float py, float dx, float dy, float vel);
	void update();
	void render(sf::RenderTarget* target);
	const sf::FloatRect getBounds() const;
private:
	sf::Sprite shape;
	sf::Texture* texture;
	sf::Vector2f dir;
	float vel;
};

