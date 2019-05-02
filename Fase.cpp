#include "Fase.h"

Fase::Fase(sf::View* vie, string caminhoMapa,int faseAt,bool carregado, Player* jog, Player* jog2)
{
	faseAtual = faseAt;
	if (carregado)
	{
		carregarJogo(vie, jog, jog2);
	}
	else
	{
		inicializar(vie, caminhoMapa, jog, jog2);
	}
}

Fase::~Fase()
{
}

void Fase::checarColisoes()
{
	sf::Vector2f direçao;
	AreaDeColisao *play = &jogador->getColisor();
	AreaDeColisao *play2 = NULL;
	if (jogador2 != NULL)
	{
		play2 = &jogador2->getColisor();
	}
	AreaDeColisao *gue;
	bool pegB = false;
	Elemento<Plataforma> *pauxPlataforma = listaPlataforma.getPrimeiroElemento();
	std::vector < Guerreiro*> guerreiros = listaGuerreiros;
	Elemento<Obstaculo> *pauxObstaculo = listaObstaculos.getPrimeiroElemento();
	Elemento<Atirador> *pauxAtirador = listaAtirador.getPrimeiroElemento();
	Elemento<Moeda> *pauxMoeda = listaMoedas.getPrimeiroElemento();
	Elemento<Vida> *pauxVida = listaVidas.getPrimeiroElemento();
	//Verifica a colisão de todos os guerreiros com o personagem(s)
	for (unsigned int i = 0; i < guerreiros.size(); i++)
	{	
		gue = &(guerreiros[i]->getColisor());
		pegB = false;
		pauxPlataforma = listaPlataforma.getPrimeiroElemento();
		while(pauxPlataforma != NULL)
		{
			if (pauxPlataforma->getInfo()->getColisor().checkColisao(*gue, direçao, 1.0f))
			{
				guerreiros[i]->emColisao(direçao);
			}
		pauxPlataforma = pauxPlataforma->getProx();
		}
		pegB = checkColisaoPersonagemGuerreiro(jogador, guerreiros[i], i, play, false, false);
		//Verificar e arrumar aqui. Não ta pegando fazendo o negociod de atacar uma vez só por colisao
		if (jogador2 != NULL && !pegB)
		{
			pegB = checkColisaoPersonagemGuerreiro(jogador2, guerreiros[i], i, play2, guerreiros[i]->getDeuDano(), pegB);
		}
	}
	//Verifica a colisão do(s) personagen(s) com as flechas e com os arqueiros
	while(pauxAtirador!= NULL)
	{
		AreaDeColisao *flecha;
		for (unsigned int k = 0; k < pauxAtirador->getInfo()->getListaFlechas().size(); k++)
		{
			pegB = false;
			flecha = &pauxAtirador->getInfo()->getListaFlechas()[k]->getColisor();
			if (flecha->checkColisao(*play, direçao, 0.0f))
			{
				jogador->sofrerDano(pauxAtirador->getInfo()->getListaFlechas()[k]->getDano());
				musicDamage.play();
				pauxAtirador->getInfo()->apagaFlecha(k);
				pegB = true;
			}

			if (jogador2 != NULL && !false)
			{
				if (flecha->checkColisao(*play2, direçao, 0.0f))
				{
					jogador2->sofrerDano(pauxAtirador->getInfo()->getListaFlechas()[k]->getDano());
					musicDamage.play();
					pauxAtirador->getInfo()->apagaFlecha(k);
				}
			}
			//Verifica a colisão das flechas com as plataformas
			pauxPlataforma = listaPlataforma.getPrimeiroElemento();
			while(pauxPlataforma !=NULL)
			{
				AreaDeColisao platafor = pauxPlataforma->getInfo()->getColisor();
				if (platafor.checkColisao(*flecha, direçao, 1.0f))
				{
					pauxAtirador->getInfo()->apagaFlecha(k);
				}
				pauxPlataforma = pauxPlataforma->getProx();
			}
		}

		if (pauxAtirador->getInfo()->getColisor().checkColisao(*play, direçao, 1.0f))
		{
			jogador->emColisao(direçao);
			if (jogador->atacandoAgora())
			{
				musicDyingEnim.play();
				Elemento <Atirador> * paux2 = pauxAtirador;
				pauxAtirador = pauxAtirador->getProx();
				listaAtirador -= paux2->getInfo();
				jogador->addPontos(30);
				pegB = true;
			}
			
		}
		
		if (jogador2 != NULL && !pegB)
		{
			if (pauxAtirador->getInfo()->getColisor().checkColisao(*play2, direçao, 1.0f))
			{
				jogador2->emColisao(direçao);
				if (jogador2->atacandoAgora())
				{
					if (pauxAtirador != NULL)
					{
						musicDyingEnim.play();
						Elemento <Atirador> * paux2 = pauxAtirador;
						pauxAtirador = pauxAtirador->getProx();
						listaAtirador -= paux2->getInfo();
						jogador2->addPontos(30);
					}
				}
			}
		}
		if(pauxAtirador !=NULL)
			pauxAtirador = pauxAtirador->getProx();
	}
	//Verifica a colisão do(s) personagem(s) com as plataformas
	pauxPlataforma = listaPlataforma.getPrimeiroElemento();
	while(pauxPlataforma !=NULL)
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
	//Verifica a colisão do(s) personagem com os obstaculos
	while(pauxObstaculo !=NULL)
	{
		if (pauxObstaculo->getInfo()->getColisor().checkColisao(*play, direçao, 1.0f))
		{
			jogador->emColisao(direçao);
			jogador->sofrerDano(pauxObstaculo->getInfo()->getDano());
			jogador->setPular(false);
			if (pauxObstaculo->getInfo()->getSerra())
			{
				pauxObstaculo->getInfo()->setDano(0);
			}
		}
		
		if (jogador2 != NULL)
		{
			if (pauxObstaculo->getInfo()->getColisor().checkColisao(*play2, direçao, 1.0f))
			{
				jogador2->emColisao(direçao);
				jogador2->sofrerDano(pauxObstaculo->getInfo()->getDano());
				jogador2->setPular(false);
				if (pauxObstaculo->getInfo()->getSerra())
				{
					pauxObstaculo->getInfo()->setDano(0);
				}
			}
		}
		pauxObstaculo = pauxObstaculo->getProx();
	}
	//Verifica a colisão do(s) personagens com as moedas
	while(pauxMoeda != NULL)
	{
		pegB = false;
		if (pauxMoeda->getInfo()->getColisor().checkColisao(*play, direçao, 0.0f))
		{
			jogador->addPontos(pauxMoeda->getInfo()->getValor());
			Elemento<Moeda> *paux2 = pauxMoeda;
			pauxMoeda = pauxMoeda->getProx();
			listaMoedas -= paux2->getInfo();
			pegB = true;
			musicCoin.play();
		}
		if (!pegB)
		{
			if (jogador2 != NULL)
			{
				if (pauxMoeda->getInfo()->getColisor().checkColisao(*play2, direçao, 0.0f))
				{
					if (pauxMoeda != NULL) {
						jogador->addPontos(pauxMoeda->getInfo()->getValor());
						Elemento<Moeda> *paux2 = pauxMoeda;
						pauxMoeda = pauxMoeda->getProx();
						listaMoedas -= paux2->getInfo();
						pegB = true;
						musicCoin.play();

					}
				}
			}
		}
		if(pauxMoeda !=NULL)
			pauxMoeda = pauxMoeda->getProx();
	}
	//Verifica a colisão do(s) personagens com as vidas
	while (pauxVida != NULL) {
		pegB = false;
		if (pauxVida->getInfo()->getColisor().checkColisao(*play, direçao, 0.0f))
		{
			jogador->addVidas(pauxVida->getInfo()->getQtdVida());
			Elemento<Vida> *paux2 = pauxVida;
			pauxVida = pauxVida->getProx();
			listaVidas -= paux2->getInfo();
			pegB = true;
			musicLife.play();
		}

		if (!pegB)
		{
			if (jogador2 != NULL)
			{
				if (pauxVida->getInfo()->getColisor().checkColisao(*play2, direçao, 0.0f))
				{
					if (pauxVida != NULL)
					{
						jogador->addVidas(pauxVida->getInfo()->getQtdVida());
						Elemento<Vida> *paux2 = pauxVida;
						pauxVida = pauxVida->getProx();
						listaVidas -= paux2->getInfo();
						pegB = true;
						musicLife.play();
					}
				}
			}
		}
		if (pauxVida != NULL)
			pauxVida = pauxVida->getProx();
	}
}

