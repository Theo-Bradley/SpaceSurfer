#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/rigid_body3d.hpp"

using namespace godot;

class PlayerMovement : public Node3D {
	GDCLASS(PlayerMovement, Node3D)

protected:
	static void _bind_methods();

public:
	PlayerMovement();
	~PlayerMovement();

	RigidBody3D* playerRigidBody = nullptr;
	void set_playerRigidBody(RigidBody3D* ref);
	RigidBody3D* get_playerRigidBody() const;

	float jumpForce = 0.0f;
	void set_jumpForce(float force);
	float get_jumpForce() const;

	void _process(double delta) override;
};
