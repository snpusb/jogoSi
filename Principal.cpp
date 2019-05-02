#include "Principal.h"
using namespace Game;

#define WINDOW_HEIGHT 512
#define HEIGHT 50
#define WIDHT  40
Principal* Principal::_instance = 0;

Principal::Principal():
	window(sf::VideoMode(600, 600), "Orc's Injustice", sf::Style::Close),
	view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WINDOW_HEIGHT, WINDOW_HEIGHT))
{
	iniciar();
}

Principal::~Principal()
{
}

void Principal::executar()
{
	musicOpen->play();
	Sleep(2000);
	musicMenuInicial->play();
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		sf::Event evnt;
		if (deltaTime > 1.0f / 20.0f)
		{
			deltaTime = 1.0f / 20.0f;
		}
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				if (evnt.text.unicode < 128 && evnt.text.unicode != 32&& evnt.text.unicode !=8)
				{
					if (entradaMenu == 10)
					{
						name += evnt.text.unicode;
					}

				}
				break;
			}
		}
		if (entradaMenu != 0)
		{
			musicMenuInicial->stop();
		}
		else if (sf::Sound::Status::Playing != musicMenuInicial->getStatus())
		{
			musicMenuInicial->play();
		}


		if (entradaMenu != 5)
		{
			musicGame->stop();
		}
		else if (sf::Sound::Status::Playing != musicGame->getStatus())
		{
			musicGame->play();
		}

		switch (entradaMenu)
		{
		case 0:
			window.clear();
			menu.draw(window);
			window.display();
			player = NULL;
			player2 = NULL;
			entradaMenu = menu.getBotaoClicado(window);
			Sleep(50);
			break;
		case 1:

			entradaMenu = 13;
			type = 1;
			
			break;
		case 2:
			type = 2;
			entradaMenu = 13;
			break;
		case 3:
			button = menu.drawButtonMenuInicial(window);
			button.setPosition(350, 500);
			gerarMostrarRanking(window);
			window.draw(button);
			window.display();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i position = sf::Mouse::getPosition(window);

				if (menu.verificaClique(position, button))
				{
					Sleep(500);
					entradaMenu = 0;
				}
			}
			break;

		case 4:
			window.close();
			break;
		case 5:
			if (fase != NULL)
			{
				if (fase->getVivo())
				{
					fase->checarColisoes();
					fase->update(deltaTime);
					fase->draw(window);
					if (fase->proximaFase())
					{
						entradaMenu = 16;
					}
				}
				else if (entradaMenu != 3)
				{
					musicGame->stop();
					musicDying.play();
					Sleep(700);
					musicLose.play();
					Sleep(1700);
					musicLaunch.play();

					musicLose.play();
					fase->faseAcabada(window);
					entradaMenu = 9;
					Sleep(300);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					view.setCenter(sf::Vector2f(260, 300));
					window.setView(view);
					entradaMenu = 7;

				}
				
			}
			else if (faseFinal != NULL)
			{
				if (faseFinal->getVivo())
				{
					faseFinal->checarColisoes();
					faseFinal->update(deltaTime);
					faseFinal->draw(window);
					if (faseFinal->proximaFase())
					{
						entradaMenu = 16;
					}
				}
				else if (entradaMenu != 3)
				{
					musicGame->stop();
					musicDying.play();
					Sleep(700);
					musicLose.play();
					Sleep(1700);
					musicLaunch.play();
					musicLose.play();
					faseFinal->faseAcabada(window);
					entradaMenu = 9;
					Sleep(300);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					view.setCenter(sf::Vector2f(260, 300));
					window.setView(view);
					entradaMenu = 7;

				}
			}
			break;
		case 6:
			player = NULL;
			player2 = NULL;
			entradaMenu = 15;
			break;
		case 7:
			view.setCenter(sf::Vector2f(260, 300));
			window.setView(view);
			window.clear();
			menu.drawMenuPause(window);
			window.display();
			entradaMenu = menu.getBotaoClicadoMenuPause(window);
			Sleep(50);
			break;
		case 8:
			Sleep(1100);
			entradaMenu = 0;
			break;
		case 9:
			view.setCenter(sf::Vector2f(260, 300));
			window.setView(view);
			window.clear();
			menu.drawMenuJogoAcabado(window);
			window.display();
			entradaMenu = menu.getBotaoClicadoJogoAcabado(window);
			Sleep(50);
			break;
		case 10:

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if (name.size() < 1)
				{
					name = "Desconhecido";
				}
				salvar(name, player->getPontos());
				entradaMenu = 0;
			}
			else
			{
				sf::Texture bg;
				sf::RectangleShape bgR;
				bg.loadFromFile("imagens/bgSalvar.png");
				bgR.setSize(sf::Vector2f(600.0f, 600.0f));
				bgR.setPosition(sf::Vector2f(0.0f, 0.0f));
				bgR.setTexture(&bg);
				window.clear();
				window.draw(bgR);
				nameS.setString(name);
				window.draw(nameS);
				window.display();
			}
			break;
		case 11:
			entradaMenu = 15;
			faseAtualNum = 1;
			break;
		case 12:
			entradaMenu = 15;
			faseAtualNum = 2;
			break;
		case 13:
			window.clear();
			menu.drawEscolherFase(window);
			window.display();
			entradaMenu = menu.getFaseEscolhida(window);
			Sleep(50);
			break;
		case 15:
			name = "";
			if (faseAtualNum == 1)
			{
				caminho = "mapas/mapa1.txt";
			}
			else if (faseAtualNum == 2)
			{
				caminho = "mapas/mapa2.txt";
			}
			if (type == 1)
			{
				player = new Player(&playerTexture, sf::Vector2u(3, 6), 0.18f, 170.0f, 100.0f, sf::Vector2f(200, 0), sf::Vector2f(100, 100), 1);
				fase = new Fase(&view, caminho, faseAtualNum, false, player);
			}
			else if (type == 2)
			{
				player = new Player(&playerTexture, sf::Vector2u(3, 6), 0.18f, 170.0f, 100.0f, sf::Vector2f(200, 0), sf::Vector2f(100, 100), 1);
				player2 = new Player(&playerTexture2, sf::Vector2u(3,6), 0.18f, 170.0f, 100.0f, sf::Vector2f(200, 0), sf::Vector2f(100, 100), 2);

				fase = new Fase(&view, caminho, faseAtualNum,false, player, player2);
			}
			if (faseAtualNum == 3)
			{
				delete(faseFinal);
				fase = NULL;
				caminho = "mapas/mapaBoss.txt";
				player->setPostition(sf::Vector2f(500.0f, 500.0f));
				if (player2 != NULL)
				{
					player2->setPostition(sf::Vector2f(500.0f, 500.0f));
					faseFinal = new FaseBoss(&view, caminho, player, player2);
				}
				else
				{
					faseFinal = new FaseBoss(&view, caminho, player);
				}
			}
			entradaMenu = 5;
			break;
		case 16:
			if (faseAtualNum == 1)
			{
				player->setPostition(sf::Vector2f(200, 0));
				faseAtualNum = 2;
				caminho = "mapas/mapa2.txt";
				if (player2 != NULL)
				{
					player2->setPostition(sf::Vector2f(200.0f, 0.0f));
					fase = new Fase(&view, caminho, faseAtualNum,false, player, player2);
				}
				else
				{
					fase = new Fase(&view, caminho, faseAtualNum,false, player);
				}
				entradaMenu = 5;
			}
			else if (faseAtualNum == 2)
			{
				player->setPostition(sf::Vector2f(500, 500));
				faseAtualNum = 3;
				delete(fase);
				fase = NULL;
				caminho = "mapas/mapaBoss.txt";
				if (player2 != NULL)
				{
					player2->setPostition(sf::Vector2f(400.0f, 500.0f));
					faseFinal = new FaseBoss(&view, caminho, player, player2);
				}
				else
				{
					faseFinal = new FaseBoss(&view, caminho, player);
				}
				entradaMenu = 5;
			}
			else if (faseAtualNum == 3)
			{
				player->addPontos(100);
				musicWin.play();
				faseFinal->faseFinalizada(window);
				Sleep(1000);
				view.setCenter(sf::Vector2f(260, 300));
				window.setView(view);
				delete(faseFinal);
				faseFinal = NULL;
				entradaMenu = 10;
			}
			break;
		case 17:
			Sleep(500);
			if (faseAtualNum != 3) 
			{
				fase->salvarJogo(faseAtualNum);
				menu.setGeraContinue(true);
				entradaMenu = 0;
			}
			else 
			{
				entradaMenu = 7;
			}
			break;
		case 18:
			player = new Player(&playerTexture, sf::Vector2u(3, 6), 0.18f, 170.0f, 100.0f, sf::Vector2f(200, 0), sf::Vector2f(100, 100), 1);
			fase = new Fase(&view, caminho, 0, true, player);
			player2 = fase->jogador2Carregado();
			faseAtualNum = fase->getFaseAtual();
			entradaMenu = 5;
					
			break;
		}
	}
}

