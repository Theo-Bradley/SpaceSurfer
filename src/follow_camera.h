#pragma once

#include "godot_cpp/classes/camera3d.hpp"
#include "godot_cpp/classes/rigid_body3d.hpp"
#include "godot_cpp/classes/rendering_server.hpp"

using namespace godot;

class FollowCamera : public Camera3D {
	GDCLASS(FollowCamera, Camera3D)

protected:
	static void _bind_methods();

public:
	FollowCamera() = default;
	~FollowCamera() override = default;

	void _process(double delta) override;

	RigidBody3D* playerRigidBody = nullptr;
	RigidBody3D* get_playerRigidBody() const;
	void set_playerRigidBody(RigidBody3D* ref);

	Vector3 cameraOffset;
	Vector3 get_cameraOffset() const;
	void set_cameraOffset(Vector3 offset);
};
