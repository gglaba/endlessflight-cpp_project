#pragma once
#include <SFML/Graphics.hpp>

class Opp
{
public:
	Opp(float posx, float posy);
	~Opp();
	void update();
	void render(sf::RenderTarget* target);
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getdmg() const;

private:

	void init();
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect currentframe;
	int hp,dmg,points;
	float posx, posy;
};

