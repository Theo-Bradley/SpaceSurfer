#include "follow_floor.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void FollowFloor::_bind_methods()
{
	//expose property in inspector
	ClassDB::bind_method(D_METHOD("get_yOffset"), &FollowFloor::get_yOffset); //add getters and setters to classdb
	ClassDB::bind_method(D_METHOD("set_yOffset", "val"), &FollowFloor::set_yOffset);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Y Offset"), "set_yOffset", "get_yOffset");
}

void FollowFloor::_ready()
{
	playerRigidBody = (RigidBody3D*)get_tree()->get_current_scene()->get_node<Node3D>("%Player")->get_child(1);
}

void FollowFloor::_process(double delta)
{
	if (playerRigidBody != nullptr)
	{
		Vector3 pos = playerRigidBody->get_global_position();
		pos.y = yOffset;
		set_global_position(pos);
	}
}

//getters and setters
float FollowFloor::get_yOffset()
{
	return yOffset;
}
void FollowFloor::set_yOffset(float val)
{
	yOffset = val;
}
