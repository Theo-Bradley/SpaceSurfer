#include "damage_obstacle.h"

void DamageObstacle::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_area", "ref"), &DamageObstacle::set_area);
	ClassDB::bind_method(D_METHOD("get_area"), &DamageObstacle::get_area);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Hit Area", PROPERTY_HINT_NODE_TYPE, "Area3D"), "set_area", "get_area");
}

void DamageObstacle::_ready()
{
	player = get_tree()->get_current_scene()->get_node<Player>("%Player");
}

void DamageObstacle::_physics_process(double delta)
{
	if (area != nullptr)
	{
		if (area->get_overlapping_bodies().size() > 0) //if something is in our area
		{
			if (player != nullptr)
				player->Hit();
			print_line("Hit");
			queue_free(); //delete ourselves
		}
	}
}

Area3D* DamageObstacle::get_area() const
{
	return area;
}

void DamageObstacle::set_area(Area3D* ref)
{
	area = ref;
}
