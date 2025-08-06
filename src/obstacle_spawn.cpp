#include "obstacle_spawn.h"

void ObstacleSpawn::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_obstacleScene"), &ObstacleSpawn::get_obstacleScene);
	ClassDB::bind_method(D_METHOD("set_obstacleScene", "scene"), &ObstacleSpawn::set_obstacleScene);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Obstacle Scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_obstacleScene", "get_obstacleScene");
}

ObstacleSpawn::ObstacleSpawn()
{
	RandomNumberGenerator* rng = memnew(RandomNumberGenerator);
	rng->randomize();
	if (rng->randf() < 0.33f)
	{
		Node* scene = obstacleScene->instantiate();
		Node3D* positionNode = memnew(Node3D);
		get_tree()->get_current_scene()->add_child(positionNode);
		positionNode->add_child(scene);
		positionNode->set_global_position(get_global_position());
		memdelete(rng);
		queue_free();
	}
}

Ref<PackedScene> ObstacleSpawn::get_obstacleScene() const
{
	return obstacleScene;
}
void ObstacleSpawn::set_obstacleScene(Ref<PackedScene> scene)
{
	obstacleScene = scene;
}
