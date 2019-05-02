#pragma once
#include"Lista.h"
#include "Obstaculo.h"
class ListaObstaculo : public Lista<Obstaculo>
{
public:
	ListaObstaculo();
	~ListaObstaculo();
	void update(float deltatime);
	void draw(sf::RenderWindow& window);
};

