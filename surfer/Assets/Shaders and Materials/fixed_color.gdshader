shader_type canvas_item;

uniform vec3 color : source_color;

void fragment() {
    vec4 sampled = texture(TEXTURE, UV); //sample tex
    COLOR = vec4(color.xyz, sampled.a); //output color with alpha cutout of tex
}