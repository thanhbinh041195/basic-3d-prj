attribute vec3 a_posL;
varying vec3 v_posl;
uniform mat4 u_w;
uniform mat4 u_l;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_w *u_l* posL;
v_posl = a_posL;
}
   