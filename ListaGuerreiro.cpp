#include "ListaGuerreiro.h"

ListaGuerreiro::ListaGuerreiro()
{
}

ListaGuerreiro::~ListaGuerreiro()
{
}

void ListaGuerreiro::update(float deltatime)
{
	Elemento<Guerreiro> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->update(deltatime);
		paux = paux->getProx();
	}
}

void ListaGuerreiro::draw(sf::RenderWindow & window)
{
	Elemento<Guerreiro> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->draw(window);
		paux = paux->getProx();
	}
}
