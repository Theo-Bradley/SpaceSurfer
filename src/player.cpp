#include "player.h"

void Player::_bind_methods()
{
	//bind property gets and sets
	ClassDB::bind_method(D_METHOD("set_stumbleCooldown", "time"), &Player::set_stumbleCooldown);
	ClassDB::bind_method(D_METHOD("get_stumbleCooldown"), &Player::get_stumbleCooldown);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Stumble Cooldown"), "set_stumbleCooldown", "get_stumbleCooldown");
}

void Player::Hit()
{
	if (!invincible)
	{
		print_line("Hit");
	}
}

void Player::Stumble()
{
	if (!invincible)
	{
		if (stumbleTime > 0.f) //if already stumbling
		{
			Hit(); //die
		}
		else
		{
			stumbling = true;
		}
	}
}

void Player::_process(double delta)
{
	if (stumbling)
	{
		stumbleTime += delta;
	}
	if (stumbleTime >= stumbleCooldown)
	{
		stumbling = false;
		stumbleTime = 0.f;
	}
}

//getters and setters
float Player::get_stumbleCooldown()
{
	return stumbleCooldown;
}

void Player::set_stumbleCooldown(float time)
{
	stumbleCooldown = time;
}
