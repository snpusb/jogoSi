#include "Moeda.h"

Moeda::Moeda(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f size, int val):
	Bonus(texture, imageCount, switchTime, position, size)
{
	valor = val;
}

Moeda::~Moeda()
{
}

int Moeda::getValor()
{
	return valor;
}
