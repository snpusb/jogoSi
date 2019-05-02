#include "ListaObstaculo.h"

ListaObstaculo::ListaObstaculo()
{
}

ListaObstaculo::~ListaObstaculo()
{
}

void ListaObstaculo::update(float deltatime)
{
	Elemento<Obstaculo> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->update(deltatime);
		paux = paux->getProx();
	}
}

void ListaObstaculo::draw(sf::RenderWindow & window)
{
	Elemento<Obstaculo> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->draw(window);
		paux = paux->getProx();
	}
}
