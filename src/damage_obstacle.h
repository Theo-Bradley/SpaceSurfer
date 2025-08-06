#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/area3d.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "player.h"

using namespace godot;

class DamageObstacle : public Node3D {
	GDCLASS(DamageObstacle, Node3D)

protected:
	static void _bind_methods();

public:
	DamageObstacle() = default;
	~DamageObstacle() override = default;

	void _ready();
	void _physics_process(double delta);

	Area3D* area = nullptr;
	Area3D* get_area() const;
	void set_area(Area3D* ref);

	Player* player = nullptr;
};
