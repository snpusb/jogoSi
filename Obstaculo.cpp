#include "Obstaculo.h"

Obstaculo::Obstaculo(sf::Texture* tex, sf::Vector2f tam, sf::Vector2f pos,bool eSerra):
	eSerra(eSerra),Entidade(tex,pos,tam)
{
	if (eSerra)
	{
		body.setSize(tam / sqrt(2.0f));
	}
	else
	{
		body.setSize(tam);
	}
	body.setOrigin(tam / 2.0f);
}

Obstaculo::~Obstaculo()
{}

AreaDeColisao Obstaculo::getColisor() const
{
	return colisor;
}

const int Obstaculo::getDano() const
{
	return dano;
}

void Obstaculo::setDano(const int dan)
{
	dano = dan;
}

const bool Obstaculo::getSerra() const
{
	return eSerra;
}

int Obstaculo::getId() const
{
	return id;
}
