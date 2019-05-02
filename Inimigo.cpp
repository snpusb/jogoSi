#include "Inimigo.h"

Inimigo::Inimigo(int dan , bool pos_ataqu, int vi, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position, sf::Vector2f size):
	Personagem(vi,texture,imageCount,switchTime,speed, position, size, false), dano(dan), pos_ataque(pos_ataqu)
{
}

Inimigo::~Inimigo()
{

}
