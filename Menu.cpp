#include "Menu.h"
#include<windows.h>

Menu::Menu()
{
	inicializar();
	ifstream CarregarJogo("savejogo.dat", ios::in);
	if (!CarregarJogo)
	{
		cerr << " Arquivo não pode ser aberto " << endl;
		fflush(stdin);
		geraContinuePrincipal = false;
	}
	else
	{
		geraContinuePrincipal = true;
	}
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow & window)
{
	window.draw(bBg);
	window.draw(bJogar);
	window.draw(bPlayer2);
	if (geraContinuePrincipal)
	{
		window.draw(bContinuar);
	}
	window.draw(bRanking);
	window.draw(bSair);
}

void Menu::drawMenuPause(sf::RenderWindow & window)
{
	window.draw(bBgPause);
	window.draw(bContinuar);
	window.draw(bRestart);
	window.draw(bMenuInicial);
	window.draw(bSalvarJogo);
}

void Menu::drawMenuJogoAcabado(sf::RenderWindow & window)
{
	window.draw(bBgAcabado);
	window.draw(bSalvar);
	window.draw(bRestart);
	window.draw(bRanking);
	window.draw(bMenuInicial);
}

void Menu::drawEscolherFase(sf::RenderWindow & window)
{
	window.draw(bBg);
	window.draw(bFase1);
	window.draw(bFase2);
}

int Menu::getBotaoClicado(sf::RenderWindow & window)
{
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bJogar, tamanhoBotao);
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bPlayer2, tamanhoBotao);
	if (geraContinuePrincipal)
	{
		verificaEmCimaBotao(sf::Mouse::getPosition(window), &bContinuar, tamanhoBotao);
	}
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bRanking, tamanhoBotao);
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bSair, tamanhoBotao);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i position = sf::Mouse::getPosition(window);
		if (verificaClique(position, bJogar))
		{
			return 1;
		}
		if (verificaClique(position, bPlayer2))
		{
			return 2;
		}
		if (verificaClique(position, bRanking))
		{
			return 3;
		}
		if (verificaClique(position, bSair))
		{
			return 4;
		}
		if (geraContinuePrincipal)
		{
			if (verificaClique(position, bContinuar))
			{
				return 18;
			}
		}
	}
	return 0;
}

bool Menu::verificaClique(sf::Vector2i position, sf::RectangleShape button)
{
	try
	{
		if (position.x >= (button.getPosition().x - button.getSize().x / 2) && position.x <= (button.getPosition().x + button.getSize().x / 2))
		{
			if (position.y >= (button.getPosition().y - button.getSize().y / 2) && position.y <= (button.getPosition().y + button.getSize().y / 2))
			{
				return true;
			}
		}
		return false;

	}
	catch (int err_code)
	{
		printf("ERRO: Código%s", err_code);
		return false;
	}
}

int Menu::getFaseEscolhida(sf::RenderWindow & window)
{
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bFase1, sf::Vector2f(300.0f, 150.0f));
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bFase2, sf::Vector2f(300.0f, 150.0f));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i position = sf::Mouse::getPosition(window);

		if (verificaClique(position, bFase1))
		{
			return 11;
		}
		else if (verificaClique(position, bFase2))
		{
			return 12;
		}

	}
	return 13;
}

int Menu::getBotaoClicadoMenuPause(sf::RenderWindow & window)
{
	if (geraContinuePrincipal)
	{
		verificaEmCimaBotao(sf::Mouse::getPosition(window), &bContinuar, tamanhoBotao);
	}
	
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bRestart, tamanhoBotao);
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bMenuInicial, tamanhoBotao);
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bSalvarJogo, tamanhoBotao);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i position = sf::Mouse::getPosition(window);
	
		if (verificaClique(position, bContinuar))
		{
			return 5;
		}
		
		if (verificaClique(position, bRestart))
		{
			return 6;
		}
		if (verificaClique(position, bMenuInicial))
		{
			return 8;
		}
		if (verificaClique(position, bSalvarJogo))
		{
			return 17;
		}
	}
	return 7;
}

int Menu::getBotaoClicadoJogoAcabado(sf::RenderWindow & window)
{
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bSalvar, tamanhoBotao);
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bRestart, tamanhoBotao);
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bRanking, tamanhoBotao);
	verificaEmCimaBotao(sf::Mouse::getPosition(window), &bMenuInicial, tamanhoBotao);


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i position = sf::Mouse::getPosition(window);
		
		if (verificaClique(position, bSalvar))
		{
			return 10;
		}
		if (verificaClique(position, bRestart))
		{
			return 6;
		}
		if (verificaClique(position, bRanking))
		{
			return 3;
		}
		if (verificaClique(position, bMenuInicial))
		{
			return 8;
		}
	}
	return 9;
}

