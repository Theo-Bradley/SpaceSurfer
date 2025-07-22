#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "player_movement.h"
#include "player.h"

using namespace godot;

class GameManager : public Node {
	GDCLASS(GameManager, Node)

protected:
	static void _bind_methods();

public:
	GameManager() = default;
	~GameManager() override = default;

	void _ready();
	void _physics_process(double delta);

	void StartGame();
	void PauseGame();
	void FinishGame();

	float elapsedTime = 0.f;
	int score = 0;

	PlayerMovement* playerMovement;
	RigidBody3D* playerRigidBody;

	float doubleTime = 0.f;
	float get_doubleTime();
	void set_doubleTime(float time);

	float maxSpeedMultiplier = 0.0f;
	float get_maxSpeedMultiplier();
	void set_maxSpeedMultiplier(float max);

	int scoreMultiplier = 0;
	int get_scoreMultiplier();
	void set_score_multiplier(int mult);
};
