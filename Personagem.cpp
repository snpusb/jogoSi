#include "Personagem.h"

Personagem::Personagem(int vi, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f size, bool principal):
	Entidade(texture, position, size, principal),animation(texture,imageCount,switchTime)
{
	vidas = vi;
}

Personagem::~Personagem()
{
}

void Personagem::mover()
{
}

void Personagem::update(float deltatime)
{
}

void Personagem::setVida(int vi)
{
	vidas = vi;
}
const unsigned int Personagem::getVidas() const
{
	return vidas;
}
const float Personagem::getGravidade()
{
	return gravidade;
}
const float Personagem::gravidade = 979.0f;