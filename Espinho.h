#pragma once
#include"Obstaculo.h"

class Espinho: public Obstaculo
{

public:
	void update(float deltaTime);
	Espinho(sf::Texture* tex, sf::Vector2f tam, sf::Vector2f pos);
	~Espinho();
};

