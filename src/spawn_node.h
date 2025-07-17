#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "godot_cpp/classes/json.hpp"
#include "godot_cpp/classes/random_number_generator.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "player.h"

using namespace godot;

class SpawnNode : public Node3D {
	GDCLASS(SpawnNode, Node3D)

private:
	RandomNumberGenerator* rng;
	bool hasSpawned = false;

protected:
	static void _bind_methods();

public:
	SpawnNode();
	~SpawnNode();

	void _ready();
	void _physics_process(double delta);

	void spawnNewTree();

	float spawnDistance = 0.0f;
	void set_spawnDistance(float distance);
	float get_spawnDistance();

	float despawnDistance = 0.0f;
	void set_despawnDistance(float distance);
	float get_despawnDistance();

	int numScenes;

	Node* rootNode;
	Node* get_rootNode();
	void set_rootNode(Node* node);

	Player* player;
};
