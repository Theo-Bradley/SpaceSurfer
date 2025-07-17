#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/rigid_body3d.hpp"
#include "obstacle.h"

using namespace godot;

class MovingObstacle : public Obstacle {
	GDCLASS(MovingObstacle, Obstacle)

protected:
	static void _bind_methods();

public:
	MovingObstacle() = default;
	~MovingObstacle() override = default;

	void _physics_process(double delta) override;
	void _ready();

	RigidBody3D* rigidbody = nullptr;
	RigidBody3D* get_rigidbody();
	void set_rigidbody(RigidBody3D* body);

	float moveSpeed = 0.0f;
	float get_moveSpeed();
	void set_moveSpeed(float speed);
};
