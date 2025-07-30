render_mode world_vertex_coords;
global uniform float zFalloff = 1.0;
global uniform highp vec3 camPos;
global uniform float zFalloffStrength;

void Curve(inout vec3 VERT)
{
	//VERT.y -= smoothstep(2.0, 100.0, pow(abs(VERT.z - camPos.z) / zFalloff, zFalloffStrength)); //change height based on z position
	VERT.y -= pow(length(camPos.z - VERT.z) / zFalloff, zFalloffStrength);
}