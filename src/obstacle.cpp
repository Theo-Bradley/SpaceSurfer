#include "obstacle.h"

void Obstacle::_bind_methods()
{
	//bind property gets and sets
	ClassDB::bind_method(D_METHOD("set_frontCollider", "ref"), &Obstacle::set_frontCollider);
	ClassDB::bind_method(D_METHOD("get_frontCollider"), &Obstacle::get_frontCollider);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Front Collider", PROPERTY_HINT_NODE_TYPE, "Area3D"), "set_frontCollider", "get_frontCollider");

	ClassDB::bind_method(D_METHOD("set_leftCollider", "ref"), &Obstacle::set_leftCollider);
	ClassDB::bind_method(D_METHOD("get_leftCollider"), &Obstacle::get_leftCollider);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Left Collider", PROPERTY_HINT_NODE_TYPE, "Area3D"), "set_leftCollider", "get_leftCollider");
	
	ClassDB::bind_method(D_METHOD("set_rightCollider", "ref"), &Obstacle::set_rightCollider);
	ClassDB::bind_method(D_METHOD("get_rightCollider"), &Obstacle::get_rightCollider);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Right Collider", PROPERTY_HINT_NODE_TYPE, "Area3D"), "set_rightCollider", "get_rightCollider");
}

void Obstacle::_ready()
{
	player = get_tree()->get_current_scene()->get_node<Player>("%Player");
	if (player != nullptr)
		playerMovement = (PlayerMovement*)(player->get_child(1)->get_child(1));
}

void Obstacle::_physics_process(double delta)
{
	if (frontCollider != nullptr)
	{
		if (frontCollider->get_overlapping_bodies().size() > 0)
		{
			for (int i = 0; i < frontCollider->get_overlapping_bodies().size(); i++)
			{
				if (player != nullptr)
				{
					player->Hit();
				}
			}
		}
	}

	if (leftCollider != nullptr)
	{
		if (leftCollider->get_overlapping_bodies().size() > 0)
		{
			for (int i = 0; i < leftCollider->get_overlapping_bodies().size(); i++)
			{
				if (player != nullptr)
				{
					if (playerMovement != nullptr)
					{
						playerMovement->BounceLeft();
					}
					player->Stumble(get_path());
				}
			}
		}
	}

	if (rightCollider != nullptr)
	{
		if (rightCollider->get_overlapping_bodies().size() > 0)
		{
			for (int i = 0; i < rightCollider->get_overlapping_bodies().size(); i++)
			{
				if (player != nullptr)
				{
					if (playerMovement != nullptr)
					{
						playerMovement->BounceRight();
					}
					player->Stumble(get_path());
				}
			}
		}
	}
}

Area3D* Obstacle::get_frontCollider()
{
	return frontCollider;
}

void Obstacle::set_frontCollider(Area3D* ref)
{
	frontCollider = ref;
}

Area3D* Obstacle::get_leftCollider()
{
	return leftCollider;
}

void Obstacle::set_leftCollider(Area3D* ref)
{
	leftCollider = ref;
}

Area3D* Obstacle::get_rightCollider()
{
	return rightCollider;
}

void Obstacle::set_rightCollider(Area3D* ref)
{
	rightCollider = ref;
}
