#include "GameEngine.h"
#include <iostream>


GameEngine::GameEngine()
{
	//inicjowanie poszczegolnych elementow gry
	this->windowInit();
	this->MenuInit();
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

	for (auto* i : this->buildings) //usuwanie budynkow
	{
		delete i;
	}
}

void GameEngine::run()
{
	//glowna petla gry
	while (this->window->isOpen())
	{
		this->updateEvents();

		if (this->player->getHp() > 0)
		{
			this->update();
		}
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

	//ustawiam style i kolory napisow w grze i napisow koncowych
	sf::Color color1(240, 44, 82);
	this->Pointstxt.setFont(this->font);
	this->Pointstxt.setCharacterSize(24);
	this->Pointstxt.setFillColor(color1);
	this->Pointstxt.setPosition(400, 0);
	this->Pointstxt.setStyle(sf::Text::Bold);
	this->Pointstxt.setOutlineThickness(2);
	//this->Pointstxt.setString("test");

	this->hpbar.setSize(sf::Vector2f(200.f, 10.f));
	this->hpbar.setFillColor(sf::Color(255,0,0));
	this->hpbar.setPosition(5.f, 5.f);
	this->hpbarstat = this->hpbar;
	this->hpbarstat.setFillColor(sf::Color(50, 50, 50, 100));

	this->Overtext.setFont(this->font);
	this->Overtext.setCharacterSize(92);
	this->Overtext.setFillColor(color1);
	this->Overtext.setPosition((this->window->getSize().x / 2) - 260, (this->window->getSize().y / 2) - 200);
	this->Overtext.setStyle(sf::Text::Bold);
	this->Overtext.setOutlineThickness(2);
	this->Overtext.setString("GAME OVER!");

	this->leaveinstr.setFont(this->font);
	this->leaveinstr.setCharacterSize(48);
	this->leaveinstr.setFillColor(color1);
	this->leaveinstr.setPosition(297, 583);
	this->leaveinstr.setStyle(sf::Text::Bold);
	this->leaveinstr.setOutlineThickness(1);
	this->leaveinstr.setString("Press Escape to exit");
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
	//inicjuje tekstury pociskow ( niestety zabrakło czasu na więcej, być może w przyszłości już dla siebie dodam)
	this->textrs["bullet"] = new sf::Texture();
	this->textrs["bullet"]->loadFromFile("textures/Bullet (1).png");
}

void GameEngine::DronesInit()
{
	//inicjowanie zmiennych spawnowania sie dronow
	this->tspawnmax = 25.f;
	this->tspawn = this->tspawnmax;
}

void GameEngine::BuidlingsInit()
{
	// ustawiam cooldown spawnowania budynkow
	this->bspawnmax = 80.f;
	this->bspawn = this->bspawnmax;

}

void GameEngine::MenuInit()
{
	sf::Color color(189, 117, 131);

	if (!this->font.loadFromFile("textures/font.otf"))
	{
		std::cout << " Nie mozna zaladowac czcionki menu \n ";
	}

	//ustawiam nizej style i kolor dla napisow w menu
	this->mtitle.setFont(this->font);
	this->mtitle.setCharacterSize(84);
	this->mtitle.setFillColor(color);
	//this->mtitle.setPosition(412, 100);
	this->mtitle.setPosition((this->window->getSize().x - mtitle.getGlobalBounds().width)/5 , (this->window->getSize().y - mtitle.getGlobalBounds().height)/12);
	this->mtitle.setStyle(sf::Text::Bold);
	this->mtitle.setOutlineThickness(2);
	this->mtitle.setString("ENDLESS FLIGHT");


	this->mexit.setFont(this->font);
	this->mexit.setCharacterSize(48);
	this->mexit.setFillColor(color);
	this->mexit.setPosition((this->window->getSize().x - mexit.getGlobalBounds().width) / 2.5f, (this->window->getSize().y - mexit.getGlobalBounds().height) - 450.f);
	this->mexit.setStyle(sf::Text::Bold);
	this->mexit.setOutlineThickness(1);
	this->mexit.setString("PLAY");


	this->mplay.setFont(this->font);
	this->mplay.setCharacterSize(48);
	this->mplay.setFillColor(color);
	this->mplay.setPosition((this->window->getSize().x - mplay.getGlobalBounds().width) / 2.5f, (this->window->getSize().y - mplay.getGlobalBounds().height) - 300.f);
	this->mplay.setStyle(sf::Text::Bold);
	this->mplay.setOutlineThickness(1);
	this->mplay.setString("EXIT");

	this->minstr.setFont(this->font);
	this->minstr.setCharacterSize(26);
	this->minstr.setFillColor(color);
	this->minstr.setPosition((this->window->getSize().x - minstr.getGlobalBounds().width)/8, (this->window->getSize().y - minstr.getGlobalBounds().height) - 80.f );
	this->minstr.setStyle(sf::Text::Bold);
	this->minstr.setOutlineThickness(1);
	this->minstr.setString("Press arrow keys to move, S key to shoot and P to pause the game");




}


//sondowanie eventow
void GameEngine::update()
{
	this->updateMenu();

	if (this->isPlayOn == true) // zmienia sie na true gdy klikniemy enter na play w menu, uruchamia gre
	{
		//aktualizowanie poszczegolnych elementow gry
		this->updateInput();
		this->player->update();
		this->updateShooting();
		this->updateDrones();
		this->updateCombat();
		this->updateBuildings();
		this->updateInterface();
	}


}


void GameEngine::updateEvents()
{ //polluje eventy
	sf::Event event;

	this->Bordercollision();
	//poruszanie sie po menu
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{

			case sf::Keyboard::Escape:
			{
				this->window->close();
			}
			case sf::Keyboard::Up:
			{
				if (!m_isPlaySelected)
				{
					m_isPlaySelected = true; // w zaleznosci od tych zmiennych zmienia sie kolor przyciskow
					m_isExitSelected = false;
				}
				break;
			}
			case sf::Keyboard::Down:
			{
				if (!m_isExitSelected)
				{
					
					m_isPlaySelected = false;
					m_isExitSelected = true;
				}
				break;
			}
			case sf::Keyboard::Return:
			{
				m_isPlayPressed = false;
				m_isExitPressed = false;

				if (m_isPlaySelected == true)
				{
					
					m_isPlayPressed = true; //po wcisnieciu enter w menu wlacza sie gra (przez boolean isplayon)
					this->isPlayOn = true;
				}
				else
				{
					if (this->isPlayOn == false) //wyjscie z gry po wcisnieciu enter na exit
					{
						m_isExitPressed = true;
						this->window->close();
					}

				}

				break;
			}
			case sf::Keyboard::P: // powrot do menu
			{
				this->isPlayOn = false;
			}

			default:
			{
				break;
			}
			}
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->player->Attack()) //strzelanie zalezne od cooldownu 
	{
		this->player->isShooting(true);
		this->bullets.push_back(new Shoot(this->textrs["bullet"], this->player->getPos().x + this->player->getBounds().width, this->player->getPos().y + this->player->getBounds().height - 30, 1.f, 0.f, 10.f)); //tworze nowe pociski
		//std::cout << "strzelam \n";
	}
}


