#include "floor_spawn.h"

void FloorSpawn::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_spawnDistance"), &FloorSpawn::get_spawnDistance);
	ClassDB::bind_method(D_METHOD("set_spawnDistance", "distance"), &FloorSpawn::set_spawnDistance);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Spawn Distance"), "set_spawnDistance", "get_spawnDistance");

	ClassDB::bind_method(D_METHOD("get_despawnDistance"), &FloorSpawn::get_despawnDistance);
	ClassDB::bind_method(D_METHOD("set_despawnDistance", "distance"), &FloorSpawn::set_despawnDistance);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Despawn Distance"), "set_despawnDistance", "get_despawnDistance");

	ClassDB::bind_method(D_METHOD("get_rootNode"), &FloorSpawn::get_rootNode);
	ClassDB::bind_method(D_METHOD("set_rootNode", "node"), &FloorSpawn::set_rootNode);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Root Node", PROPERTY_HINT_NODE_TYPE, "Node"), "set_rootNode", "get_rootNode");

	ClassDB::bind_method(D_METHOD("get_packedScene"), &FloorSpawn::get_packedScene);
	ClassDB::bind_method(D_METHOD("set_packedScene", "scene"), &FloorSpawn::set_packedScene);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "Mesh Scene Path"), "set_packedScene", "get_packedScene");
}

void FloorSpawn::_ready()
{
	player = get_tree()->get_current_scene()->get_node<Player>("%Player");
}

void FloorSpawn::_physics_process(double delta)
{
	if (player != nullptr)
	{
		float playerPos = ((Node3D*)player->get_child(1))->get_global_position().z;

		if (get_global_position().z - playerPos > -spawnDistance) //> - because objects move +z towards camera from -z and we using position not length
		{
			spawnNewTree();
		}

		if (get_global_position().z - playerPos > despawnDistance) //we are not getting the actual distance here or above as the player is at 0, 0, 0
		{
			if (rootNode != nullptr)
				rootNode->queue_free();
		}
	}
}

void FloorSpawn::spawnNewTree()
{
	if (!hasSpawned)
	{
		Ref<PackedScene> packedScene = ResourceLoader::get_singleton()->load(meshScenePath);
		Node* scene = packedScene->instantiate();
		Node3D* positionNode = memnew(Node3D);
		get_tree()->get_current_scene()->add_child(positionNode);
		positionNode->add_child(scene);
		positionNode->set_global_position(get_global_position());
		hasSpawned = true;
	}
}

//getters and setters
void FloorSpawn::set_spawnDistance(float distance)
{
	spawnDistance = distance;
}

float FloorSpawn::get_spawnDistance()
{
	return spawnDistance;
}

void FloorSpawn::set_despawnDistance(float distance)
{
	despawnDistance = distance;
}

float FloorSpawn::get_despawnDistance()
{
	return despawnDistance;
}

Node* FloorSpawn::get_rootNode()
{
	return rootNode;
}
void FloorSpawn::set_rootNode(Node* node)
{
	rootNode = node;
}

void FloorSpawn::set_packedScene(String scene)
{
	meshScenePath = scene;
}

String FloorSpawn::get_packedScene()
{
	return meshScenePath;
}