void Fase::draw(sf::RenderWindow & window)
{
	window.setView(*view);
	window.clear();
	window.draw(background);
	listaMoedas.draw(window);
	listaObstaculos.draw(window);
	listaVidas.draw(window);

	for (unsigned int i = 0; i < listaGuerreiros.size(); i++)
	{
		listaGuerreiros[i]->draw(window);
	}
	listaPlataforma.draw(window);

	Elemento<Atirador> *pauxAtirador = listaAtirador.getPrimeiroElemento();
	listaAtirador.draw(window);
	while (pauxAtirador != NULL)
	{
		for (unsigned int i = 0; i < pauxAtirador->getInfo()->getListaFlechas().size(); i++)
		{
			pauxAtirador->getInfo()->getListaFlechas()[i]->draw(window);
		}
		pauxAtirador = pauxAtirador->getProx();
	}
	jogador->draw(window);
	if (jogador2 != NULL)
	{
		jogador2->draw(window);
		window.draw(lifes2);
	}
	window.draw(pontosText);
	window.draw(lifes);
	window.display();
}

int Fase::getVivo()
{	
	if (jogador2 != NULL)
	{
		if (jogador->getPosition().y > 3000 || jogador2->getPosition().y > 3000)
		{
			return 0;
		}
		if (jogador->getVidas() <= 0 || jogador2->getVidas() <=0 || jogador->getPosition().y > 3000 || jogador2->getPosition().y >3000)
		{
			return 0;
		}
	}
	if (jogador->getPosition().y > 3000)
	{
		return 0;
	}	
	return jogador->getVidas();
}

