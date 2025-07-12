#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/node3d.hpp"

using namespace godot;

class GameManager : public Node {
	GDCLASS(GameManager, Node)

protected:
	static void _bind_methods();

public:
	GameManager() = default;
	~GameManager() override = default;

	void StartGame();
	void PauseGame();
	void FinishGame();
};
