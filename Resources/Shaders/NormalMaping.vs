attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
varying vec3 v_pos;
uniform mat4 u_w;
uniform mat4 u_l;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_w *u_l* posL;
v_uv = a_uv;
v_pos = a_posL;
}
   