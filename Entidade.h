#pragma once
#include <SFML/Graphics.hpp>
#include "AreaDeColisao.h"
#include "Animador.h"

class Entidade
{
public:
	Entidade(sf::Texture* texture, sf::Vector2f position, sf::Vector2f tamanho, bool principal = false);
	virtual ~Entidade();
	virtual void draw(sf::RenderWindow& window);
	AreaDeColisao getColisor();
	sf::Vector2f getPosition() const;
	void setPostition(sf::Vector2f pos);
protected:
	sf::RectangleShape body;
	AreaDeColisao colisor;
};

