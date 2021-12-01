#pragma once
#include <map>
#include <string>
#include <sstream>
#include "Aircraft.h"
#include "Opp.h"
#include "Shoot.h"

class GameEngine
{
private:
	sf::RenderWindow* window;
	Aircraft* player;
	sf::Texture backgroundTexture;
	sf::Sprite background;

	std::map<std::string, sf::Texture*> textrs;
	std::vector<Shoot*> bullets;

	sf::RectangleShape hpbar;
	sf::RectangleShape hpbarstat;

	float tspawn;
	float tspawnmax;
	std::vector<Opp*> drones;
	Opp* drone;

	sf::Font font;
	sf::Text Pointstxt;
	int score;

	void statsInit();

	void interfaceInit();

	void windowInit();
	
	void Playerinit();

	void Backgroundinit();

	void TexturesInit();

	void DronesInit();


public:
	GameEngine();
	~GameEngine();
	void run();
	void update();
	void updateEvents();
	void updateInput();
	void updateShooting();
	void updateDrones();
	void updateInterface();
	void render();
	void renderBackground();
	void renderInterface();
	void Bordercollision();
};

