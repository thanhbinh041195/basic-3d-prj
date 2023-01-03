precision mediump float;

varying vec2 v_uv;
varying vec3 v_pos;

uniform sampler2D  u_s_texture;
uniform float u_pixel;
void main()
{
    vec2 samples0,samples1,samples2,samples3,samples4;
    vec4 rez;
    samples0 = (v_uv * 1.0 +0.5) +  0.05 *vec2( 0.0, 0.0);
     samples1 = (v_uv * 1.0 +0.5) + 0.05 *vec2( -1.0,0.0);
     samples2 = (v_uv * 1.0 +0.5) + 0.05 *vec2( -2.0,0.0);
     samples3 = (v_uv * 1.0 +0.5) +0.05 *vec2( 1.0, 0.0);
     samples4 =(v_uv * 1.0 +0.5) + 0.05 *vec2( 2.0, 0.0);
    rez = 0.061*(texture2D(u_s_texture,samples1) +texture2D(u_s_texture,samples4)) +0.242*(texture2D(u_s_texture,samples2) +texture2D(u_s_texture,samples3)) +0.383*texture2D(u_s_texture,samples0);
	gl_FragColor = rez;
}
