attribute vec3 a_posL;
attribute vec2 a_uv;

uniform mat4 MVP;
varying vec3 v_posL;
void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = MVP * posL;
	v_posL = a_posL;
}
   