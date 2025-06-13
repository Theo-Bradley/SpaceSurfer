#include "spawn_node.h"

void SpawnNode::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_spawnDistance"), &SpawnNode::get_spawnDistance);
	ClassDB::bind_method(D_METHOD("set_spawnDistance", "distance"), &SpawnNode::set_spawnDistance);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Spawn Distance"), "set_spawnDistance", "get_spawnDistance");

	ClassDB::bind_method(D_METHOD("get_despawnDistance"), &SpawnNode::get_despawnDistance);
	ClassDB::bind_method(D_METHOD("set_despawnDistance", "distance"), &SpawnNode::set_despawnDistance);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Despawn Distance"), "set_despawnDistance", "get_despawnDistance");

	ClassDB::bind_method(D_METHOD("get_rootNode"), &SpawnNode::get_rootNode);
	ClassDB::bind_method(D_METHOD("set_rootNode", "node"), &SpawnNode::set_rootNode);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Root Node", PROPERTY_HINT_NODE_TYPE, "Node"), "set_rootNode", "get_rootNode");
}

SpawnNode::SpawnNode()
{
	Ref<Resource> res = (ResourceLoader::get_singleton()->load("res://scenes.json"));
	if (res != nullptr)
	{
		Ref<JSON> resJSON = (Ref<JSON>)res;
		numScenes = (int)resJSON->get_data();
	}
	rng = memnew(RandomNumberGenerator);
}

SpawnNode::~SpawnNode()
{
	memdelete(rng);
}

void SpawnNode::_physics_process(double delta)
{
	if (!hasSpawned)
	{
		if (get_global_position().z > -spawnDistance) //> - because objects move +z towards camera from -z and we using position not length
		{
			spawnNewTree();
		}
	}

	if (get_global_position().z > despawnDistance) //we are not getting the actual distance here or above as the player is at 0, 0, 0
	{
		if (rootNode != nullptr)
			rootNode->queue_free();
	}
}

void SpawnNode::spawnNewTree()
{
	if (numScenes > 0)
	{
		int sceneNum = rng->randi_range(1, numScenes);
		String path = String("res://Scenes/") + String(std::to_string(sceneNum).c_str()) + String(".tscn");
		Node* scene = ((Ref<PackedScene>)ResourceLoader::get_singleton()->load(path))->instantiate();
		Node3D* positionNode = memnew(Node3D);
		get_tree()->get_current_scene()->add_child(positionNode);
		positionNode->add_child(scene);
		positionNode->set_global_position(get_global_position());
		hasSpawned = true;
	}
	else
		print_line("Failed to spawn scene! numScenes < 1");
}

//getters and setters
void SpawnNode::set_spawnDistance(float distance)
{
	spawnDistance = distance;
}

float SpawnNode::get_spawnDistance()
{
	return spawnDistance;
}

void SpawnNode::set_despawnDistance(float distance)
{
	despawnDistance = distance;
}

float SpawnNode::get_despawnDistance()
{
	return despawnDistance;
}

Node* SpawnNode::get_rootNode()
{
	return rootNode;
}
void SpawnNode::set_rootNode(Node* node)
{
	rootNode = node;
}
