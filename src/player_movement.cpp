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

	ClassDB::bind_method(D_METHOD("get_moveSpeed"), &PlayerMovement::get_moveSpeed);
	ClassDB::bind_method(D_METHOD("set_moveSpeed", "speed"), &PlayerMovement::set_moveSpeed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Move Speed"), "set_moveSpeed", "get_moveSpeed");

	ClassDB::bind_method(D_METHOD("get_laneWidth"), &PlayerMovement::get_laneWidth);
	ClassDB::bind_method(D_METHOD("set_laneWidth", "width"), &PlayerMovement::set_laneWidth);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Lane Width"), "set_laneWidth", "get_laneWidth");
	
	ClassDB::bind_method(D_METHOD("get_easingStart"), &PlayerMovement::get_easingStart);
	ClassDB::bind_method(D_METHOD("set_easingStart", "start"), &PlayerMovement::set_easingStart);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Easing Start"), "set_easingStart", "get_easingStart");

	ClassDB::bind_method(D_METHOD("get_movementStop"), &PlayerMovement::get_movementStop);
	ClassDB::bind_method(D_METHOD("set_movementStop", "stop"), &PlayerMovement::set_movementStop);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Movement Stop"), "set_movementStop", "get_movementStop");
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
	if (input->is_action_just_pressed("Jump"))
	{
		print_line("jumping");
		playerRigidBody->apply_central_impulse(Vector3(0.f, jumpForce * playerRigidBody->get_mass(), 0.f));
	}
	if (input->is_action_just_pressed("Left"))
	{
		moveDirection = Left;
	}
	if (input->is_action_just_pressed("Right"))
	{
		moveDirection = Right;
	}
}

void PlayerMovement::_physics_process(double delta)
{
	int change = moveDirection == Left ? -1 : 1;
	if (moveDirection == None)
		change = 0;
	int lane = moveDirection == Left ? 0 : 1;
	float dist = Math::absf(lane * laneWidth - playerRigidBody->get_global_position().x);
	float easing = fminf(powf(dist * powf(easingStart, -1.f), 0.5f), 1.0f); //y = min((x*a)^(1/2)) where x is distance between player and lane and 1/a is the start of easing
	float v = moveSpeed * easing * change;
	float u = playerRigidBody->get_linear_velocity().x;
	playerRigidBody->apply_central_impulse(Vector3((v - u) * playerRigidBody->get_mass(), 0.f, 0.f));
	if (easing <= movementStop)
		moveDirection = None;
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

void PlayerMovement::set_easingStart(float start)
{
	easingStart = start;
}
float PlayerMovement::get_easingStart() const
{
	return easingStart;
}

void PlayerMovement::set_movementStop(float stop)
{
	movementStop = stop;
}

float PlayerMovement::get_movementStop() const
{
	return movementStop;
}
