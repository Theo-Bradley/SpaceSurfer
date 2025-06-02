#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/input.hpp"
#include "godot_cpp/classes/rigid_body3d.hpp"
#include "godot_cpp/classes/physics_direct_body_state3d.hpp"
///#include "godot_cpp/core/math.hpp"

using namespace godot;

class PlayerMovement : public Node3D {
	GDCLASS(PlayerMovement, Node3D)

protected:
	static void _bind_methods();

	enum MovementDirection
	{
		None,
		Left,
		Right
	};

	MovementDirection moveDirection;

public:
	PlayerMovement();
	~PlayerMovement();

	RigidBody3D* playerRigidBody = nullptr;
	void set_playerRigidBody(RigidBody3D* ref);
	RigidBody3D* get_playerRigidBody() const;

	float jumpForce = 0.0f;
	void set_jumpForce(float force);
	float get_jumpForce() const;

	float moveSpeed = 0.0f;
	void set_moveSpeed(float speed);
	float get_moveSpeed() const;

	float laneWidth = 0.0f;
	void set_laneWidth(float width);
	float get_laneWidth() const;

	float easingStart = 0.0f;
	void set_easingStart(float start);
	float get_easingStart() const;

	float movementStop = 0.0f;
	void set_movementStop(float stop);
	float get_movementStop() const;

	int desiredLane = 1;
	int currentLane = 1;
	void ChangeDesiredLane(MovementDirection dir);

	void _process(double delta) override;
	void _physics_process(double delta) override;
};
