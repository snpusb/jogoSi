#pragma once
#include <iostream>
#include "Elemento.h"
#include "SFML/Graphics.hpp"
template<class T>
class Lista
{
protected:
	Elemento<T> *pPrim, *pAtual;
public:

	Lista() { pPrim = NULL;
			  pAtual = NULL;
	};
	~Lista() {
		Elemento<T>* paux = NULL;
		paux = pPrim;
		while (paux != NULL)
		{
			paux = pPrim->getProx();
			delete(pPrim);
			pPrim = paux;
		}
	};
	void operator-=(T* pt) 
	{
		Elemento<T>* paux;
		paux = pPrim;
		if (paux->getInfo() == pt)
		{
			if (paux->getProx() == NULL)
			{
				delete(paux);
				pPrim = NULL;
				pAtual = NULL;
			}
			else
			{
				pPrim = paux->getProx();
				pPrim->setAnte(NULL);
				delete(paux);
			}
		}
		else
		{
			while (pt != paux->getInfo())
			{
				paux = paux->getProx();
			}
			if (paux->getProx() == NULL)
			{
				paux->getAnte()->setProx(NULL);
				delete(paux);
			}
			else
			{
				paux->getAnte()->setProx(paux->getProx());
				paux->getProx()->setAnte(paux->getAnte());
				delete(paux);
			}
		}
		paux = NULL;
	}
	void operator+=(T* pt)
	{
		Elemento<T>* paux = NULL;
		paux = new Elemento<T>();
		paux->setInfo(pt);
		if (pPrim == NULL)
		{
			pPrim = paux;
			pAtual = paux;
		}
		else
		{
			pAtual->setProx(paux);
			paux->setAnte(pAtual);
			pAtual = paux;
		}
	}
	Elemento<T>* getPrimeiroElemento() const { return pPrim; };
};
