precision mediump float;

varying vec2 v_uv;
varying vec3 v_pos;

uniform sampler2D  u_s_texture, u_s_texture1, u_s_texture2;
uniform float u_pixel;

float CalculateMixFactor(vec2 uv)
{
float depth = texture2D(u_s_texture, uv).x;
float z = -5.0 * 1.0 / (depth * (5.0 - 1.0) - 5.0);
float k = clamp(abs(z - 0.5) / 1.5, 0.0, 1.0);
return k;

}
void main()
{
    vec2 uv2 = v_uv + vec2(1.5,6.0);
    vec2 uv3 = v_uv + vec2(3.0, 0.2);
    vec2 uv4 = v_uv + vec2(6.0, 0.1);
    vec2 uv5 = v_uv + vec2(-3.0, 0.2);
    vec2 uv6 = v_uv + vec2(-1.5, 6.0);
    vec2 uv7 = v_uv + vec2(-3.0, -0.2);
    vec2 uv8 = v_uv + vec2(6.0, -0.1);
    vec2 uv9 = v_uv + vec2(3.0, -0.2);

    vec4 color1 = texture2D(u_s_texture1, v_uv);
    vec4 color2 = texture2D(u_s_texture1, uv2);
    vec4 color3 = texture2D(u_s_texture1, uv3);
    vec4 color4 = texture2D(u_s_texture1, uv4);
    vec4 color5 = texture2D(u_s_texture1, uv5);
    vec4 color6 = texture2D(u_s_texture1, uv6);
    vec4 color7 = texture2D(u_s_texture1, uv7);
    vec4 color8 = texture2D(u_s_texture1, uv8);
    vec4 color9 = texture2D(u_s_texture1, uv9);

    float d1 = CalculateMixFactor(v_uv);
    float d2 = CalculateMixFactor(uv2);
    float d3 = CalculateMixFactor(uv3);
    float d4 = CalculateMixFactor(uv4);
    float d5 = CalculateMixFactor(uv5);
    float d6 = CalculateMixFactor(uv6);
    float d7 = CalculateMixFactor(uv7);
    float d8 = CalculateMixFactor(uv8);
    float d9 = CalculateMixFactor(uv9);

    float total = 2.0  + d2 + d3 + d4 + d5 + d6 + d7 + d8 + d9;

    vec4 colorOriginal = texture2D(u_s_texture2, v_uv);
    vec4 colorBlur = (2.0  * color1 + color2 * d2 + color3 * d3 + color4 * d4 + color5 * d5 + color6 * d6 + color7 * d7 + color8 * d8 + color9 * d9) / total;
    gl_FragColor = mix(colorOriginal,colorBlur, d1);
}