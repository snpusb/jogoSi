#include "Player.h"
#include <math.h>
#include "Fase.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float alturaP, sf::Vector2f position, sf::Vector2f size, int nb) :
	Personagem(1, texture, imageCount, switchTime, speed, position, size, true)
{
	this->speed = speed;
	pontos = 0;
	row = 0;
	faceRight = true;
	alturaPulo = alturaP;
	vidas = 7;
	atacando = false;
	deltaTimeIn = -1;
	numberPlayer = nb;
	fase = NULL;
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	velocidade.x *= 0.5f;
	mover();
	velocidade.y += gravidade * deltaTime;
	tempo_ataque += deltaTime;
	if (numberPlayer == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			row = 0;
			atacando = true;
			velocidade.x = velocidade.x / 10.0f;
			colisor.setHalfSize(sf::Vector2f(body.getSize().x / 3.0f, body.getSize().y / 2.0f));
			deltaTimeIn = 0.05f;
		}
		else
		{
			deltaTimeIn = -1;
			colisor.setHalfSize(sf::Vector2f(-1, -1));
			atacando = false;
			if (velocidade.x == 0.0f)
			{
				row = 2;
			}
			else if (0 == vidas)
			{
				row = 5;
			}
			else
			{
				row = 3;
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
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			row = 0;
			atacando = true;
			velocidade.x = velocidade.x / 10;
			colisor.setHalfSize(sf::Vector2f(body.getSize().x / 3.0f, body.getSize().y / 2.0f));
			deltaTimeIn = 0.05f;
		}
		else
		{
			deltaTimeIn = -1;
			colisor.setHalfSize(sf::Vector2f(-1, -1));
			atacando = false;
			if (velocidade.x == 0.0f)
			{
				row = 2;
			}
			else if (0 == vidas)
			{
				row = 5;
			}
			else
			{
				row = 3;
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
	}
	if (deltaTimeIn > 0)
	{
		animation.update(row, deltaTimeIn, faceRight);
	}
	else
	{
		animation.update(row, deltaTime, faceRight);
	}
	body.setTextureRect(animation.uvRect);
	body.move(velocidade*deltaTime);
}

void Player::emColisao(sf::Vector2f& direcao)
{
	if (direcao.y < 0.0f)
	{
		velocidade.y = 0.0f;
		alturaPulo = 210.0f;
		podePular = true;
	}
	else if (direcao.y > 0.0f)
	{
		velocidade.y = 0.0f;
	}
	if (direcao.x != 0.0f)
	{
		velocidade.x = 0.0f;
		alturaPulo = 40.0f;
		velocidade.y = sqrt(2.0f*gravidade*alturaPulo) / 10;
		podePular = true;
		//arrumar isso 
	}
}

void Player::mover()
{
	velocidade.x *= 0.5f;
	if (numberPlayer == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocidade.x -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocidade.x += speed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && podePular)
		{
			velocidade.y = -sqrt(2.0f*gravidade*alturaPulo);
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			velocidade.x -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			velocidade.x += speed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && podePular)
		{
			velocidade.y = -sqrt(2.0f*gravidade*alturaPulo);
		}
	}
	podePular = false;
}

void Player::addPontos(const int po)
{
	pontos += po;
}

void Player::addVidas(const int qtd)
{
	vidas += qtd;
	if (vidas > 7)
	{
		vidas = 7;
	}
}

const int Player::getPontos() const
{
	return pontos;
}

void Player::setPular(const bool pul)
{
	podePular = pul;
}

void Player::sofrerDano(const int dano)
{
	
	vidas -= dano;
	if (vidas < 0)
	{
		vidas = 0;
	}
}

bool Player::atacandoAgora()
{
	if (tempo_ataque >= 0.2f)
	{
		tempo_ataque = 0.0f;
		return atacando;
	}
	return false;
}

void Player::setFase(Fase * faseAtual)
{
	fase = faseAtual;
}

void Player::setPontos(const int pont)
{
	pontos = pont;
}
