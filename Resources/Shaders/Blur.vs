attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
uniform mat4 u_w;
uniform mat4 u_l;
void main()
{
vec2 pos = vec2(a_posL.x,a_posL.y);
vec4 posL = vec4(pos, 0.0, 1.0);
gl_Position = u_w *u_l* posL;
v_uv = a_uv;
}
   