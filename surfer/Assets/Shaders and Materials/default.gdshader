shader_type spatial;
render_mode world_vertex_coords;

//uniform sampler2D tex;
global uniform float zFalloff = 1.0;
global uniform vec3 camPos;
global uniform float zFalloffStrength;

void vertex() {
	// Called for every vertex the material is visible on.
	VERTEX.y -= pow(abs(VERTEX.z - camPos.z) / zFalloff, zFalloffStrength); //change height based on z position
}

void fragment() {
	// Called for every pixel the material is visible on.
	//ALBEDO = texture(tex, UV).xyz;
	ALBEDO = COLOR.xyz;
}