void Principal::iniciar()
{
	player = NULL;
	player2 = NULL;

	caminho = "nenhum";
	musicOpen = new sf::Music();
	if (!musicOpen->openFromFile("sons/start.wav"))
	{
		std::cout << "ERROR IN MUSIC" << std::endl;
	}

	musicGame = new sf::Music();
	if (!musicGame->openFromFile("sons/duringGame.wav"))
	{
		std::cout << "ERROR IN MUSIC" << std::endl;
	}
	musicGame->setLoop(true);

	musicMenuInicial = new sf::Music();
	if (!musicMenuInicial->openFromFile("sons/backgroundInicial.wav"))
	{
		std::cout << "ERROR IN MUSIC" << std::endl;
	}
	musicMenuInicial->setLoop(true);

	if (!bufferLaunch.loadFromFile("sons/risada.wav"))
	{
		std::cout << "ERROR IN MUSIC" << std::endl;
	}
	musicLaunch.setBuffer(bufferLaunch);

	if (!bufferLose.loadFromFile("sons/lose.wav"))
	{
		std::cout << "ERROR IN MUSIC" << std::endl;
	}
	musicLose.setBuffer(bufferLose);
	if (!bufferDying.loadFromFile("sons/dying.wav"))
	{
		std::cout << "ERROR IN MUSIC" << std::endl;
	}
	musicDying.setBuffer(bufferDying);
	getRanking();

	playerTexture.loadFromFile("imagens/ogro2.png");
	playerTexture2.loadFromFile("imagens/orc2.png");

	fase = NULL;
	deltaTime = 0.0f;

	entradaMenu = 0;
	type = 1;
	name = "";
	if (!font.loadFromFile("arial.ttf"))
	{
		printf("erro na fonte");
	}
	nameS.setFont(font);
	nameS.setCharacterSize(24);
	nameS.setFillColor(sf::Color::Black);
	nameS.setStyle(sf::Text::Bold);
	nameS.setPosition(sf::Vector2f(100, 300));


}