void Menu::inicializar()
{
	jogar.loadFromFile("imagens/singleplayer.jpeg");
	play2.loadFromFile("imagens/player2.png");
	ranking.loadFromFile("imagens/ranking.png");
	sair.loadFromFile("imagens/sair.png");
	bg.loadFromFile("imagens/bgMenuInicial.png");
	continuar.loadFromFile("imagens/continue.png");
	restart.loadFromFile("imagens/restart.png");
	bgPause.loadFromFile("imagens/bgPause.jpg");
	menuInicial.loadFromFile("imagens/menu.png");
	salvar.loadFromFile("imagens/salvar.png");
	bgAcabado.loadFromFile("imagens/bgAcabado.jpg");
	fase1.loadFromFile("imagens/fase1.png");
	fase2.loadFromFile("imagens/fase2.png");
	bgRanking.loadFromFile("imagens/bgRanking.png");
	salvarJogo.loadFromFile("imagens/salvarjogo.jpeg");
	tamanhoBotao.x = 200;
	tamanhoBotao.y = 100;

	bBg.setSize(sf::Vector2f(600.0f, 600.0f));
	bBg.setPosition(sf::Vector2f(0.0f, 0.0f));
	bBg.setTexture(&bg);

	bBgRanking.setSize(sf::Vector2f(600.0f, 600.0f));
	bBgRanking.setPosition(sf::Vector2f(0.0f, 0.0f));
	bBgRanking.setTexture(&bgRanking);

	bBgPause.setSize(sf::Vector2f(600.0f, 600.0f));
	bBgPause.setPosition(sf::Vector2f(0.0f, 0.0f));
	bBgPause.setTexture(&bgPause);

	bFase1.setSize(sf::Vector2f(300.0f, 150.0f));
	bFase1.setOrigin(bFase1.getSize() / 2.0f);
	bFase1.setPosition(sf::Vector2f(350.0f, 200.0f));
	bFase1.setTexture(&fase1);

	bFase2.setSize(sf::Vector2f(300.0f, 150.0f));
	bFase2.setOrigin(bFase2.getSize() / 2.0f);
	bFase2.setPosition(sf::Vector2f(350.0f, 400.0f));
	bFase2.setTexture(&fase2);

	bBgAcabado.setSize(sf::Vector2f(600.0f, 600.0f));
	bBgAcabado.setPosition(sf::Vector2f(0.0f, 0.0f));
	bBgAcabado.setTexture(&bgAcabado);

	bJogar.setSize(tamanhoBotao);
	bJogar.setOrigin(bJogar.getSize() / 2.0f);
	bJogar.setPosition(sf::Vector2f(120.0f, 120.0f));
	bJogar.setTexture(&jogar);

	bSalvar.setSize(tamanhoBotao);
	bSalvar.setOrigin(bSalvar.getSize() / 2.0f);
	bSalvar.setPosition(sf::Vector2f(120.0f, 120.0f));
	bSalvar.setTexture(&salvar);

	bContinuar.setSize(tamanhoBotao);
	bContinuar.setOrigin(bContinuar.getSize() / 2.0f);
	bContinuar.setPosition(sf::Vector2f(360.0f, 480.0f));
	bContinuar.setTexture(&continuar);

	bPlayer2.setSize(tamanhoBotao);
	bPlayer2.setOrigin(bPlayer2.getSize() / 2.0f);
	bPlayer2.setPosition(sf::Vector2f(120.0f, 240.0f));
	bPlayer2.setTexture(&play2);

	bRestart.setSize(tamanhoBotao);
	bRestart.setOrigin(bRestart.getSize() / 2.0f);
	bRestart.setPosition(sf::Vector2f(120.0f, 240.0f));
	bRestart.setTexture(&restart);

	bRanking.setSize(tamanhoBotao);
	bRanking.setOrigin(bRanking.getSize() / 2.0f);
	bRanking.setPosition(sf::Vector2f(120.0f, 360.0f));
	bRanking.setTexture(&ranking);

	bSair.setSize(tamanhoBotao);
	bSair.setOrigin(bSair.getSize() / 2.0f);
	bSair.setPosition(sf::Vector2f(120.0f, 480.0f));
	bSair.setTexture(&sair);

	bMenuInicial.setSize(tamanhoBotao);
	bMenuInicial.setOrigin(bMenuInicial.getSize() / 2.0f);
	bMenuInicial.setPosition(sf::Vector2f(120.0f, 480.0f));
	bMenuInicial.setTexture(&menuInicial);

	bSalvarJogo.setSize(tamanhoBotao);
	bSalvarJogo.setOrigin(bSalvar.getSize() / 2.0f);
	bSalvarJogo.setPosition(sf::Vector2f(120.0f, 120.0f));
	bSalvarJogo.setTexture(&salvarJogo);


}

void Menu::verificaEmCimaBotao(sf::Vector2i pos, sf::RectangleShape* button, sf::Vector2f posPadrao)
{
	if (verificaClique(pos, *button))
	{
		button->setSize(posPadrao * 1.1f);
	}
	else
	{
		button->setSize(posPadrao);
	}
}

sf::RectangleShape Menu::drawButtonMenuInicial(sf::RenderWindow & window)
{
	window.clear();
	window.draw(bBgRanking);
	return bMenuInicial;
}

void Menu::setGeraContinue(bool ne)
{
	geraContinuePrincipal = ne;
}
