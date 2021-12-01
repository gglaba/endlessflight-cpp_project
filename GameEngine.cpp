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
	if (!this->font.loadFromFile("textures/font.ttf"))
	{
		std::cout << " nie wczytano czcionki";
	}
	this->Pointstxt.setFont(this->font);
	this->Pointstxt.setCharacterSize(20);
	this->Pointstxt.setFillColor(sf::Color(0,255,0));
	this->Pointstxt.setPosition(400, 0);
	//this->Pointstxt.setString("test");

	this->hpbar.setSize(sf::Vector2f(200.f, 10.f));
	this->hpbar.setFillColor(sf::Color(255,51,102));
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
	this -> background.setTexture(this->backgroundTexture);

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




//sondowanie eventow
void GameEngine::update()
{
	//aktualizowanie poszczegolnych elementow gry
	this->updateEvents();
	this->updateInput();
	this->player->update();
	this->updateShooting();
	this->updateDrones();
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

		if (Shoot->getBounds().left + Shoot->getBounds().width > this->window->getSize().x) // usuwam pociski ktore wyjda za szerokosc okienka
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			//std::cout << this->bullets.size() << "\n";
		}
		counter++;
	}

}

void GameEngine::updateDrones() //ktorys z warunkow wyrzuca blad - do poprawy
{
	this->tspawn += 1.f;
	if (this->tspawn >= this->tspawnmax)
	{
		this->drones.push_back(new Opp(1080, rand() % 400)); //tworze nowe drony na podanych wspolrzednych
		this->tspawn = 0.f;
	}

	for (int i = 0; i < this->drones.size(); ++i)
	{
		bool droneshot = false;
		this->drones[i]->update();

		for (size_t j = 0; j < this->bullets.size() && droneshot == false; j++)
		{
			if (this->bullets[j]->getBounds().intersects(this->drones[i]->getBounds())) // niszczenie dronow po ich zetknieciu z pociskiem samolotu
			{
				this->score += this->drones[i]->getPoints();

				this->bullets.erase(this->bullets.begin() + j);
				this->drones.erase(this->drones.begin() + i);

				droneshot = true;


			}
		}

		if (droneshot == false)
		{
			if (this->drones[i]->getBounds().left <= 0) //warunek usuwania dronow gdy wyjda za okno
			{
				this->drones.erase(this->drones.begin() + i);
				std::cout << this->drones.size();
				droneshot = true;
			}
		}

		if (this->drones[i]->getBounds().intersects(this->player->getBounds())) // zderzenie drona z graczem
		{
			this->player->loseHp(this->drones[i]->getdmg());
			delete this->drones.at(i);
			this->drones.erase(this->drones.begin() + i);
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

	for (auto *Shoot : this->bullets)
	{
		Shoot->render(this->window);
	}

	for (auto* drone : this->drones)
	{
		drone->render(this->window);
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
		this->player->setPos(this->player->getBounds().left,0.f);
	}
	else if (this->player->getBounds().top+this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPos(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}

}