void Fase::faseAcabada(sf::RenderWindow & window)
{	
	window.clear();
	pontosText.setString("MORREU! \nSeus pontos: " + std::to_string(jogador->getPontos()));
	pontosText.setPosition(jogador->getPosition().x, jogador->getPosition().y);
	window.draw(pontosText);
	window.display();	
}

bool Fase::checkColisaoPersonagemGuerreiro(Player* jog, Guerreiro* guerreiro,unsigned int i, AreaDeColisao* col, bool atual, bool danoOutroPlay)
{
	sf::Vector2f direçao;
	bool matou = false;
	if (guerreiro->getColisor().checkColisao(*col, direçao, 1.0f))
	{
		if (jog->atacandoAgora())
		{
			musicDyingEnim.play();
			apagarGuerreiro(i);
			jogador->addPontos(30);
			matou = true;
		}
		else if (!guerreiro->getDeuDano() && !danoOutroPlay)
		{
			jog->emColisao(direçao);
			guerreiro->setDeuDano(true);
			jog->sofrerDano(1);
			musicDamage.play();
		}
	}
	else
	{
		guerreiro->setDeuDano(false || atual);
	}
	
	return matou;
}

void Fase::inicializar(sf::View* vie, const string caminho, Player* jog, Player* jog2)
{
	view = vie;
	jogador = jog;
	jogador->setFase(this);
	jogador2 = jog2;
	if (jogador2 != NULL)
	{
		jogador2->setFase(this);
		lifes2.setSize(sf::Vector2f(210.0f, 30.0f));
		lifes2.setTexture(&vidas);
		rectLifes2.width = vidas.getSize().x;
		rectLifes2.height = vidas.getSize().y / 7;
		rectLifes2.left = 0;
	}
	vidas.loadFromFile("imagens/lifes.png");
	lifes.setSize(sf::Vector2f(210.0f, 30.0f));
	lifes.setTexture(&vidas);
	rectLifes.width = vidas.getSize().x;
	rectLifes.height = vidas.getSize().y / 7;
	rectLifes.left = 0;
	if (!font.loadFromFile("arial.ttf"))
	{
		printf("erro na fonte");
	}
	pontosText.setFont(font);
	pontosText.setCharacterSize(24);
	pontosText.setFillColor(sf::Color::White);
	pontosText.setStyle(sf::Text::Bold);
	crate.loadFromFile("imagens/crate.png");
	moeda.loadFromFile("imagens/moeda.png");
	terra1.loadFromFile("imagens/tile (2).png");
	terra2.loadFromFile("imagens/tile (5).png");
	terra3.loadFromFile("imagens/tile (9).png");
	ce1.loadFromFile("imagens/tile (1).png");
	ce2.loadFromFile("imagens/tile (4).png");
	cd1.loadFromFile("imagens/tile (3).png");
	cd2.loadFromFile("imagens/tile (6).png");
	quinad.loadFromFile("imagens/tile (11).png");
	quinae.loadFromFile("imagens/tile (7).png");
	curvad.loadFromFile("imagens/tile (10).png");
	ce3.loadFromFile("imagens/tile (12).png");
	cd3.loadFromFile("imagens/tile (13).png");
	curvae.loadFromFile("imagens/tile (8).png");
	platafor1.loadFromFile("imagens/PLAT14.png");
	platafor2.loadFromFile("imagens/PLAT15.png");
	platafor3.loadFromFile("imagens/PLAT16.png");
	acido1.loadFromFile("imagens/acid.png");
	vida.loadFromFile("imagens/vida.png");
	bg1.loadFromFile("imagens/bg1.png");
	bg2.loadFromFile("imagens/bg2.png");
	background.setSize(sf::Vector2f(7500, 4000));
	background.setPosition(sf::Vector2f(-420, -600));
	if (faseAtual == 1)
	{
		background.setTexture(&bg1);
		guerreiro.loadFromFile("imagens/guerreiroH.png");
	}
	else
	{
		background.setTexture(&bg2);
		guerreiro.loadFromFile("imagens/guerreiroM.png");
	}
	spike.loadFromFile("imagens/spike.png");
	serra.loadFromFile("imagens/saw.png");
	elf.loadFromFile("imagens/elf.png");
	//Para gerar o mapa, é feita a leitura do arquivo txt, via a estrutura de uma matriz de tamanho fixo predefinida
	char linha[120];
	int matriz[COMPRIMENTO][LARGURA];
	fopen_s(&arquivo, caminho.c_str(), "r");
	int c = 0, l = 0;
	if (NULL == arquivo)
	{
		printf("erro no caminho");
	}
	while (fgets(linha, sizeof(linha), arquivo) != NULL)
	{
		for (unsigned int i = 0; i < strlen(linha); i++)
		{
			if (linha[i] != ' ')
			{
				matriz[l][c++] = linha[i] - '0';
			}
		}
		c = 0;
		l++;
	}
	fclose(arquivo);
	//Criação do mapa, via leitura e identifação do arquivo txt
	float posy = 0.0f;
	float posx = 0.0f;
	int qtdAtirador=0, qtdGuerreiro=0, qtdObstaculo=0;
	for (int i = 0; i < COMPRIMENTO; i++)
	{
		for (int j = 0; j < LARGURA; j++)
		{
			if (matriz[i][j] == 23)
			{
				Vida* vid = new Vida(&vida, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(posx, posy), sf::Vector2f(40, 48), 1);
				listaVidas += vid;
			}
			else if (matriz[i][j] == 2)
			{
				Moeda* moed = new Moeda(&moeda, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(posx, posy), sf::Vector2f(20, 24), 5);
				listaMoedas += moed;
			}
			else if (matriz[i][j] == 19)
			{
				Acido* obst = new Acido(&acido1, sf::Vector2f(120.0f, 60.0f), sf::Vector2f(posx, posy + 30.0f));
				listaObstaculos += static_cast<Obstaculo*>(obst);
				qtdObstaculo++;
			}
			else if (matriz[i][j] == 24)
			{
				Guerreiro* guer = new Guerreiro(&guerreiro, sf::Vector2u(3, 3), 0.5f, 100.0f, sf::Vector2f(posx, posy), sf::Vector2f(80.0f, 96.0f));
				listaGuerreiros.push_back(guer);
				qtdGuerreiro++;
			}
			else if (matriz[i][j] == 21)
			{
				Espinho* obst = new Espinho(&spike, sf::Vector2f(100.0f, 60.0f), sf::Vector2f(posx, posy + 30.0f));
				listaObstaculos += static_cast<Obstaculo*>(obst);
				qtdObstaculo++;
			}
			else if (matriz[i][j] == 22)
			{
				Serra* obst = new Serra(&serra, tamanho_plataforma, sf::Vector2f(posx, posy + tamanho_plataforma.y / 2.0f));
				listaObstaculos += static_cast<Obstaculo*>(obst);
				qtdObstaculo++;
			}
			else if (matriz[i][j] == 25)
			{
				Atirador* atirador = new Atirador(&elf, sf::Vector2u(3, 3), 0.2f, 300.0f, sf::Vector2f(posx, posy), sf::Vector2f(100.0f, 100.0f));
				listaAtirador += atirador;
				qtdAtirador++;
			}
			else if (matriz[i][j] == 26)
			{
				Serra* obst = new Serra(&serra, tamanho_plataforma, sf::Vector2f(posx + tamanho_plataforma.x / 2.0f, posy));
				listaObstaculos += static_cast<Obstaculo*>(obst);
				qtdObstaculo++;
			}
			else if (matriz[i][j] == 27)
			{
				Serra* obst = new Serra(&serra, tamanho_plataforma, sf::Vector2f(posx - tamanho_plataforma.x / 2.0f, posy));
				listaObstaculos += static_cast<Obstaculo*>(obst);
				qtdObstaculo++;
			}
			else
			{
				geraPlataforma(matriz[i][j], sf::Vector2f(posx, posy));
			}
			posx += tamanho_plataforma.x;
		}
		posy += tamanho_plataforma.y;
		posx = 0.0f;
	}

	Elemento<Obstaculo> *pauxObstaculo = listaObstaculos.getPrimeiroElemento();
	Elemento<Atirador> *pauxAtirador = listaAtirador.getPrimeiroElemento();
	if (qtdAtirador > 8)
	{
		srand(time(NULL));
		int retira = rand() % (qtdAtirador - 5);
		while (pauxAtirador != NULL)
		{
			if (rand() % 2 && retira != 0)
			{
				Elemento <Atirador> * paux2 = pauxAtirador;
				pauxAtirador = pauxAtirador->getProx();
				listaAtirador -= paux2->getInfo();
				retira--;
				qtdAtirador--;
			}
			if (pauxAtirador != NULL)
			{
				pauxAtirador = pauxAtirador->getProx();
			}
		}
	}
	if (qtdObstaculo > 18)
	{
		srand(time(NULL));
		int retira = rand() % (qtdObstaculo - 5);
		while (pauxObstaculo != NULL)
		{
			if (rand() % 2 && retira != 0)
			{
				Elemento <Obstaculo> * paux2 = pauxObstaculo;
				pauxObstaculo = pauxObstaculo->getProx();
				listaObstaculos -= paux2->getInfo();
				retira--;
			}
			if (pauxObstaculo != NULL)
			{
				pauxObstaculo = pauxObstaculo->getProx();
			}
			
		}
	}
	if (qtdGuerreiro > 8)
	{
		srand(time(NULL));
		int retira = rand() % (qtdGuerreiro- 5);
		for (unsigned int i = 0; i < listaGuerreiros.size(); i++)
		{
			if (rand() % 2 && retira != 0) 
			{
				apagarGuerreiro(i);
				retira--;
				qtdGuerreiro--;
			}
		}	
	}

	if (!bufferLife.loadFromFile("sons/life.wav"))
	{
		std::cout << "ERROR IN MUSIC" << std::endl;
	}
	musicLife.setBuffer(bufferLife);

	if (!bufferCoin.loadFromFile("sons/coin.wav"))
	{
		std::cout << "ERROR IN MUSIC" << std::endl;
	}
	musicCoin.setBuffer(bufferCoin);

	if (!bufferDamage.loadFromFile("sons/damage.wav"))
	{
		std::cout << "ERROR IN MUSIC" << std::endl;
	}
	musicDamage.setBuffer(bufferDamage);
	if (!bufferDyingEnim.loadFromFile("sons/inimigoMorre.wav"))
	{
		std::cout << "ERROR IN MUSIC" << std::endl;
	}
	musicDyingEnim.setBuffer(bufferDyingEnim);
}

