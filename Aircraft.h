#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


class Aircraft
{
public:
	Aircraft();

	void render(sf::RenderTarget& target);

	void move(const float dx, const float dy);

	const sf::FloatRect getBounds() const;

	void setPos(const float x, const float y);

	const sf::Vector2f& getPos() const;

	void isShooting(bool shooting);

	bool Attack();

	void update();

	void updateCooldown();

	void variablesInit();

	const int& getHp() const;
	const int& getMaxhp() const;
	void setHp(const int newhp);
	void loseHp(const int dmg);

private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect currentframe;
	bool isDead;
	bool shooting;
	float velocity;
	float cooldown;
	float cooldownMax;
	int hp;
	int maxhp;

	void Spriteinit();
	void Textureinit();
	
};

