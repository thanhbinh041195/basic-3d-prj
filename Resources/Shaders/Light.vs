attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec3 a_norm;
attribute vec3 a_binorm;
attribute vec3 a_tgt;

varying vec2 v_uv;
varying vec3 v_viewDirection;
varying vec3 v_lightDirection;

uniform mat4 u_w;
uniform mat4 u_l;
uniform mat4 u_invertMax;
uniform vec3 u_posCamera;
void main()
{
vec4 posL = vec4(a_posL, 1.0);

//Transform eye vector into world space
vec3 eyePositionWorld = (u_invertMax * vec4(u_posCamera, 1.0)).xyz;

// Compute world space direction vector
vec3 viewDirectionWorld = eyePositionWorld - a_posL.xyz;

// Transform light position into world space
vec3 lightPositionWorld = (u_invertMax * vec4(0.0,0.0,10.0,1.0)).xyz;

// Compute world space light direction vector
vec3 lightDirectionWorld = lightPositionWorld - a_posL.xyz;

// Create the tangent matrix
mat3 tangentMat = mat3(a_tgt,a_binorm,a_norm);

// Transform the view and light vectors into tangent space
v_viewDirection = viewDirectionWorld * tangentMat;
v_lightDirection = lightDirectionWorld * tangentMat;

gl_Position = u_w *u_l* posL;
v_uv = a_uv;
}
   