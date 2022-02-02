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

	sf::Text mtitle;
	sf::Text mplay;
	sf::Text mexit;
	sf::Text minstr;

	sf::Color color;


	bool m_isPlaySelected;
	bool m_isExitSelected;
	bool m_isPlayPressed;
	bool m_isExitPressed;

	bool isPlayOn;

	float score;

	void statsInit();

	void interfaceInit();

	void windowInit();
	
	void Playerinit();

	void Backgroundinit();

	void TexturesInit();

	void DronesInit();

	void BuidlingsInit();

	void MenuInit();


public:
	GameEngine();
	~GameEngine();
	void run();
	void update();
	void render();
	void renderBackground();
	void renderInterface();
	void renderMenu();
	void Bordercollision();
	void updateEvents();
	void updateInput();
	void updateShooting();
	void updateBuildings();
	void updateDrones();
	void updateCombat();
	void updateInterface();
	void updateMenu();
	void overscreen();
	
};
