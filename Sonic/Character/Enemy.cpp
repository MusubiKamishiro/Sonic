#include "Enemy.h"
#include "Player.h"


Enemy::Enemy(Camera& camera, Player& player) : Actor(camera), player(player)
{
}


Enemy::~Enemy()
{
}
