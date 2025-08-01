#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/collision_shape3d.hpp"
#include "godot_cpp/classes/rigid_body3d.hpp"
#include "player_movement.h"

using namespace godot;

class Player : public Node3D {
	GDCLASS(Player, Node3D)

protected:
	static void _bind_methods();

	bool invincible = false;
	bool stumbling = false;
	float stumbleTime = 0.f;
	float stumbleCooldown = 0.f;
	bool justStumbled = false;
	bool wasStumbled = false;
	bool wasJustStumbled = false;
	String lastPath;

public:
	Player() = default;
	~Player() override = default;
	void _ready();
	void _process(double delta);

	void Hit();
	void Stumble(String path);
	void Die();

	float alive = true;

	float get_stumbleCooldown();
	void set_stumbleCooldown(float time);

	PlayerMovement* playerMovement;
};
