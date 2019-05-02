#pragma once
#include "Personagem.h"

class Inimigo: public Personagem
{
protected:
	bool pos_ataque;
	int dano;
public:
	Inimigo(int dano, bool pos_ataque, int vi, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f size);
	virtual ~Inimigo();
	virtual void update(float deltaTime) = 0;
	virtual void mover() = 0;
};

