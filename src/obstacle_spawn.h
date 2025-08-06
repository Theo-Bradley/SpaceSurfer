#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
#include "godot_cpp/classes/random_number_generator.hpp"
#include "godot_cpp/classes/scene_tree.hpp"

using namespace godot;

class ObstacleSpawn : public Node3D {
	GDCLASS(ObstacleSpawn, Node3D)

protected:
	static void _bind_methods();

public:
	ObstacleSpawn();
	~ObstacleSpawn() override = default;

	Ref<PackedScene> obstacleScene = nullptr;
	Ref<PackedScene> get_obstacleScene() const;
	void set_obstacleScene(Ref<PackedScene> scene);
};
