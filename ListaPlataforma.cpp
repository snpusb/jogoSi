#include "ListaPlataforma.h"

ListaPlataforma::ListaPlataforma()
{
}

ListaPlataforma::~ListaPlataforma()
{
}

void ListaPlataforma::draw(sf::RenderWindow& window)
{
	Elemento<Plataforma> *paux;
	paux = pPrim;
	while (paux != NULL)
	{
		paux->getInfo()->draw(window);
		paux = paux->getProx();
	}
}
