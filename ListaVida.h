#pragma once
#include "Lista.h"
#include "Vida.h"

class ListaVida : public Lista<Vida>
{
public:
	ListaVida();
	~ListaVida();
	void update(float deltatime);
	void draw(sf::RenderWindow& window);
};

