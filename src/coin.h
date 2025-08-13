#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/area3d.hpp"
#include "godot_cpp/variant/node_path.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/gpu_particles3d.hpp"
#include "coin_manager.h"

using namespace godot;

class Coin : public Node3D {
	GDCLASS(Coin, Node3D)

private:
	CoinManager* manager;

protected:
	static void _bind_methods();

public:
	Coin() = default;
	~Coin() override = default;

	void _ready();
	void _physics_process(double delta);

	Area3D* coinArea = nullptr;
	void set_coinArea(Area3D* ref);
	Area3D* get_coinArea();

	Ref<PackedScene> particleScene = nullptr;
	Ref<PackedScene> get_particleScene();
	void set_particleScene(Ref<PackedScene> scene);
};
