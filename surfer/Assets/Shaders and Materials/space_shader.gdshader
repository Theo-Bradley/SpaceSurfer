shader_type sky;

uniform sampler2D skyNoise;
uniform float starThresh;
uniform vec3 starColor: source_color;

void sky() {
	// Called for every visible pixel in the sky background, as well as all pixels
	// in the radiance cubemap.
	float val = texture(skyNoise, SKY_COORDS).r;
	COLOR = step(starThresh, val) * starColor;
	//COLOR = vec3(val);
}
