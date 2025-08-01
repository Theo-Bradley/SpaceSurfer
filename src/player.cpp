#include "player.h"

void Player::_bind_methods()
{
	//bind property gets and sets
	ClassDB::bind_method(D_METHOD("set_stumbleCooldown", "time"), &Player::set_stumbleCooldown);
	ClassDB::bind_method(D_METHOD("get_stumbleCooldown"), &Player::get_stumbleCooldown);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Stumble Cooldown"), "set_stumbleCooldown", "get_stumbleCooldown");

	ADD_SIGNAL(MethodInfo("player_dead"));
}

void Player::_ready()
{
	playerMovement = (PlayerMovement*)get_child(1)->get_child(1);
}

void Player::Hit()
{
	if (!invincible)
	{
		Die();
	}
}

void Player::Stumble(String path)
{
	if (!invincible)
	{
		if (path != lastPath) //if this wasn't the same collider we hit last time
		{
			stumbling = true;
			justStumbled = true;
		}
		lastPath = path;
	}
}

void Player::Die()
{
	if (alive)
	{
		//((CollisionShape3D*)get_child(1)->get_child(0))->set_disabled(true);
		//((RigidBody3D*)get_child(1))->set_gravity_scale(0.0f);
		((PlayerMovement*)get_child(1)->get_child(1))->shouldMove = false;
		emit_signal("player_dead");
		print_line("die");
	}
	alive = false;
}

void Player::_process(double delta)
{
	if (stumbling)
	{
		stumbleTime += delta;
		if (stumbleTime >= stumbleCooldown)
		{
			stumbling = false;
			stumbleTime = 0.0f;
		}
		if (justStumbled && wasStumbled)
		{
			Die();
		}
	}

	wasStumbled = stumbling;
	justStumbled = false;
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
