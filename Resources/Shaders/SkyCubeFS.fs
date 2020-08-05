uniform samplerCube u_texture;
precision mediump float;
varying vec3 v_posL;
void main()
{
	gl_FragColor = textureCube(u_texture, v_posL);
}
