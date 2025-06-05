#include "follow_camera.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void FollowCamera::_bind_methods()
{
	//expose playerRigidBody in inspector
	ClassDB::bind_method(D_METHOD("get_playerRigidBody"), &FollowCamera::get_playerRigidBody); //add getters and setters to classdb
	ClassDB::bind_method(D_METHOD("set_playerRigidBody", "ref"), &FollowCamera::set_playerRigidBody);

	//add the property by setting the getters and setters function names to the ones we added above
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Player Rigid Body", PROPERTY_HINT_NODE_TYPE, "RigidBody3D"), "set_playerRigidBody", "get_playerRigidBody");

	ClassDB::bind_method(D_METHOD("get_cameraOffset"), &FollowCamera::get_cameraOffset);
	ClassDB::bind_method(D_METHOD("set_cameraOffset", "offset"), &FollowCamera::set_cameraOffset);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "Camera Offset"), "set_cameraOffset", "get_cameraOffset");
}

void FollowCamera::_process(double delta)
{
	if (playerRigidBody != nullptr)
	{
		Vector3 pos = playerRigidBody->get_global_position();
		set_global_position(pos + cameraOffset);
	}
}

//getters and setters
RigidBody3D* FollowCamera::get_playerRigidBody() const
{
	return playerRigidBody;
}
void FollowCamera::set_playerRigidBody(RigidBody3D* ref)
{
	playerRigidBody = ref;
}

Vector3 FollowCamera::get_cameraOffset() const
{
	return cameraOffset;
}

void FollowCamera::set_cameraOffset(Vector3 offset)
{
	cameraOffset = offset;
}
