#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/resource_loader.hpp"
#include "player.h"

using namespace godot;

class FloorSpawn : public Node3D {
	GDCLASS(FloorSpawn, Node3D)

private:
	bool hasSpawned = false;

protected:
	static void _bind_methods();

public:
	void _ready();
	void _physics_process(double delta);

	void spawnNewTree();

	float spawnDistance = 0.0f;
	void set_spawnDistance(float distance);
	float get_spawnDistance();

	float despawnDistance = 0.0f;
	void set_despawnDistance(float distance);
	float get_despawnDistance();

	Node* rootNode = nullptr;
	Node* get_rootNode();
	void set_rootNode(Node* node);

	Player* player = nullptr;

	String meshScenePath = "";
	void set_packedScene(String scene);
	String get_packedScene();
};