void GameEngine::updateShooting()
{
	int counter = 0;
	for (auto* Shoot : this->bullets)
	{
		Shoot->update();
		//usuwanie pociskow ktore wyjda za ekran
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
	//w zaleznosci od cooldownu spawnu budynkow, generuje losowe budynki
	if (this->bspawn >= this->bspawnmax)
	{
		this->buildings.push_back(new Building(1080.f,300,rand() % 5 ));
		this->bspawn = 0.f;
	}

	int counter = 0;
	for (auto* building : this->buildings)
	{
		building->update();
		//usuwanie budynkow poza ekranem
		if (building->getBounds().left + building->getBounds().width < 0.f)
		{
			delete this->buildings.at(counter);
			this->buildings.erase(this->buildings.begin() + counter);
			--counter;
		}
		//zderzenie budynku z graczem, dmg budynku zalezny od jego szerokosci
		else if (building->getBounds().intersects(this->player->getBounds()))
		{
			int dmg = (building->getBounds().width)/4;
			this->player->loseHp(dmg);
			this->player->setPos(0, 0);
		}
		counter++;
	}
}

void GameEngine::updateDrones()
{
	this->tspawn += 1.f;
	if (this->tspawn >= this->tspawnmax) //spawn dronow zalezny od ich cooldownu
	{
		this->drones.push_back(new Opp(1080, rand() % 300));
		this->tspawn = 0.f;
	}

	int counter = 0;
	for (auto* drone : this->drones)
	{
		drone->update();
		//usuwanie dronow ktore wyjda poza ekran
		if (drone->getBounds().left + drone->getBounds().width < 0.f)
		{
			delete this->drones.at(counter);
			this->drones.erase(this->drones.begin() + counter);
			--counter;

			//std::cout << this->bullets.size() << "\n";
		}
		//kolizja przeciwnika z graczem, gracz ma odejmowane hp,punkty i usuwany jest dron
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
	//usuwanie przeciwnika i pocisku po ich zderzeniu oraz "leczenie" gracza o polowe punktow drona
	for (int i = 0; i < this->drones.size(); ++i)
	{
		bool droneshot = false;
		for (size_t j = 0; j < this->bullets.size() && droneshot == false; j++)
		{
			if (this->drones[i]->getBounds().intersects(this->bullets[j]->getBounds()))
			{
				this->player->setHp(this->player->getHp() + (this->drones[i]->getPoints())/2);

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
	if (this->isPlayOn == true)
	{
		this->score += 0.01; //dodawanie punktow za przebyta odleglosc
	}


	//aktualizowanie hp i wyniku
	std::stringstream s;
	s << "Score: " << static_cast<int>(this->score);
	this->Pointstxt.setString(s.str()); // wyswietlam wynik

	float percentage = static_cast<float>(this->player->getHp()) / this->player->getMaxhp(); // zmieniam aktualne hp z liczby na procent maksymalnego hp
	this->hpbar.setSize(sf::Vector2f(200 * percentage, this->hpbar.getSize().y)); // dlugosc hp bara zalezna od liczby przez ktora mnoze procentowe hp
}

void GameEngine::updateMenu()
{
	//warunki zmiany koloru przyciskow w zaleznosci czy sa aktualnie wybrane
	if (!m_isPlaySelected)
	{
		this->mplay.setFillColor(sf::Color::Black);
		this->mexit.setFillColor(sf::Color(189, 117, 131));
	}
	else if (!m_isExitSelected)
	{
		this->mexit.setFillColor(sf::Color::Black);
		this->mplay.setFillColor(sf::Color(189, 117, 131));
	}
}

void GameEngine::overscreen()
{
//procedura ekranu końcowego, czyszcze okno i rysuje wynik z instrukcja wyjscia z gry
	this->window->clear();
	this->renderBackground();
	this->window->draw(this->Overtext);
	this->Pointstxt.setPosition(352, 383);
	this->Pointstxt.setCharacterSize(72);
	this->window->draw(this->Pointstxt);
	this->window->draw(this->leaveinstr);
}





//wyswietlanie poszczegolnych elementow gry
void GameEngine::render()
{
	this->window->clear();
	
	//rysowanie tla menu i menu

	this->renderBackground();

	this->renderMenu();

	this->updateMenu();

	if (this->isPlayOn == true) //rysowanie ekranu na biezaco
	{
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

		if (this->player->getHp() <= 0) //wyswietlanie ekranu koncowego
		{
			this->overscreen();
		}
	}


	this->window->display();

}


//rysowanie tla
void GameEngine::renderBackground()
{
	if (this->player->getHp() <= 0) //wlaczenie przyciemnionego tla w ekranie koncowym
	{
		if (this->backgroundTexture.loadFromFile("textures/background_dead.png") == false)
		{
			std::cout << "nie załadaowano tekstury tła \n";
		}
	}

	this->window->draw(this->background);

}

void GameEngine::renderInterface() //rysowanie interfejsu
{
	this->window->draw(this->Pointstxt);
	this->window->draw(this->hpbarstat);
	this->window->draw(this->hpbar);
}

void GameEngine::renderMenu() //rysowanie menu
{
	this->window->draw(this->mtitle);
	this->window->draw(this->mexit);
	this->window->draw(this->mplay);
	this->window->draw(this->minstr);

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