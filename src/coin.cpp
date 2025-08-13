#include "coin.h"

void Coin::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_coinArea", "ref"), &Coin::set_coinArea);
	ClassDB::bind_method(D_METHOD("get_coinArea"), &Coin::get_coinArea);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Coin Area", PROPERTY_HINT_NODE_TYPE, "Area3D"), "set_coinArea", "get_coinArea");

	ClassDB::bind_method(D_METHOD("set_particleScene", "scene"), &Coin::set_particleScene);
	ClassDB::bind_method(D_METHOD("get_particleScene"), &Coin::get_particleScene);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Particles Scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_particleScene", "get_particleScene");
}

void Coin::_ready()
{
	manager = get_tree()->get_current_scene()->get_node<CoinManager>("%CoinManager");
}

void Coin::_physics_process(double delta)
{
	if (coinArea != nullptr)
	{
		if (coinArea->get_overlapping_bodies().size() > 0) //if something is in our area
		{
			if (manager != nullptr)
				manager->add_coin();
			else
				print_line("failed to add coin!");
			if (&particleScene != nullptr)
			{
				Node3D* scene = (Node3D*)particleScene->instantiate();
				get_parent()->add_child(scene);
				scene->set_position(get_position());
				((GPUParticles3D*)scene->get_child(0))->set_emitting(true);
			}
			queue_free(); //delete ourselves
		}
	}
}

//getters and setters
void Coin::set_coinArea(Area3D* ref)
{
	coinArea = ref;
}
Area3D* Coin::get_coinArea()
{
	return coinArea;
}

Ref<PackedScene> Coin::get_particleScene()
{
	return particleScene;
}

void Coin::set_particleScene(Ref<PackedScene> scene)
{
	particleScene = scene;
}
