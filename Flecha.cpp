#include "Flecha.h"

Flecha::Flecha(sf::Vector2f speed, bool direcao, sf::Texture* tex, sf::Vector2f pos, sf::Vector2f tam):
	Entidade(tex,pos,tam),direcao (direcao), animation(tex,sf::Vector2u(1,1), 0.0f)
{
	if (!direcao)
	{
		speedf.x = (-1)*speed.x;
	}
	else
	{
		speedf.x = speed.x;
	}
	dano = 2;
	speedf.y = (-1)*speed.y;
}

Flecha::~Flecha()
{
}

void Flecha::update(float deltaTime)
{
	velocidade.x += speedf.x;
	velocidade.y += speedf.y;
	animation.update(0, deltaTime, direcao);
	body.setTextureRect(animation.uvRect);
	body.move(velocidade * deltaTime);
	velocidade.x = 0.0f;
	velocidade.y = 0.0f;
}
