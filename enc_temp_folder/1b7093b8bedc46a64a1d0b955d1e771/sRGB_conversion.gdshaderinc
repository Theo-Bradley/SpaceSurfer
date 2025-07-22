vec4 Linearize(in vec4 col)
{
	vec4 result;
	result.r = pow(col.r, 2.2);
	result.g = pow(col.g, 2.2);
	result.b = pow(col.b, 2.2);
	result.a = col.a;
	return result;
}