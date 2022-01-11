#pragma once
#include <map>
#include <string>
#include <sstream>
#include "Aircraft.h"
#include "Opp.h"
#include "Shoot.h"
#include "Building.h"

class GameEngine
{
private:

	sf::IntRect startButton;


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

	float bspawn, bspawnmax;
	std::vector<Building*> buildings;
	Building* building;

	sf::Font font;
	sf::Text Pointstxt;

	sf::Text Overtext;
	sf::Text leaveinstr;

	int score;

	void statsInit();

	void interfaceInit();

	void windowInit();
	
	void Playerinit();

	void Backgroundinit();

	void TexturesInit();

	void DronesInit();

	void BuidlingsInit();


public:
	GameEngine();
	~GameEngine();
	void run();
	void update();
	void render();
	void renderBackground();
	void renderInterface();
	void Bordercollision();
	void updateEvents();
	void updateInput();
	void updateShooting();
	void updateBuildings();
	void updateDrones();
	void updateCombat();
	void updateInterface();
	void overscreen();

};
