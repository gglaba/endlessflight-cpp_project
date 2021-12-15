#pragma once
#include <SFML/Graphics.hpp>

class Building
{
public:
	Building(float posx, float posy);
	~Building();
	void update();
	void render(sf::RenderTarget* target);
	const sf::FloatRect getBounds() const;

private:

	void init();
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect currentframe;
	float posx, posy;
};

