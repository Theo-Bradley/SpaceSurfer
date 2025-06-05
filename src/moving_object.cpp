#include "moving_object.h"

void MovingObject::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_offset"), &MovingObject::get_offset);
	ClassDB::bind_method(D_METHOD("set_offset", "off"), &MovingObject::set_offset);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Per Frame Offset"), "set_offset", "get_offset");
}

MovingObject::MovingObject()
{
}

void MovingObject::_process(double delta)
{
	Vector3 position = get_global_position();
	set_global_position(Vector3(position.x, position.y, position.z + offset * delta));
}

void MovingObject::set_offset(float off)
{
	offset = off;
}

float MovingObject::get_offset()
{
	return offset;
}
