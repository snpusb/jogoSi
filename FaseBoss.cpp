#include "FaseBoss.h"

FaseBoss::FaseBoss(sf::View* vie, string caminhoMapa, Player* jog, Player* jog2):
	Fase(vie,caminhoMapa,3,false,jog,jog2)
{
	bosTex.loadFromFile("imagens/boss.png");
	boss = new Boss(1, false, 10, &bosTex, sf::Vector2u(3, 4), 0.2f, 100.0f, sf::Vector2f(500.0f, 500.0f), sf::Vector2f(100.0f, 100.0f));
	vidas.loadFromFile("imagens/lifes2.png");
	bg1.loadFromFile("imagens/bgBoss.png");
	background.setSize(sf::Vector2f(2000, 1500));
	background.setPosition(sf::Vector2f(-300, -300));
	background.setTexture(&bg1);
	lifesBoss.setSize(sf::Vector2f(300.0f, 30.0f));
	lifesBoss.setTexture(&vidas);
	rectLifesBoss.width = vidas.getSize().x;
	rectLifesBoss.height = vidas.getSize().y / 10;
	rectLifesBoss.left = 0;
}

FaseBoss::~FaseBoss()
{
	delete(boss);
	boss = NULL;
}

void FaseBoss::update(float deltatime)
{
	
		boss->setPosPlayer(jogador->getPosition());
		boss->update(deltatime);
		jogador->update(deltatime);
		for (unsigned int i = 0; i < boss->getListaProjetil().size(); i++)
		{
			boss->getListaProjetil()[i]->update(deltatime);
		}
		if (jogador2 != NULL)
		{
			jogador2->update(deltatime);
		}
		lifes.setPosition(jogador->getPosition().x - view->getSize().x / 2, jogador->getPosition().y - view->getSize().y / 2);
		rectLifes.top = (7 - jogador->getVidas()) * rectLifes.height;
		lifes.setTextureRect(rectLifes);
		pontosText.setString(std::to_string(jogador->getPontos()));
		pontosText.setPosition(jogador->getPosition().x, jogador->getPosition().y - view->getSize().y / 2);
		view->setCenter(jogador->getPosition());
		if (jogador2 != NULL)
		{
			lifes2.setPosition(jogador->getPosition().x - view->getSize().x / 2, jogador->getPosition().y - view->getSize().y / 2 + 50);
			rectLifes.top = (7 - jogador2->getVidas()) * rectLifes.height;
			lifes2.setTextureRect(rectLifes);
		}
		lifesBoss.setPosition(boss->getPosition().x - 100.0f, boss->getPosition().y - 150.0f);
		rectLifesBoss.top = (10 - boss->getVidas()) * rectLifesBoss.height;
		lifesBoss.setTextureRect(rectLifesBoss);
}

void FaseBoss::checarColisoes()
{
	sf::Vector2f direçao;
	AreaDeColisao *play = &jogador->getColisor();
	AreaDeColisao *play2 = NULL;
	if (jogador2 != NULL)
	{
		play2 = &jogador2->getColisor();
	}
	bool pegB = false;
	//Pega a lista e adiciona em um vetor, para facilitar a verificação
	Elemento<Plataforma> *pauxPlataforma = listaPlataforma.getPrimeiroElemento();

		AreaDeColisao* bossC = &boss->getColisor();
		AreaDeColisao *projetil;
		for (unsigned int i = 0; i < boss->getListaProjetil().size(); i++)
		{
			projetil = &boss->getListaProjetil()[i]->getColisor();
			if (projetil->checkColisao(*play, direçao, 0.0f))
			{
				jogador->sofrerDano(boss->getListaProjetil()[i]->getDano());
				musicDamage.play();
				boss->apagaProjetil(i);
				pegB = true;
			}

			if (jogador2 != NULL && !pegB)
			{
				if (projetil->checkColisao(*play2, direçao, 0.0f))
				{
					jogador2->sofrerDano(boss->getListaProjetil()[i]->getDano());
					musicDamage.play();
					boss->apagaProjetil(i);
				}
			}
			//Verifica a colisão das flechas com as plataformas

			while (pauxPlataforma != NULL)
			{
				AreaDeColisao platafor = pauxPlataforma->getInfo()->getColisor();
				if (platafor.checkColisao(*projetil, direçao, 1.0f))
				{
					boss->apagaProjetil(i);
				}
				pauxPlataforma = pauxPlataforma->getProx();
			}
			pauxPlataforma = listaPlataforma.getPrimeiroElemento();
		}

		if (boss->getColisor().checkColisao(*play, direçao, 0.0f))
		{
			jogador->emColisao(direçao);
			if (jogador->atacandoAgora())
			{
				boss->sofrerDano(1);
				pegB = true;
			}
		}

		if (jogador2 != NULL && !pegB)
		{
			if (boss->getColisor().checkColisao(*play2, direçao, 0.0f))
			{
				jogador2->emColisao(direçao);
				if (jogador2->atacandoAgora())
				{
					boss->sofrerDano(1);
				}
			}
		}
		while (pauxPlataforma != NULL)
		{
			AreaDeColisao* bossC = &boss->getColisor();
			AreaDeColisao platafor = pauxPlataforma->getInfo()->getColisor();
			if (platafor.checkColisao(*bossC, direçao, 1.0f))
			{
				boss->emColisao(direçao);
			}
			pauxPlataforma = pauxPlataforma->getProx();
		}
		pauxPlataforma = listaPlataforma.getPrimeiroElemento();
		while (pauxPlataforma != NULL)
		{
			if (pauxPlataforma->getInfo()->getColisor().checkColisao(*play, direçao, 1.0f))
			{
				jogador->emColisao(direçao);
			}
			if (jogador2 != NULL)
			{
				if (pauxPlataforma->getInfo()->getColisor().checkColisao(*play2, direçao, 1.0f))
				{
					jogador2->emColisao(direçao);
				}
			}
			pauxPlataforma = pauxPlataforma->getProx();
		}
}

void FaseBoss::draw(sf::RenderWindow & window)
{
	window.setView(*view);
	window.clear();
	window.draw(background);
	boss->draw(window);
	for (unsigned int i = 0; i < boss->getListaProjetil().size(); i++)
	{
		boss->getListaProjetil()[i]->draw(window);
	}
	listaPlataforma.draw(window);
	jogador->draw(window);
	if (jogador2 != NULL)
	{
		jogador2->draw(window);
		window.draw(lifes2);
	}
	window.draw(pontosText);
	window.draw(lifes);
	window.draw(lifesBoss);
	window.display();
}

bool FaseBoss::proximaFase()
{
	return !boss->getVivo();
}

void FaseBoss::faseFinalizada(sf::RenderWindow & window)
{
	window.clear();
	pontosText.setString("VOCE GANHOU! \nSeus pontos: " + std::to_string(jogador->getPontos()));
	pontosText.setPosition(jogador->getPosition().x, jogador->getPosition().y);
	window.draw(pontosText);
	window.display();
}
