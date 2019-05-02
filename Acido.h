#pragma once
#include "Obstaculo.h"

class Acido: public Obstaculo
{
public:
	void update(float deltaTime);
	Acido(sf::Texture* tex, sf::Vector2f tam, sf::Vector2f pos);
	~Acido();
};

