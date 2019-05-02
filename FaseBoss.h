#pragma once
#include "Fase.h"
class FaseBoss:public Fase
{
private :
	Boss* boss;
	sf::Texture bosTex;
	sf::RectangleShape lifesBoss;
	sf::IntRect rectLifesBoss;
public:
	FaseBoss(sf::View* vie, string caminhoMapa, Player* jog, Player* jog2 = NULL);
	~FaseBoss();
	void update(float deltatime);
	void checarColisoes();
	void draw(sf::RenderWindow& window);
	bool proximaFase();
	void faseFinalizada(sf::RenderWindow& win);
};

