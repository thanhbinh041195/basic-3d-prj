precision mediump float;

varying vec2 v_uv;
varying vec3 v_pos;

uniform sampler2D  u_s_texture;
uniform float u_pixel;
void main()
{
    vec3 color = texture2D(u_s_texture, v_uv).rgb;
    float brightness = 0.3 * color.r + 0.59 * color.g + 0.11 * color.b;
    float val = step(0.1, brightness);
    gl_FragColor = vec4(color * val, 1.0);
}
