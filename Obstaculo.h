#pragma once
#include <SFML/Graphics.hpp>
#include "Entidade.h"
class Obstaculo:public Entidade
{
public:
	Obstaculo(sf::Texture* tex, sf::Vector2f tam, sf::Vector2f pos,bool eSerra=false);
	virtual ~Obstaculo();
	AreaDeColisao getColisor() const;
	const int getDano () const;
	virtual void update(float deltaTime) = 0;
	void setDano(const int dan);
	const bool getSerra() const;
	int getId()const;
protected:
	bool eSerra;
	int dano;
	int id;
};

