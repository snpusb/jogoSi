#pragma once
#include "Moeda.h"
#include "Lista.h"
class ListaMoeda: public Lista<Moeda>
{
public:
	ListaMoeda();
	~ListaMoeda();
	void update(float deltatime);
	void draw(sf::RenderWindow& window);
};

