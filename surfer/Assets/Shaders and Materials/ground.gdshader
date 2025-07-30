shader_type spatial;
render_mode world_vertex_coords;

uniform float xFalloff = 1.0;
uniform float xFalloffStrength = 1.70;
global uniform float zFalloff = 1.0;
uniform vec3 baseColor: source_color = vec3(1.0);
uniform vec3 stripeColor: source_color = vec3(0.2);
uniform vec3 spotColor: source_color = vec3(0.8);
uniform sampler2D baseNoise;
uniform sampler2D spotNoise;
uniform float scaling = 150.0;
uniform float spotClip = 0.8;
uniform float colorBanding = 8.0;

global uniform highp vec3 camPos;
global uniform float zFalloffStrength;

void vertex() {
	// Called for every vertex the material is visible on.
	//VERTEX.y -= smoothstep(100.0, 100.0, pow(abs(VERTEX.x) / xFalloff, xFalloffStrength)); //change height based on x position
	VERTEX.y -= pow(length(camPos.x - VERTEX.x) / xFalloff, xFalloffStrength) * 0.1;
	VERTEX.y -= pow(length(camPos.z - VERTEX.z) / zFalloff, zFalloffStrength); //change height based on z position
	UV = VERTEX.xz/scaling;
}

void fragment() {
	// Called for every pixel the material is visible on.
	float alpha = texture(baseNoise, UV).x;
	alpha = floor(alpha * colorBanding) / (colorBanding - 1.0);
	vec3 color = baseColor * alpha + stripeColor * (1.0 - alpha);
	float spotAlpha = step(spotClip, texture(spotNoise, UV).x);
	ALBEDO = mix(color, spotColor, spotAlpha);
}

//void light() {
//	// Called for every pixel for every light affecting the material.
//	// Uncomment to replace the default light processing function with this one.
//}
