#include "moving_obstacle.h"

void MovingObstacle::_bind_methods()
{
	//bind property gets and sets
	ClassDB::bind_method(D_METHOD("set_rigidbody", "body"), &MovingObstacle::set_rigidbody);
	ClassDB::bind_method(D_METHOD("get_rigidbody"), &MovingObstacle::get_rigidbody);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Rigidbody", PROPERTY_HINT_NODE_TYPE, "RigidBody3D"), "set_rigidbody", "get_rigidbody");

	ClassDB::bind_method(D_METHOD("set_moveSpeed", "speed"), &MovingObstacle::set_moveSpeed);
	ClassDB::bind_method(D_METHOD("get_moveSpeed"), &MovingObstacle::get_moveSpeed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "Move Speed"), "set_moveSpeed", "get_moveSpeed");
}

void MovingObstacle::_ready()
{
	Obstacle::_ready();

}

void MovingObstacle::_physics_process(double delta)
{
	Obstacle::_physics_process(delta);

	if (rigidbody != nullptr)
	{
		rigidbody->apply_central_impulse(Vector3(0.0f, 0.0f, (-moveSpeed - rigidbody->get_linear_velocity().z) * rigidbody->get_mass()));
	}
}

RigidBody3D* MovingObstacle::get_rigidbody()
{
	return rigidbody;
}

void MovingObstacle::set_rigidbody(RigidBody3D* body)
{
	rigidbody = body;
}

float MovingObstacle::get_moveSpeed()
{
	return moveSpeed;
}

void MovingObstacle::set_moveSpeed(float speed)
{
	moveSpeed = speed;
}
