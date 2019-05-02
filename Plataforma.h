#pragma once
#include "Entidade.h"

class Plataforma: public Entidade
{
public:
	Plataforma(sf::Texture* tex,sf::Vector2f tam, sf::Vector2f pos);
	~Plataforma();
};

