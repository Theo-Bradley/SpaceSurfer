shader_type canvas_item;

uniform vec3 color : source_color = vec3(0.706, 0.696, 0.658); //nice tinted grey default color

void fragment() {
    vec4 sampled = texture(TEXTURE, UV); //sample tex
    COLOR = vec4(color.xyz, sampled.a); //output color with alpha cutout of tex
}