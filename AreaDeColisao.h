#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class AreaDeColisao
{
public:
	AreaDeColisao(sf::RectangleShape& body, bool principalE = false);
	~AreaDeColisao();
	void move(float dx, float dy);
	bool getPrincipal();
	bool checkColisao(AreaDeColisao& objeto,sf::Vector2f& direçao, float empurra);
	sf::Vector2f getPosition() const;
	void setHalfSize(sf::Vector2f half);
	sf::RectangleShape getBody();
	sf::Vector2f getHalfSize();
	sf::Vector2f calcHalfSize();
	
private:
	sf::Vector2f sizeHalf;
	sf::RectangleShape& body;
	bool principal;

};

