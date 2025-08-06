shader_type spatial;

#include "res://Assets/Shaders and Materials/distance_curve.gdshaderinc"

uniform float radius;
uniform float feathering;
uniform float edgeFeathering;
uniform float innerRadius;
uniform vec3 baseColor: source_color = vec3(0.0, 0.0, 0.0);
uniform vec3 edgeColor: source_color = vec3(1.0, 1.0, 1.0);
uniform vec2 uv_offset;

void vertex() {
	// Called for every vertex the material is visible on.
	UV += uv_offset;
	Curve(VERTEX);
}

void fragment() {
	// Called for every pixel the material is visible on.
	float value = smoothstep(length(vec2(0.5, 0.5) - UV.xy) - feathering / 2.0, length(vec2(0.5, 0.5) - UV.xy) + feathering / 2.0, radius);
	//float rim = smoothstep(edge2, edge1 - feathering / 2.0, 1.0 - smoothstep(length(vec2(0.5, 0.5) - UV.xy) - feathering / 2.0, length(vec2(0.5, 0.5) - UV.xy) + feathering / 2.0, innerRadius));
	//ALBEDO = mix(edgeColor, baseColor, rim);
	ALBEDO = mix(baseColor, edgeColor, 1.0 - smoothstep(length(vec2(0.5, 0.5) - UV.xy) - edgeFeathering / 2.0, length(vec2(0.5, 0.5) - UV.xy) + edgeFeathering/ 2.0, innerRadius));
	ALPHA = value;
}

//void light() {
//	// Called for every pixel for every light affecting the material.
//	// Uncomment to replace the default light processing function with this one.
//}
