#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
using namespace std;

class Menu
{
private:
	sf::Texture jogar, ranking, sair, bg, play2, restart, continuar, bgPause, menuInicial, salvar, bgAcabado, fase1, fase2, bgRanking, salvarJogo;
	sf::RectangleShape bBg, bJogar, bRanking, bSair, bPlayer2, bRestart, bContinuar, bBgPause, bMenuInicial, bSalvar, bBgAcabado, bFase1, bFase2, bBgRanking,bSalvarJogo;
	sf::Vector2f tamanhoBotao;
	bool geraContinuePrincipal;
public:
	Menu();
	~Menu();
	void draw(sf::RenderWindow & window);
	void drawMenuPause(sf::RenderWindow & window);
	void drawMenuJogoAcabado(sf::RenderWindow & window);
	void drawEscolherFase(sf::RenderWindow & window);
	int getBotaoClicado(sf::RenderWindow & window);
	int getFaseEscolhida(sf::RenderWindow & window);
	bool verificaClique(sf::Vector2i pos, sf::RectangleShape button);
	int getBotaoClicadoMenuPause(sf::RenderWindow & window);
	int getBotaoClicadoJogoAcabado(sf::RenderWindow & window);
	void inicializar();
	void verificaEmCimaBotao(sf::Vector2i pos, sf::RectangleShape* button, sf::Vector2f posPadrao);
	sf::RectangleShape drawButtonMenuInicial(sf::RenderWindow & window);
	void setGeraContinue(bool ne);
};


