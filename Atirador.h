#pragma once
#include <SFML/Graphics.hpp>
#include "Inimigo.h"
#include "Flecha.h"

class Atirador:public Inimigo
{
public:
	Atirador( sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f size);
	~Atirador();
	void update(float deltaTime);
	void mover(); 
	void setDirecao();
	void setPosPlayer(sf::Vector2f pos);
	std::vector<Flecha*> getListaFlechas();
	void apagaFlecha(unsigned int i);
private:
	sf::Texture flecha;
	float tempo_ataque;
	sf::Vector2f difPosPlayer,posPlayer;
	bool direcao;
	std::vector<Flecha*> lflechas;
};

