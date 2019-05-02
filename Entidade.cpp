#include "Entidade.h"

Entidade::Entidade(sf::Texture * texture, sf::Vector2f position, sf::Vector2f tamanho, bool principal):
	colisor(body, principal)
{
	body.setSize(tamanho);//48 - 40
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

Entidade::~Entidade()
{
}

void Entidade::draw(sf::RenderWindow & window)
{
	window.draw(body);
}

AreaDeColisao Entidade::getColisor()
{
	return colisor;
}

sf::Vector2f Entidade::getPosition() const
{
	return body.getPosition();
}

void Entidade::setPostition(sf::Vector2f pos)
{
	body.setPosition(pos);
}
