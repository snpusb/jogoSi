#pragma once
#include <SFML/Graphics.hpp>
#include "Entidade.h"

class Bonus: public Entidade
{
private:
	Animador animation;
	unsigned int row;

public:
	Bonus(sf::Texture* texture, sf::Vector2u imageCount,  float switchTime, sf::Vector2f position, sf::Vector2f size);
	~Bonus();
	void update(float deltaTime);

};

