precision mediump float;
varying vec2 v_uv;
uniform sampler2D  u_s_texture,u_s_texture1,u_s_texture2,u_s_texture3;
void main()
{
	vec4 BT = texture2D(u_s_texture, v_uv );
    vec4 Tex1 = texture2D(u_s_texture1, v_uv * 16.0);
    vec4 Tex2 = texture2D(u_s_texture2, v_uv * 16.0);
    vec4 Tex3 = texture2D(u_s_texture3, v_uv * 16.0);
	gl_FragColor = (BT.r * Tex1 + BT.g * Tex2 + BT.b * Tex3) / (BT.r + BT.g + BT.b);
}
