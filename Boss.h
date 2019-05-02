#pragma once
#include "Inimigo.h"
#include <vector>
#include "Flecha.h"
#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>

class Boss:public Inimigo
{
private:
	float tempo_ataque1,tempo_ataque2,tempo_voando,tempo_entre_voo
			,teta,velocidade_projetil,deltatime;
	bool voando,vivo;
	int tamanho_flechas;
	std::vector<Flecha*> listaProjetil;
	sf::Texture flecha, magia;
	sf::Vector2f difPosPlayer,posPlayer;
	float speedy, speedx;
public:
	Boss(int dano, bool pos_ataque, int vi, sf::Texture* texture, sf::Vector2u imageCount,
		float switchTime, float speed, sf::Vector2f position, sf::Vector2f size);
	~Boss();
	void update(float deltaTime);
	void mover();
	void setDirecao();
	void setPosPlayer(sf::Vector2f posP);
	void setAngulo();
	std::vector<Flecha*> getListaProjetil();
	void emColisao(sf::Vector2f& direcao);
	void apagaProjetil(unsigned int i);
	void criaFlechas();
	void sofrerDano(int dano);
	const bool getVivo() const;
	const int getVidas() const { return vidas; };
};

