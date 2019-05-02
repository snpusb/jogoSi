#pragma once
#include "Inimigo.h"

class Guerreiro : public Inimigo
{
private:
	bool deuDano;
public:
	Guerreiro(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f size);
	~Guerreiro();
	void update(float deltatime);
	void mover();
	void emColisao(sf::Vector2f direçao);
	void setDeuDano(bool dano);
	bool getDeuDano();
};

