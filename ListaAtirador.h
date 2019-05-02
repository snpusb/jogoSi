#pragma once
#include "Lista.h"
#include "Atirador.h"
class ListaAtirador:public Lista<Atirador>
{
public:
	ListaAtirador();
	~ListaAtirador();
	void update(float deltatime, sf::Vector2f posPlayer);
	void draw(sf::RenderWindow& window);
};

