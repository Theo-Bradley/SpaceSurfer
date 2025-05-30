#include "player_movement.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void PlayerMovement::_bind_methods()
{
	//expose playerRigidBody in inspector
	ClassDB::bind_method(D_METHOD("get_playerRigidBody"), &PlayerMovement::get_playerRigidBody); //add getters and setters to classdb
	ClassDB::bind_method(D_METHOD("set_playerRigidBody", "ref"), &PlayerMovement::set_playerRigidBody);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Player Rigid Body", PROPERTY_HINT_NODE_TYPE, "RigidBody3D"), "set_playerRigidBody", "get_playerRigidBody");

	ClassDB::bind_method(D_METHOD("get_jumpForce"), &PlayerMovement::get_jumpForce); //add getters and setters to classdb
	ClassDB::bind_method(D_METHOD("set_jumpForce", "force"), &PlayerMovement::set_jumpForce);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Jump Impulse"), "set_jumpForce", "get_jumpForce");
}

PlayerMovement::PlayerMovement()
{
	// Initialize any variables here.
}

PlayerMovement::~PlayerMovement()
{
	// Add your cleanup here.
}

void PlayerMovement::_process(double delta)
{
	if (Input::get_singleton()->is_action_just_pressed("Jump"))
	{
		print_line("jumping");
		playerRigidBody->apply_central_impulse(Vector3(0.f, jumpForce, 0.f));
	}
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
