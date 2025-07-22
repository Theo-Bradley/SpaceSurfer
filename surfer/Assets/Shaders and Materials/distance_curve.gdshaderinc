render_mode world_vertex_coords;
global uniform float zFalloff = 1.0;
global uniform vec3 camPos;
global uniform float zFalloffStrength;

void Curve(inout vec3 VERT)
{
	VERT.y -= pow(abs(VERT.z - camPos.z) / zFalloff, zFalloffStrength); //change height based on z position
}