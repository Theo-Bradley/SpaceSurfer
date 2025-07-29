#pragma once

#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/rigid_body3d.hpp"
#include "godot_cpp/classes/scene_tree.hpp"

using namespace godot;

class FollowFloor : public Node3D {
	GDCLASS(FollowFloor, Node3D)

protected:
	static void _bind_methods();

public:
	FollowFloor() = default;
	~FollowFloor() override = default;

	void _ready();
	void _process(double delta) override;

	RigidBody3D* playerRigidBody = nullptr;

	float yOffset = 0.0f;
	float get_yOffset();
	void set_yOffset(float val);
};
