#include "ListaAtirador.h"

ListaAtirador::ListaAtirador()
{
}

ListaAtirador::~ListaAtirador()
{
}

void ListaAtirador::update(float deltatime,sf::Vector2f posPlayer)
{
	Elemento<Atirador> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->setPosPlayer(posPlayer);
		paux->getInfo()->update(deltatime);
		paux = paux->getProx();
	}
}

void ListaAtirador::draw(sf::RenderWindow & window)
{
	Elemento<Atirador> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->draw(window);
		paux = paux->getProx();
	}
}
