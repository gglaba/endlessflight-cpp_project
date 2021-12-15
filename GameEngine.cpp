#include "GameEngine.h"
#include <iostream>


GameEngine::GameEngine()
{
	//inicjowanie poszczegolnych elementow gry
	this->windowInit();
	this->TexturesInit();
	this->Playerinit();
	this->Backgroundinit();
	this->statsInit();
	this->DronesInit();
	this->BuidlingsInit();
	this->interfaceInit();
}

GameEngine::~GameEngine()
{
	//destruktor 
	delete this->window;
	delete this->player;

	for (auto& i : this->textrs) //usuwanie tekstur 
	{
		delete i.second;
	}

	for (auto* i : this->bullets) //usuwanie pozostalych pociskow
	{
		delete i;
	}

	for (auto* i : this->drones) //usuwanie wrogow
	{
		delete i;
	}

	for (auto* i : this->buildings)
	{
		delete i;
	}
}

void GameEngine::run()
{

	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}


void GameEngine::statsInit()
{
	this->score = 0;
}

void GameEngine::interfaceInit()
{ //inicjowanie tekstur dla interfejsu i wskaznika hp
	if (!this->font.loadFromFile("textures/font.otf"))
	{
		std::cout << " nie wczytano czcionki";
	}
	this->Pointstxt.setFont(this->font);
	this->Pointstxt.setCharacterSize(24);
	this->Pointstxt.setFillColor(sf::Color(0, 255, 0));
	this->Pointstxt.setPosition(400, 0);
	this->Pointstxt.setStyle(sf::Text::Bold);
	//this->Pointstxt.setString("test");

	this->hpbar.setSize(sf::Vector2f(200.f, 10.f));
	this->hpbar.setFillColor(sf::Color(255, 51, 102));
	this->hpbar.setPosition(5.f, 5.f);
	this->hpbarstat = this->hpbar;
	this->hpbarstat.setFillColor(sf::Color(50, 50, 50, 100));

}

//inicjowanie okna gry
void GameEngine::windowInit()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1024, 768), "Endless Flight", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

//inicjowanie gracza
void GameEngine::Playerinit()
{
	this->player = new Aircraft();
}


//³adowanie i skalowanie tekstury t³a
void GameEngine::Backgroundinit()
{ //inicjowanie tla
	if (this->backgroundTexture.loadFromFile("textures/background.png") == false)
	{
		std::cout << "nie zaladowano tekstury tla" << std::endl;
	}
	this->background.scale(0.5f, 0.5f);
	this->background.setTexture(this->backgroundTexture);

}

void GameEngine::TexturesInit()
{
	//inicjuje tekstury pociskow ( w domysle bedzie ich wiecej niz 1)
	this->textrs["bullet"] = new sf::Texture();
	this->textrs["bullet"]->loadFromFile("textures/Bullet (1).png");
}

void GameEngine::DronesInit()
{
	//inicjowanie zmiennych spawnowania sie dronow
	this->tspawnmax = 30.f;
	this->tspawn = this->tspawnmax;
}

void GameEngine::BuidlingsInit()
{
	this->bspawnmax = 30.f;
	this->bspawn = this->bspawnmax;

}




//sondowanie eventow
void GameEngine::update()
{
	//aktualizowanie poszczegolnych elementow gry
	this->updateEvents();
	this->updateInput();
	this->player->update();
	this->updateShooting();
	this->updateDrones();
	this->updateCombat();
	this->updateBuildings();
	this->updateInterface();

}


void GameEngine::updateEvents()
{ //polluje eventy
	sf::Event event;

	this->Bordercollision();

	while (this->window->pollEvent(event))
	{
		if (event.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			this->window->close();
		}
	}
}

void GameEngine::updateInput()
{
	//sterowanie samolotem i strzelanie
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->player->move(0.f, 1.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->player->Attack())
	{
		this->player->isShooting(true);
		this->bullets.push_back(new Shoot(this->textrs["bullet"], this->player->getPos().x + this->player->getBounds().width, this->player->getPos().y + this->player->getBounds().height - 30, 1.f, 0.f, 10.f));
		//std::cout << "strzelam \n";
	}
}


void GameEngine::updateShooting()
{
	int counter = 0;
	for (auto* Shoot : this->bullets)
	{
		Shoot->update();

		if (Shoot->getBounds().left + Shoot->getBounds().width > this->window->getSize().x)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			//std::cout << this->bullets.size() << "\n";
		}
		counter++;
	}

}

void GameEngine::updateBuildings()
{
	this->bspawn += 1.f;
	if (this->bspawn >= this->bspawnmax)
	{
		this->buildings.push_back(new Building(1080.f,500.f));
		this->bspawn = 0.f;
	}

	for (auto* building : this->buildings)
	{
		building->update();
	}

	//int counter = 0;

}

void GameEngine::updateDrones()
{
	this->tspawn += 1.f;
	if (this->tspawn >= this->tspawnmax)
	{
		this->drones.push_back(new Opp(1080, rand() % 400));
		this->tspawn = 0.f;
	}

	int counter = 0;
	for (auto* drone : this->drones)
	{
		drone->update();

		if (drone->getBounds().left + drone->getBounds().width < 0.f)
		{
			delete this->drones.at(counter);
			this->drones.erase(this->drones.begin() + counter);
			--counter;

			//std::cout << this->bullets.size() << "\n";
		}

		else if (drone->getBounds().intersects(this->player->getBounds()))
		{
			int dmg = this->drones.at(counter)->getdmg();
			int pts = this->drones.at(counter)->getPoints();
			this->player->loseHp(dmg);
			this->score -= pts;
			delete this->drones.at(counter);
			this->drones.erase(this->drones.begin() + counter);
		}
		counter++;
	}



}

void GameEngine::updateCombat()
{
	for (int i = 0; i < this->drones.size(); ++i)
	{
		bool droneshot = false;
		for (size_t j = 0; j < this->bullets.size() && droneshot == false; j++)
		{
			if (this->drones[i]->getBounds().intersects(this->bullets[j]->getBounds()))
			{
				this->score += this->drones[i]->getPoints();

				delete this->drones[i];
				this->drones.erase(this->drones.begin() + i);

				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);

				droneshot = true;
			}
		}
	}
}

void GameEngine::updateInterface()
{
	//aktualizowanie hp i wyniku
	std::stringstream s;
	s << "Wynik: " << this->score;
	this->Pointstxt.setString(s.str());

	float percentage = static_cast<float>(this->player->getHp()) / this->player->getMaxhp();
	this->hpbar.setSize(sf::Vector2f(200 * percentage, this->hpbar.getSize().y));
}





//wyswietlanie poszczegolnych elementow gry
void GameEngine::render()
{
	this->window->clear();

	this->renderBackground();

	this->player->render(*this->window);

	for (auto* Shoot : this->bullets)
	{
		Shoot->render(this->window);
	}

	for (auto* drone : this->drones)
	{
		drone->render(this->window);
	}

	for (auto* building : this->buildings)
	{
		building->render(this->window);
	}

	this->renderInterface();

	this->window->display();

}


//rysowanie tla
void GameEngine::renderBackground()
{
	this->window->draw(this->background);
}

void GameEngine::renderInterface()
{
	this->window->draw(this->Pointstxt);
	this->window->draw(this->hpbarstat);
	this->window->draw(this->hpbar);
}

//zderzenia z granica okna gry
void GameEngine::Bordercollision()
{
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPos(0.f, this->player->getBounds().top);
	}
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPos(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPos(this->player->getBounds().left, 0.f);
	}
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPos(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}

}