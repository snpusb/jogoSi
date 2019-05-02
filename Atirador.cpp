#include "Atirador.h"

Atirador::Atirador( sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f size):
	Inimigo(2,false,1,texture,imageCount,switchTime,speed,position,size)
{
	this->speed = speed;
	row = 0;
	flecha.loadFromFile("imagens/arrow.png");
	tempo_ataque = 1;
}

Atirador::~Atirador()
{
}

void Atirador::update(float deltaTime)
{
	difPosPlayer = getPosition() - posPlayer;
	setDirecao();
	if (tempo_ataque >= 2.0f && (abs(difPosPlayer.x) < 550.0f&&abs(difPosPlayer.y < 100.0f)))
	{
		mover();
		row = 0;
		tempo_ataque = 0;
	}

	else if (tempo_ataque >= 2.0f)
	{
		tempo_ataque = 2.0f;
		row = 0;
	}
	else
	{
		tempo_ataque += deltaTime;
		row = 1;
		if (tempo_ataque > 1.75)
		{
			row = 0;
		}
	}
	for (unsigned int i = 0; i < lflechas.size(); i++)
		lflechas[i]->update(deltaTime);
	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Atirador::mover()
{
	Flecha* flech = new Flecha(sf::Vector2f(speed,0.0f), direcao, &flecha, getPosition(), sf::Vector2f(50.0f, 6.0f));
	lflechas.push_back(flech);
}

void Atirador::setDirecao()
{
	if (difPosPlayer.x > 0.0f)
	{
		direcao = false;
		faceRight = false;
	}
	else
	{
		direcao = true;
		faceRight = true;
	}
}

void Atirador::setPosPlayer(sf::Vector2f pos)
{
	posPlayer = pos;
}

std::vector<Flecha*> Atirador::getListaFlechas()
{
	return lflechas;
}

void Atirador::apagaFlecha(unsigned int i)
{
	if (i < lflechas.size())
	{
		delete lflechas[i];
		lflechas.erase(lflechas.begin() + i);
	}
}