Principal* Game::Principal::instance()
{
	if (_instance == 0)
	{
		_instance = new Principal();
	}

	return _instance;
}

void Principal::salvar(string nomeE, int pontosE)
{
	Pontuacao* pon = new Pontuacao;
	pon->pontos = pontosE;
	pon->nome = nomeE;
	rankingAtual.push_back(pon);
	int pos = rankingAtual.size() - 1;
	for (int i = rankingAtual.size() - 1; i >= 0; i--)
	{
		if (pontosE >= rankingAtual[i]->pontos)
		{
			Pontuacao* ver = rankingAtual[i];
			rankingAtual[i] = pon;
			rankingAtual[pos] = ver;
			pos = i;
		}
		else
		{
			break;
		}
	}


	ofstream gravacaoPontos("ranking.dat", ios::out);
	if (!gravacaoPontos)
	{
		cerr << " Arquivo não pode ser aberto " << endl;
		fflush(stdin);
		return;
	}
	for (unsigned int i = 0; i < rankingAtual.size(); i++)
	{

		gravacaoPontos << rankingAtual[i]->nome << " " << rankingAtual[i]->pontos << endl;//VER DE SALVAR A DATA
	}

	gravacaoPontos.close();

}

void Principal::getRanking()
{
	ifstream recuperarRanking("ranking.dat", ios::in);
	if (!recuperarRanking)
	{
		cerr << " Arquivo não pode ser aberto " << endl;
		fflush(stdin);
		return;
	}
	while (!recuperarRanking.eof())
	{
		Pontuacao* pont = new Pontuacao;
		int pontose = 0;
		string nomee;
		string datae;
		recuperarRanking >> nomee >> pontose; //>> datae;
		// pont->data = datae;
		pont->nome = nomee;
		pont->pontos = pontose;
		rankingAtual.push_back(pont);
	}
	rankingAtual.pop_back();//Retira o ultimo, pois ele pega um a mais e seta como zero, depois na hora de salvar da problema
	recuperarRanking.close();
}

void Principal::gerarMostrarRanking(sf::RenderWindow & window)
{
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		printf("erro na fonte");
	}
	vector<sf::Text*> listaPontos;
	for (unsigned int i = 0; i < 10 && i < rankingAtual.size(); i++)
	{
		sf::Text* pontosText = new sf::Text;
		pontosText->setFont(font);
		pontosText->setCharacterSize(24);
		pontosText->setFillColor(sf::Color::White);
		pontosText->setStyle(sf::Text::Bold);
		pontosText->setString(std::to_string(i + 1) + "° " + rankingAtual[i]->nome + " " + std::to_string(rankingAtual[i]->pontos));
		pontosText->setPosition(50.0f, 140.0f + 25*(i + 1));
		listaPontos.push_back(pontosText);
	}

	for (unsigned int i = 0; i < listaPontos.size(); i++)
	{
		window.draw(*(listaPontos[i]));
	}
	
}
