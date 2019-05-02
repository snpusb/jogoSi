#pragma once
#include "Lista.h"
#include "Plataforma.h"

class ListaPlataforma:public Lista<Plataforma>
{
public:
	ListaPlataforma();
	~ListaPlataforma();
	void draw(sf::RenderWindow& window);
};

