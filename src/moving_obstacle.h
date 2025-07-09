#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/area3d.hpp"
#include "godot_cpp/classes/scene_tree.hpp"

using namespace godot;

class MovingObstacle : public Node3D {
	GDCLASS(MovingObstacle, Node3D)

protected:
	static void _bind_methods();

public:
	MovingObstacle() = default;
	~MovingObstacle() override = default;

	void _physics_process(double delta);
	void _ready();

	Area3D* collider = nullptr;
	Area3D* get_collider();
	void set_collider(Area3D* ref);
};