void Fase::update(float deltaTime)
{
	jogador->update(deltaTime);
	if (jogador2 != NULL)
	{
		jogador2->update(deltaTime);
	}
	listaMoedas.update(deltaTime);
	for (unsigned int i = 0; i < listaGuerreiros.size(); i++)
	{
		listaGuerreiros[i]->update(deltaTime);
	}
	listaObstaculos.update(deltaTime);
	listaAtirador.update(deltaTime,jogador->getPosition());
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
}

void Fase::apagarGuerreiro(unsigned int i)
{
	if (i < listaGuerreiros.size())
	{
		delete listaGuerreiros[i];
		listaGuerreiros.erase(listaGuerreiros.begin() + i);
	}
}

bool Fase::proximaFase()
{
	if ((jogador->getPosition().x >= 5300 && jogador->getPosition().y >= 2300 && jogador->getPosition().x <= 5500 && jogador->getPosition().y <= 2600)
		|| (jogador2 != NULL && jogador2->getPosition().x >= 5300 && jogador2->getPosition().y >= 2300 && jogador2->getPosition().x <= 5500 && jogador2->getPosition().y <= 2600))
	{
		return true;
	}
	return false;
}

void Fase::salvarJogo(int faseAtual)
{
	Elemento<Obstaculo> *pauxObstaculo = listaObstaculos.getPrimeiroElemento();
	Elemento<Atirador> *pauxAtirador = listaAtirador.getPrimeiroElemento();
	Elemento<Moeda> *pauxMoeda = listaMoedas.getPrimeiroElemento();
	Elemento<Vida> *pauxVida = listaVidas.getPrimeiroElemento();
	ofstream salvarFase("savejogo.dat", ios::out);
	if (!salvarFase)
	{
		cerr << " Arquivo não pode ser aberto " << endl;
		fflush(stdin);
		return;
	}
	salvarFase <<0<<" "<< faseAtual << endl;

	for (unsigned int i = 0; i < listaGuerreiros.size() ; i++)
	{
		salvarFase << 1 << " " << listaGuerreiros[i]->getPosition().x << " " << listaGuerreiros[i]->getPosition().y << endl;//VER DE SALVAR A DATA
	}

	while (pauxAtirador != NULL)
	{
		salvarFase << 2 << " " << pauxAtirador->getInfo()->getPosition().x << " " << pauxAtirador->getInfo()->getPosition().y << endl;//VER DE SALVAR A DATA
		pauxAtirador = pauxAtirador->getProx();
	}

	while (pauxObstaculo != NULL)
	{
		salvarFase << 3 << " " << pauxObstaculo->getInfo()->getPosition().x << " " << pauxObstaculo->getInfo()->getPosition().y << " " <<pauxObstaculo->getInfo()->getId() << endl;//VER DE SALVAR A DATA
		pauxObstaculo = pauxObstaculo->getProx();
	}

	while (pauxMoeda != NULL)
	{
		salvarFase << 4 << " " << pauxMoeda->getInfo()->getPosition().x << " " << pauxMoeda->getInfo()->getPosition().y << endl;//VER DE SALVAR A DATA
		pauxMoeda = pauxMoeda->getProx();
	}

	while (pauxVida != NULL)
	{
		salvarFase << 5 << " " << pauxVida->getInfo()->getPosition().x << " " << pauxVida->getInfo()->getPosition().y << endl;//VER DE SALVAR A DATA
		pauxVida = pauxVida->getProx();
	}
	if (jogador2 != NULL)
	{
		salvarFase << 7 << " " << jogador2->getVidas() << " " << jogador2->getPosition().x << " " << jogador2->getPosition().y<< endl;
	}
	salvarFase << 6 << " " << jogador->getPontos() << " " << jogador->getVidas() << " " << jogador->getPosition().x << " " << jogador->getPosition().y;

	salvarFase.close();
}

