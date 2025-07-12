#include "moving_obstacle.h"

void MovingObstacle::_bind_methods()
{
	//bind property gets and sets
	ClassDB::bind_method(D_METHOD("set_collider", "ref"), &MovingObstacle::set_collider);
	ClassDB::bind_method(D_METHOD("get_collider"), &MovingObstacle::get_collider);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Collider", PROPERTY_HINT_NODE_TYPE, "Area3D"), "set_collider", "get_collider");
}

void MovingObstacle::_ready()
{
	player = get_tree()->get_current_scene()->get_node<Player>("%Player");
}

void MovingObstacle::_physics_process(double delta)
{
	if (collider != nullptr)
	{
		if (collider->get_overlapping_bodies().size() > 0)
		{
			for (int i = 0; i < collider->get_overlapping_bodies().size(); i++)
			{
				if (player != nullptr)
				{
					player->Hit();
				}
			}
		}
	}
}

Area3D* MovingObstacle::get_collider()
{
	return collider;
}

void MovingObstacle::set_collider(Area3D* ref)
{
	collider = ref;
}
