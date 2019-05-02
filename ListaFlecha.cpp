#include "ListaFlecha.h"

ListaFlecha::ListaFlecha()
{
}

ListaFlecha::~ListaFlecha()
{
}

void ListaFlecha::update(float deltatime)
{
	Elemento<Flecha> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->update(deltatime);
		paux = paux->getProx();
	}
}

void ListaFlecha::draw(sf::RenderWindow & window)
{
	Elemento<Flecha> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->draw(window);
		paux = paux->getProx();
	}
}
