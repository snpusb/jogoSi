#include "Vida.h"

Vida::Vida(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f size, int qtd):
	Bonus(texture, imageCount, switchTime, position, size) 
{
	qtdVidas = qtd;
}

int Vida::getQtdVida()
{
	return qtdVidas;
}

Vida::~Vida()
{
}
