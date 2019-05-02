#pragma once
#include "Bonus.h"

class Moeda : public Bonus
{
public:
	Moeda(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f size, int val);
	~Moeda();
	int getValor();
private:
	int valor;
};