void Fase::carregarJogo(sf::View* vie, Player* jog, Player* jog2)
{
	player2.loadFromFile("imagens/orc2.png");
	crate.loadFromFile("imagens/crate.png");
	moeda.loadFromFile("imagens/moeda.png");
	terra1.loadFromFile("imagens/tile (2).png");
	terra2.loadFromFile("imagens/tile (5).png");
	terra3.loadFromFile("imagens/tile (9).png");
	ce1.loadFromFile("imagens/tile (1).png");
	ce2.loadFromFile("imagens/tile (4).png");
	cd1.loadFromFile("imagens/tile (3).png");
	cd2.loadFromFile("imagens/tile (6).png");
	quinad.loadFromFile("imagens/tile (11).png");
	quinae.loadFromFile("imagens/tile (7).png");
	curvad.loadFromFile("imagens/tile (10).png");
	ce3.loadFromFile("imagens/tile (12).png");
	cd3.loadFromFile("imagens/tile (13).png");
	curvae.loadFromFile("imagens/tile (8).png");
	platafor1.loadFromFile("imagens/PLAT14.png");
	platafor2.loadFromFile("imagens/PLAT15.png");
	platafor3.loadFromFile("imagens/PLAT16.png");
	acido1.loadFromFile("imagens/acid.png");
	vida.loadFromFile("imagens/vida.png");
	spike.loadFromFile("imagens/spike.png");
	serra.loadFromFile("imagens/saw.png");
	elf.loadFromFile("imagens/elf.png");
	bg1.loadFromFile("imagens/bg1.png");
	bg2.loadFromFile("imagens/bg2.png");

	background.setSize(sf::Vector2f(7500, 4000));
	background.setPosition(sf::Vector2f(-420, -600));

	view = vie;
	jogador = jog;
	jogador->setFase(this);

	vidas.loadFromFile("imagens/lifes.png");
	lifes.setSize(sf::Vector2f(210.0f, 30.0f));
	lifes.setTexture(&vidas);

	rectLifes.width = vidas.getSize().x;
	rectLifes.height = vidas.getSize().y / 7;
	rectLifes.left = 0;
	ifstream CarregarJogo("savejogo.dat", ios::in);
	if (!CarregarJogo)
	{
		cerr << " Arquivo não pode ser aberto " << endl;
		fflush(stdin);
	}
	
	while (!CarregarJogo.eof())
	{
		int id;
		CarregarJogo >> id;
		if (id == 0) {
			int num;
			CarregarJogo >> num;
			faseAtual = num;
			if (faseAtual == 1)
			{
				guerreiro.loadFromFile("imagens/guerreiroH.png");
				background.setTexture(&bg1);
			}
			else
			{
				guerreiro.loadFromFile("imagens/guerreiroM.png");
				background.setTexture(&bg2);
			}
		}
		else if (id == 1)
		{
			float posx, posy;
			CarregarJogo >> posx >> posy;
			Guerreiro* guer = new Guerreiro(&guerreiro, sf::Vector2u(3,3), 0.5f, 100.0f, sf::Vector2f(posx, posy), sf::Vector2f(80.0f, 96.0f));
			listaGuerreiros.push_back(guer);
		}
		else if (id == 2) {
			float posx, posy;
			CarregarJogo >> posx >> posy;
			Atirador* atirador = new Atirador(&elf, sf::Vector2u(3, 3), 0.2f, 300.0f, sf::Vector2f(posx, posy), sf::Vector2f(100.0f, 100.0f));
			listaAtirador += atirador;
		}
		else if (id == 3)
		{
			float posx, posy;
			int obstid;
			CarregarJogo >> posx >> posy >> obstid;
			if (obstid == 1)
			{
				Acido* obst = new Acido(&acido1, sf::Vector2f(120.0f, 60.0f), sf::Vector2f(posx, posy));
				listaObstaculos += static_cast<Obstaculo*>(obst);
			}
			else if (obstid == 2)
			{
				Espinho* obst = new Espinho(&spike, sf::Vector2f(100.0f, 60.0f), sf::Vector2f(posx, posy));
				listaObstaculos += static_cast<Obstaculo*>(obst);
			}
			else if (obstid == 3)
			{
				Serra* obst = new Serra(&serra, tamanho_plataforma, sf::Vector2f(posx, posy));
				listaObstaculos += static_cast<Obstaculo*>(obst);
			}
		}
		else if (id == 4)
		{
			float posx, posy;
			CarregarJogo >> posx >> posy;
			Moeda* moed = new Moeda(&moeda, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(posx, posy), sf::Vector2f(20, 24), 5);
			listaMoedas += moed;
		}
		else if (id == 5) {
			float posx, posy;
			CarregarJogo >> posx >> posy;
			Vida* vid = new Vida(&vida, sf::Vector2u(10, 1), 0.1f, sf::Vector2f(posx, posy), sf::Vector2f(40, 48), 1);
			listaVidas += vid;
		}
		else if (id == 6)
		{
			int pontos, vidas;
			float posx, posy;
			CarregarJogo >> pontos >> vidas >> posx >> posy;
			jogador->setPontos(pontos);
			jogador->setVida(vidas);
			jogador->setPostition(sf::Vector2f(posx, posy));
		}
		else if (id == 7) 
		{
				jogador2 = new Player(&player2, sf::Vector2u(3, 6), 0.18f, 170.0f, 100.0f, sf::Vector2f(200, 0), sf::Vector2f(100, 100), 2);
				int vidas;
				float posx, posy;
				CarregarJogo >> vidas >> posx >> posy;
				jogador2->setVida(vidas);
				jogador2->setPostition(sf::Vector2f(posx, posy));
		}
		else
		{
			jogador2 = NULL;
		}
		
	}
	CarregarJogo.close();
	if (jogador2 != NULL)
	{
		jogador2->setFase(this);
		lifes2.setSize(sf::Vector2f(210.0f, 30.0f));
		lifes2.setTexture(&vidas);
		rectLifes2.width = vidas.getSize().x;
		rectLifes2.height = vidas.getSize().y / 7;
		rectLifes2.left = 0;
	}

	if (!font.loadFromFile("arial.ttf"))
	{
		printf("erro na fonte");
	}
	if (faseAtual == 1)
	{
		caminhoMapa = "mapas/mapa1.txt";
	}
	else if (faseAtual == 2)
	{
		caminhoMapa = "mapas/mapa2.txt";
	}
	pontosText.setFont(font);
	pontosText.setCharacterSize(24);
	pontosText.setFillColor(sf::Color::White);
	pontosText.setStyle(sf::Text::Bold);


	//matrix ja possui tamanho fixo 
	char linha[120];
	int matriz[COMPRIMENTO][LARGURA];
	fopen_s(&arquivo, caminhoMapa.c_str(), "r");
	int c = 0, l = 0;
	if (NULL == arquivo)
	{
		printf("erro no caminho");
	}
	while (fgets(linha, sizeof(linha), arquivo) != NULL)
	{
		for (unsigned int i = 0; i < strlen(linha); i++)
		{
			if (linha[i] != ' ')
			{
				matriz[l][c++] = linha[i] - '0';
			}
		}
		c = 0;
		l++;
	}
	fclose(arquivo);
	float posy = 0.0f;
	float posx = 0.0f;
	for (int i = 0; i < COMPRIMENTO; i++)
	{
		for (int j = 0; j < LARGURA; j++)
		{
			geraPlataforma(matriz[i][j], sf::Vector2f(posx, posy));
			posx += tamanho_plataforma.x;
		}
		posy += tamanho_plataforma.y;
		posx = 0.0f;
	}
}

