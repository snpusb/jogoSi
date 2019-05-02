#pragma once
#include "Player.h"
#include <SFML/Audio.hpp>

#include <iostream>
using namespace std;
#include <fstream>
#include "Acido.h"
#include "Espinho.h"
#include "Serra.h"
#include <string>
#include "ListaPlataforma.h"
#include "ListaAtirador.h"
#include "ListaVida.h"
#include "ListaGuerreiro.h"
#include "ListaMoeda.h"
#include "ListaObstaculo.h"
#include "Boss.h"

#define COMPRIMENTO 28
#define LARGURA 57
class Fase
{
protected:
	Player* jogador;
	Player* jogador2;
	string caminhoMapa;
	sf::View* view;
	sf::Texture vidas;
	sf::RectangleShape lifes;
	sf::IntRect rectLifes;
	sf::RectangleShape lifes2;
	sf::IntRect rectLifes2;
	sf::Font font;
	sf::Text pontosText;
	sf::Sound musicLife;
	sf::SoundBuffer bufferCoin;
	sf::SoundBuffer bufferLife;
	sf::SoundBuffer bufferDamage;
	sf::Sound musicCoin;
	sf::Sound musicDamage;
	sf::SoundBuffer bufferDyingEnim;
	sf::Sound musicDyingEnim;
	sf::Texture crate, moeda, terra1, terra2, terra3, ce1, ce2, ce3, cd1, cd2, cd3, platafor1, platafor2, platafor3, quinae, quinad, curvae, curvad, acido1, spike, serra, vida, guerreiro, elf, bg1, bg2, player2;
	FILE* arquivo;
	ListaPlataforma listaPlataforma;
	ListaMoeda listaMoedas;
	ListaObstaculo listaObstaculos;
	ListaVida listaVidas;
	std::vector<Guerreiro*> listaGuerreiros ;
	ListaAtirador listaAtirador;
	sf::RectangleShape background;
	const sf::Vector2f tamanho_plataforma = sf::Vector2f(100.0f, 100.0f);
	const sf::Vector2f tamanho_acido = sf::Vector2f(120.0f, 100.0f);
	int faseAtual;
public:
	Fase(sf::View* vie, string caminhoMapa,int faseAt, bool carregado, Player* jog, Player* jog2 = NULL);
	~Fase();
	virtual void checarColisoes();
	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow& window);
	int getVivo();
	void faseAcabada(sf::RenderWindow & window);
	bool checkColisaoPersonagemGuerreiro(Player* jog, Guerreiro *guerreiro,unsigned int i, AreaDeColisao* col, bool atual, bool danoOutroPlay);
	void inicializar(sf::View* vie, const string caminho, Player* jog, Player* jog2);
	void apagarGuerreiro(unsigned int i);
	virtual bool proximaFase();
	void salvarJogo(int faseAtual);
	void carregarJogo(sf::View* vie, Player* jog, Player* jog2);
	int getFaseAtual();
	Player* jogador2Carregado();
	void geraPlataforma(const int i, sf::Vector2f pos);
};

