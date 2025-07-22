shader_type spatial;
render_mode world_vertex_coords;

uniform float xFalloff = 1.0;
uniform float zFalloff = 1.0;
global uniform vec3 camPos;
global uniform float zFalloffStrength;

void vertex() {
	// Called for every vertex the material is visible on.
	VERTEX.y -= pow(abs(VERTEX.x) / xFalloff, zFalloffStrength); //change height based on x position
	VERTEX.y -= pow(abs(VERTEX.z - camPos.z) / zFalloff, zFalloffStrength); //.. z position
}

void fragment() {
	// Called for every pixel the material is visible on.
}

//void light() {
//	// Called for every pixel for every light affecting the material.
//	// Uncomment to replace the default light processing function with this one.
//}
