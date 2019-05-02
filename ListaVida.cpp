#include "ListaVida.h"

ListaVida::ListaVida()
{
}

ListaVida::~ListaVida()
{
}

void ListaVida::update(float deltatime)
{
	Elemento<Vida> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->update(deltatime);
		paux = paux->getProx();
	}
}

void ListaVida::draw(sf::RenderWindow & window)
{
	Elemento<Vida> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->draw(window);
		paux = paux->getProx();
	}
}
