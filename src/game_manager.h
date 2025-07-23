#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/resource_saver.hpp"
#include "godot_cpp/classes/json.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/classes/progress_bar.hpp"
#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/button.hpp"
#include "player_movement.h"
#include "player.h"
#include "utils.h"

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
	void _process(double delta);

	void StartGame();
	void PauseGame();
	void FinishGame();
	bool HighScore(int score, int highScore);

	float elapsedTime = 0.f;
	int score = 0;
	int highscore = 1;
	bool paused = false;

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

	//UI Elements
	Control* UINode = nullptr;
	Control* get_UI();
	void set_UI(Control* ref);

	Label* scoreLabel = nullptr;
	Label* highscoreLabel = nullptr;
	Button* pauseButton = nullptr;
	ProgressBar* progBar = nullptr;
};
