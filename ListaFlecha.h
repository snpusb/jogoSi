#pragma once
#include "Lista.h"
#include "Flecha.h"
class ListaFlecha:public Lista<Flecha>
{
public:
	ListaFlecha();
	~ListaFlecha();
	void update(float deltatime);
	void draw(sf::RenderWindow& window);
};

