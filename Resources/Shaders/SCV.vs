attribute vec3 a_posL;
attribute vec2 a_uv;
varying vec2 v_uv;
varying vec3 v_pos;
varying float v_distance;
uniform mat4 u_w;
uniform mat4 u_l;
uniform vec3 u_posCamera;
void main()
{
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_w *u_l* posL;
vec4 posObj = u_l * posL;
v_distance = sqrt( (posObj.x - u_posCamera.x) *(posObj.x - u_posCamera.x) +
				   (posObj.y - u_posCamera.y) *(posObj.y - u_posCamera.y) +
				   (posObj.z - u_posCamera.z) *(posObj.z - u_posCamera.z) );
v_uv = a_uv;
v_pos = a_posL;
}
   