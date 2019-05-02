#include "Serra.h"

Serra::Serra(sf::Texture* tex, sf::Vector2f tam, sf::Vector2f pos):
	Obstaculo(NULL,tam,pos,true)
{
	omega = 100.0f;
	tempo_ataque = 0.0f;
	bodyC.setTexture(tex);
	bodyC.setPosition(pos);
	bodyC.setOrigin(tam / 2.0f);
	bodyC.setRadius(tam.x/2.0f);
	id = 3;
}

Serra::~Serra()
{
}

void Serra::update(float deltaTime)
{
	if (tempo_ataque >= 1.0f)
	{
		dano = 1;
		tempo_ataque = 0.0f;
	}
	else
	{
		tempo_ataque += deltaTime;
	}
	if (omega >= 360.0f)
	{
		omega = 0.0f;
	}
	else
	{
		omega += 300.0f*deltaTime;
	}
	bodyC.setRotation(omega);
}

void Serra::draw(sf::RenderWindow & window)
{
	window.draw(bodyC);
}
