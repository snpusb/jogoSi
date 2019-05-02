#pragma once
#include "Animador.h"
#include "Entidade.h"
class Personagem: public Entidade
{
protected:
	int vidas;
	Animador animation;
	unsigned int row;
	float speed;
	static const float gravidade;
	bool faceRight;
	sf::Vector2f velocidade;
public:
	Personagem(int vi, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f size, bool principal = false);
	virtual ~Personagem();
	virtual void mover() = 0 ;
	virtual void update(float deltatime) = 0;
	void setVida(const int vi);
	const unsigned int getVidas() const;
	static const float getGravidade();
};

