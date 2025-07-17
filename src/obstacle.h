#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/area3d.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "player.h"
#include "player_movement.h"

using namespace godot;

class Obstacle : public Node3D {
	GDCLASS(Obstacle, Node3D)

protected:
	static void _bind_methods();

public:
	Obstacle() = default;
	~Obstacle() override = default;

	void _physics_process(double delta);
	void _ready();

	Area3D* frontCollider = nullptr;
	Area3D* get_frontCollider();
	void set_frontCollider(Area3D* ref);

	Area3D* leftCollider = nullptr;
	Area3D* get_leftCollider();
	void set_leftCollider(Area3D* ref);

	Area3D* rightCollider = nullptr;
	Area3D* get_rightCollider();
	void set_rightCollider(Area3D* ref);

	Player* player;
	PlayerMovement* playerMovement;
};
