#pragma once
#include"Lista.h"
#include "Guerreiro.h"
class ListaGuerreiro:public Lista<Guerreiro>
{
public:
	ListaGuerreiro();
	~ListaGuerreiro();
	void update(float deltatime);
	void draw(sf::RenderWindow& window);
};

