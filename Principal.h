#pragma once
#include "Player.h"
#include "FaseBoss.h"
#include "Menu.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>
#include<time.h>
#include<windows.h>
namespace Game
{
	class Principal
	{
	private:
		class Pontuacao
		{
		public:
			int pontos;
			string nome;
			string data;
		};

		Player* player;
		Player* player2;
		Fase* fase;
		FaseBoss* faseFinal;
		int faseAtualNum;
		sf::Text nameS;
		sf::Font font;
		string name;

		sf::RenderWindow window;
		sf::View view;
		sf::Texture playerTexture, playerTexture2;
		sf::RectangleShape button;
		Menu menu;
		float deltaTime;
		sf::Clock clock;
		int entradaMenu;
		int type = 1;
		string caminho;

		sf::Music* musicOpen;
		sf::Music* musicMenuInicial;
		sf::Music* musicGame;
		sf::SoundBuffer bufferLaunch;
		sf::Sound musicLaunch;
		sf::SoundBuffer bufferLose;
		sf::Sound musicLose;
		sf::SoundBuffer bufferDying;
		sf::Sound musicDying;
		sf::SoundBuffer bufferWin;
		sf::Sound musicWin;
		vector<Pontuacao*> rankingAtual;
		Principal();
		static Principal *_instance;
	public:
		~Principal();
		void iniciar();
		Principal* instance();
		void salvar(string nomeE, int pontosE);
		void getRanking();
		void gerarMostrarRanking(sf::RenderWindow & window);
		void executar();
	};
}