#include "ListaMoeda.h"

ListaMoeda::ListaMoeda()
{
}

ListaMoeda::~ListaMoeda()
{
}

void ListaMoeda::update(float deltatime)
{
	Elemento<Moeda> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->update(deltatime);
		paux = paux->getProx();
	}
}

void ListaMoeda::draw(sf::RenderWindow & window)
{
	Elemento<Moeda> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->draw(window);
		paux = paux->getProx();
	}
}
