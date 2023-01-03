attribute vec3 a_posL;
attribute vec3 a_norm;
attribute vec2 a_uv;

varying vec3 Normal;
varying vec3 Position;

uniform mat4 u_w;
uniform mat4 u_l;
uniform mat4 u_normW;
void main()
{
Normal = mat3(u_l)  * a_norm;
Position = vec3(u_w * u_normW * vec4(a_posL, 1.0));
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_w *u_l* posL;
}
   