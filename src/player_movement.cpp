#include "player_movement.h"
#include <godot_cpp/core/class_db.hpp>

#define input Input::get_singleton()

using namespace godot;

void PlayerMovement::_bind_methods()
{
	//expose playerRigidBody in inspector
	ClassDB::bind_method(D_METHOD("get_playerRigidBody"), &PlayerMovement::get_playerRigidBody); //add getters and setters to classdb
	ClassDB::bind_method(D_METHOD("set_playerRigidBody", "ref"), &PlayerMovement::set_playerRigidBody);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Player Rigid Body", PROPERTY_HINT_NODE_TYPE, "RigidBody3D"), "set_playerRigidBody", "get_playerRigidBody");

	//..
	ClassDB::bind_method(D_METHOD("get_jumpForce"), &PlayerMovement::get_jumpForce);
	ClassDB::bind_method(D_METHOD("set_jumpForce", "force"), &PlayerMovement::set_jumpForce);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Jump Impulse"), "set_jumpForce", "get_jumpForce");

	ClassDB::bind_method(D_METHOD("get_fallingForce"), &PlayerMovement::get_fallingForce);
	ClassDB::bind_method(D_METHOD("set_fallingForce", "stop"), &PlayerMovement::set_fallingForce);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Falling Force"), "set_fallingForce", "get_fallingForce");

	ClassDB::bind_method(D_METHOD("get_moveSpeed"), &PlayerMovement::get_moveSpeed);
	ClassDB::bind_method(D_METHOD("set_moveSpeed", "speed"), &PlayerMovement::set_moveSpeed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Move Speed"), "set_moveSpeed", "get_moveSpeed");

	ClassDB::bind_method(D_METHOD("get_runSpeed"), &PlayerMovement::get_runSpeed);
	ClassDB::bind_method(D_METHOD("set_runSpeed", "speed"), &PlayerMovement::set_runSpeed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Run Speed"), "set_runSpeed", "get_runSpeed");

	ClassDB::bind_method(D_METHOD("get_laneWidth"), &PlayerMovement::get_laneWidth);
	ClassDB::bind_method(D_METHOD("set_laneWidth", "width"), &PlayerMovement::set_laneWidth);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Lane Width"), "set_laneWidth", "get_laneWidth");
}

PlayerMovement::PlayerMovement()
{
	// Initialize any variables here.
	moveDirection = None;
}

PlayerMovement::~PlayerMovement()
{
	// Add your cleanup here.
}

void PlayerMovement::_process(double delta)
{
	if (input->is_action_pressed("Jump"))
	{
		isJumping = true;
		isFalling = false;
	}
	if (input->is_action_pressed("Jump") == false)
	{
		isFalling = true;
	}
	if (input->is_action_just_pressed("Left"))
	{
		moveDirection = Left;
		ChangeDesiredLane(moveDirection);
	}
	if (input->is_action_just_pressed("Right"))
	{
		moveDirection = Right;
		ChangeDesiredLane(moveDirection);
	}
}

void PlayerMovement::_physics_process(double delta)
{
	print_line(playerRigidBody->get_global_position().x);
	//lane changing code:
	int change = moveDirection == Left ? -1 : 1;
	if (moveDirection == None || (moveDirection == Left && currentLane == 0) || (moveDirection == Right && currentLane == 2)) //dont move if we are on edge lanes
		change = 0;
	float dist = Math::absf(desiredLane * laneWidth - playerRigidBody->get_global_position().x);
	//float easing = fminf(powf(dist * powf(easingStart, -1.f), 0.5f), 1.0f); //y = min((x*a)^(1/2)) where x is distance between player and lane and 1/a is the start of easing
	Vector2 v = Vector2(moveSpeed * change, runSpeed);
	Vector2 u = Vector2(playerRigidBody->get_linear_velocity().x, playerRigidBody->get_linear_velocity().z);
	playerRigidBody->apply_central_impulse(Vector3((v.x - u.x) * playerRigidBody->get_mass(), 0.f, (v.y - u.y) *playerRigidBody->get_mass()));
	if (Math::absf(desiredLane * laneWidth - playerRigidBody->get_global_position().x) <= Math::absf(playerRigidBody->get_linear_velocity().x * delta * 1.05f)
		&& moveDirection != None) //if in the correct lane: stop
	{
		print_line("stopped");
		moveDirection = None;
		currentLane = desiredLane;
		bounceBack = false;
	}
	//jumping code:
	if (isJumping == true && oldIsJumping == false) //if we just jumped
	{
		playerRigidBody->apply_central_impulse(Vector3(0.f, jumpForce * playerRigidBody->get_mass(), 0.f));
	}
	if (oldIsJumping == true && isJumping == true && playerRigidBody->get_contact_count() > 0) //detect if we are touching something
	{//if so, assume we are grounded
		isJumping = false;
	}
	if (isJumping == true && isFalling == true)
	{
		playerRigidBody->apply_central_impulse(Vector3(0.0f, fallingForce * playerRigidBody->get_mass(), 0.0f)); //add the jetpacking force
	}
	oldIsJumping = isJumping;
}

void PlayerMovement::BounceRight()
{
	if (bounceBack == false)
	{
		currentLane = desiredLane;
		moveDirection = Right;
		desiredLane++;
		bounceBack = true;
	}
}

void PlayerMovement::BounceLeft()
{
	if (bounceBack == false)
	{
		currentLane = desiredLane;
		moveDirection = Left;
		desiredLane--;
		bounceBack = true;
	}
}

void PlayerMovement::ChangeDesiredLane(MovementDirection dir)
{
	if (dir == Left && desiredLane > 0)
		desiredLane--;
	if (dir == Right && desiredLane < 2)
		desiredLane++;
}

//getters and setters for ClassDB

void PlayerMovement::set_playerRigidBody(RigidBody3D* ref)
{
	playerRigidBody = ref;
}

RigidBody3D* PlayerMovement::get_playerRigidBody() const
{
	return playerRigidBody;
}

void PlayerMovement::set_jumpForce(float force)
{
	jumpForce = force;
}

float PlayerMovement::get_jumpForce() const
{
	return jumpForce;
}

void PlayerMovement::set_moveSpeed(float speed)
{
	moveSpeed = speed;
}

float PlayerMovement::get_moveSpeed() const
{
	return moveSpeed;
}

void PlayerMovement::set_laneWidth(float width)
{
	laneWidth = width;
}
float PlayerMovement::get_laneWidth() const
{
	return laneWidth;
}

void PlayerMovement::set_fallingForce(float force)
{
	fallingForce = force;
}
float PlayerMovement::get_fallingForce()
{
	return fallingForce;
}

void PlayerMovement::set_runSpeed(float speed)
{
	runSpeed = speed;
}

float PlayerMovement::get_runSpeed()
{
	return runSpeed;
}
