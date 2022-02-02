#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<vector>


class Building
{
public:
	Building(float posx, float posy, int frame);
	~Building();
	void update();
	void render(sf::RenderTarget* target);
	const sf::FloatRect getBounds() const;
	void infoInit();

private:

	void init(int frame);
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect currentframe;
	float posx, posy;

	struct DATA_B
	{
		int width;
		int height;
		std::string filename;
	};

	DATA_B b1, b2, b3, b4, b5;

	std::vector<DATA_B> building_info;


};

