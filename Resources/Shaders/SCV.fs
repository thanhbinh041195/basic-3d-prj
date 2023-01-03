precision mediump float;
varying vec2 v_uv;
varying vec3 v_pos;
varying float v_distance;
uniform float u_fogStar;
uniform float u_fogLenght;
uniform vec4  u_fogColor;
uniform sampler2D  u_s_texture;
void main()
{
	float levp = clamp( (v_distance - u_fogStar ) /u_fogLenght, 0.0, 1.0 );
	gl_FragColor =levp *u_fogColor + (1.0 - levp) * texture2D(u_s_texture, v_uv);
}
