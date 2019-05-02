#include "Guerreiro.h"

Guerreiro::Guerreiro(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f size):
	Inimigo(1, false, 1, texture, imageCount, switchTime, speed, position, size)
{
	this->speed = speed;
	row = 0;
	deuDano = false;
}

Guerreiro::~Guerreiro()
{
}

void Guerreiro::update(float deltatime)
{
	velocidade.x = 0.0f;
	mover();
	animation.update(row, deltatime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocidade*deltatime);
}

void Guerreiro::emColisao(sf::Vector2f direçao)
{
	if (direçao.x < 0.0f) 
	{
		velocidade.x = 0.0f;
		speed *= (-1);
	}
	else if (direçao.x > 0.0f)
	{
		velocidade.x = 0.0f;
		speed *= (-1);
	}
	velocidade.y = 0.0f;
}

void Guerreiro::setDeuDano(bool dano)
{
	deuDano = dano;
}

bool Guerreiro::getDeuDano()
{
	return deuDano;
}

void Guerreiro::mover()
{
	velocidade.x += speed;

	if (velocidade.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (velocidade.x > 0.0f)
		{
			faceRight = true;
		}
		else
		{
			faceRight = false;
		}
	}
}
