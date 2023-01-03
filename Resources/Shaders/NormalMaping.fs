precision mediump float;
varying vec2 v_uv;
uniform sampler2D  u_s_texture,u_s_texture2;
void main()
{
    highp vec4 finalColor = texture2D(u_s_texture, v_uv);
	highp vec4 finalColor1 = texture2D(u_s_texture2, v_uv);
	gl_FragColor = vec4(mix(finalColor.rgb, finalColor1.rgb, 0.5), finalColor.a);
}
