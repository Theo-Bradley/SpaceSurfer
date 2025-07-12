#include "player.h"

void Player::_bind_methods()
{
}

void Player::Hit()
{
	if (!invincible)
	{
		print_line("Hit");
	}
}