int Fase::getFaseAtual()
{
	return faseAtual;
}

Player * Fase::jogador2Carregado()
{
	return jogador2;
}

void Fase::geraPlataforma(const int i, sf::Vector2f pos)
{
	if (i == 1)
	{
		Plataforma* plat = new Plataforma(&crate, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 3)
	{
		Plataforma* plat = new Plataforma(&terra1, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 4)
	{
		Plataforma* plat = new Plataforma(&terra2, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 15)
	{
		Plataforma* plat = new Plataforma(&quinad, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 17)
	{
		Plataforma* plat = new Plataforma(&curvae, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 16)
	{
		Plataforma* plat = new Plataforma(&quinae, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 11)
	{
		Plataforma* plat = new Plataforma(&cd3, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 8)
	{
		Plataforma* plat = new Plataforma(&ce3, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 5)
	{
		Plataforma* plat = new Plataforma(&terra3, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 10)
	{
		Plataforma* plat = new Plataforma(&cd2, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 18)
	{
		Plataforma* plat = new Plataforma(&curvad, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 7)
	{
		Plataforma* plat = new Plataforma(&ce2, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 9)
	{
		Plataforma* plat = new Plataforma(&cd1, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 6)
	{
		Plataforma* plat = new Plataforma(&ce1, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 12)
	{
		Plataforma* plat = new Plataforma(&platafor1, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 13)
	{
		Plataforma* plat = new Plataforma(&platafor2, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
	else if (i == 14)
	{
		Plataforma* plat = new Plataforma(&platafor3, tamanho_plataforma, pos);
		listaPlataforma += plat;
	}
}
