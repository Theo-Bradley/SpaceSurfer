#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/node3d.hpp"

using namespace godot;

class Player : public Node3D {
	GDCLASS(Player, Node3D)

protected:
	static void _bind_methods();

	bool invincible = false;

public:
	Player() = default;
	~Player() override = default;

	void Hit();
};
