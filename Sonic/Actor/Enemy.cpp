#include "Enemy.h"
#include "Player.h"


Enemy::Enemy(Camera& camera, Player& player, Vector2f& pos) : Actor(camera), player(player)
{
}


Enemy::~Enemy()
{
}
