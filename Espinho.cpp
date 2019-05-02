#include "Espinho.h"

void Espinho::update(float deltaTime)
{
}

Espinho::Espinho(sf::Texture* tex, sf::Vector2f tam, sf::Vector2f pos) :
	Obstaculo(tex, tam, pos)
{
	dano = 7;
	id = 2;
}

Espinho::~Espinho()
{
}
