#pragma once
#include "Personagem.h"
#include "Obstaculo.h"

class Fase;

class Player: public Personagem
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,float alturaP, sf::Vector2f position, sf::Vector2f size, int nb);
	~Player();
	void update(float deltaTime);
	void emColisao(sf::Vector2f& direcao);
	void mover();
	void addPontos(const int po);
	void addVidas(const int qtd);
	const int getPontos() const;
	void setPular(const bool pul);
	void sofrerDano(const int dano);
	bool atacandoAgora();
	void setFase(Fase* faseAtual);
	void setPontos(const int pont);
private:
	sf::Vector2f velocidade;
	bool podePular;
	float alturaPulo, tempo_ataque;
	int pontos;
	bool atacando;
	float deltaTimeIn;
	int numberPlayer;
	Fase* fase;
};