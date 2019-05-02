#pragma once
#include"Obstaculo.h"

class Serra:public Obstaculo
{
private:
	sf::CircleShape bodyC;
	float omega,tempo_ataque;
public:
	Serra(sf::Texture* tex, sf::Vector2f tam, sf::Vector2f pos);
	~Serra();
	void update(float deltaTime);
	void draw(sf::RenderWindow & window);
};

