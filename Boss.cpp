#include "Boss.h"
#include <math.h>

Boss::Boss(int dano, bool pos_ataque, int vi, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f size):
	Inimigo(dano,pos_ataque,vi,texture,imageCount,switchTime,speed,position,size)
{
	tempo_ataque1 = 0.0f;
	tempo_ataque2 = 0.0f;
	tempo_voando = 0.0f;
	tempo_entre_voo = 0.0f;
	tamanho_flechas = 7;
	velocidade_projetil = 100.0f;
	velocidade = sf::Vector2f(0.0f,0.0f);
	voando = false;
	vivo = true;
	this->vidas = vi;
	this->speed = speed;
	speedx = speed;
	speedy = speed;
	flecha.loadFromFile("imagens/arrow2.png");
	magia.loadFromFile("imagens/1_boll.png");
}

Boss::~Boss()
{
	listaProjetil.clear();
}

void Boss::update(float deltaTime)
{
	deltatime = deltaTime;
	difPosPlayer = getPosition() - posPlayer;
	setDirecao();
	if (voando)
	{
		if (tempo_voando >= 3.0f)
		{
			voando = false;
			tempo_voando = 0.0f;
		}
		else
			tempo_voando += deltaTime;
	}
	else 
	{
		if (tempo_entre_voo >= 6.0f)
		{
			voando = true;
			tempo_entre_voo = 0.0f;
		}
		else
		tempo_entre_voo += deltaTime;
	}
	tempo_ataque1 += deltaTime;
	tempo_ataque2 += deltaTime;
	setAngulo();
	mover();
	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocidade*deltaTime);
}

void Boss::mover()
{	
	if (tempo_ataque1 >= 2.5f)
	{
		Flecha* bola = new Flecha(sf::Vector2f(abs(velocidade_projetil*cosf(teta)),velocidade_projetil*sinf(teta)),
			faceRight,&magia,getPosition(),sf::Vector2f(20.0f,20.0f));
		listaProjetil.push_back(bola);
		tempo_ataque1 = 0.0f;
	}
	if ( vidas < 7 && vidas >= 5)
	{
		criaFlechas();
	}
	else if (vidas < 5 && vidas >= 2)
	{
		criaFlechas();
		if (voando)
		{
			velocidade.x += speedx*deltatime;
			if (abs(difPosPlayer.y) >= 200.0f)
			{
				velocidade.y = 0.0f;
			}
			else
			{
				velocidade.y = 0.0f;
				velocidade.y -= speedy;
			}
		}
		else
		{
			velocidade.y += gravidade*deltatime;
			velocidade.x = 0.0f;
		}
	}
	else if(vidas< 2)
	{
		criaFlechas();
		velocidade = sf::Vector2f(0.0f, 0.0f);
		if (speedx > 0) 
		{
			velocidade.x += rand() % (int)speedx + speedx / 2.0f;
			if (speedy > 0)
			{
				velocidade.y += rand() % (int)speedy + speedy / 2.0f;
			}
			else
			{
				velocidade.y -= rand() % (int)speedy - speedy / 2.0f;
			}
		}
		else
		{
			velocidade.x -= rand() % (int)speedx - speedx / 2.0f;
			if (speedy > 0)
			{
				velocidade.y += rand() % (int)speedy + speedy / 2.0f;
			}
			else
			{
				velocidade.y -= rand() % (int)speedy - speedy / 2.0f;
			}
		}
	}

}

void Boss::setDirecao()
{

		if (difPosPlayer.x > 0.0f)
		{
			faceRight = false;
		}
		else
		{
			faceRight = true;
		}
}

void Boss::setPosPlayer(sf::Vector2f posP)
{
	posPlayer = posP;
}

void Boss::setAngulo()
{
	teta = atan2f(difPosPlayer.y, difPosPlayer.x);
}

std::vector<Flecha*> Boss::getListaProjetil()
{
	return listaProjetil;
}

void Boss::emColisao(sf::Vector2f& direcao)
{
	if (direcao.y != 0.0f)
	{
		speedy *= (-1);
		velocidade.y = 0.0f;
	}
	if (direcao.x != 0.0f)
	{
		speedx *= (-1);
		velocidade.x = 0.0f;
	}
}

void Boss::apagaProjetil(unsigned int i)
{
	if (i < listaProjetil.size())
	{
		delete listaProjetil[i];
		listaProjetil.erase(listaProjetil.begin() + i);
	}
}

void Boss::criaFlechas()
{
	if (tempo_ataque2 >= 6.0f)
	{
		float posx = posPlayer.x,
			posy = posPlayer.y - 250.0f;
		for (int i = 0; i < tamanho_flechas; i++)
		{
			Flecha* flechas = new Flecha(sf::Vector2f(0.0f, -200.0f), faceRight,
				&flecha, sf::Vector2f(posx, posy), sf::Vector2f(6.0f, 30.0f));
			listaProjetil.push_back(flechas);
			posx += 10.0f;
		}
		tempo_ataque2 = 0.0f;
	}
}

void Boss::sofrerDano(int dano)
{
	vidas -= dano;
	if (vidas <= 0)
		vivo = false;
}

const bool Boss::getVivo() const 
{
	return vivo;
}