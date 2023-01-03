precision mediump float;
varying vec2 v_uv;
varying vec3 v_pos;

uniform float u_time;
uniform sampler2D  u_s_texture, u_s_texture1 ,u_s_texture2;
void main()
{
    vec2 disp = texture2D(u_s_texture, vec2(v_uv.x, v_uv.y + u_time)).rg;
    vec2 offset = (2.0 * disp - 1.0) * 0.1;
    vec2 Tex_coords_display = v_uv + offset;
    vec4 fire_color = texture2D(u_s_texture2,Tex_coords_display);
    vec4 AlphaValue = texture2D(u_s_texture1, v_uv);
    vec4 finalColor = fire_color * (1.0, 1.0, 1.0, AlphaValue.r);
    if(finalColor.a < 0.8)
        discard;
	gl_FragColor = fire_color * (1.0, 1.0, 1.0, AlphaValue.r);
}
