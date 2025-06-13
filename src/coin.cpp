#include "coin.h"

void Coin::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_coinArea", "ref"), &Coin::set_coinArea);
	ClassDB::bind_method(D_METHOD("get_coinArea"), &Coin::get_coinArea);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Coin Area", PROPERTY_HINT_NODE_TYPE, "Area3D"), "set_coinArea", "get_coinArea");
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
			get_parent()->queue_free(); //delete ourselves
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
