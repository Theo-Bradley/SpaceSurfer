#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/node3d.hpp"

using namespace godot;

class MovingObject : public Node3D {
	GDCLASS(MovingObject, Node3D)

protected:
	static void _bind_methods();

public:
	MovingObject();
	~MovingObject() override = default;

	void _process(double delta);

	float offset = 0.0f;
	void set_offset(float off);
	float get_offset();
};
