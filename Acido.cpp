#include "Acido.h"

void Acido::update(float deltaTime)
{
}

Acido::Acido(sf::Texture* tex, sf::Vector2f tam, sf::Vector2f pos):
	Obstaculo(tex,tam,pos)
{	
	dano = 7;
	id = 1;
}

Acido::~Acido()
{
}


