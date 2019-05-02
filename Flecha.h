#pragma once
#include <SFML/Graphics.hpp>
#include "Entidade.h"
#include "Animador.h"
class Flecha:public Entidade
{
private:
	
	bool direcao;
	int dano;
	Animador animation;
	sf::Vector2f velocidade, speedf;
public:
	Flecha(sf::Vector2f speed,bool direcao,sf::Texture* tex,sf::Vector2f pos,sf::Vector2f tam);
	~Flecha();
	void update(float deltaTime);
	const int getDano() const { return dano; };
};

