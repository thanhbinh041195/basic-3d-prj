precision mediump float;
uniform samplerCube  u_s_texture;
uniform vec3 u_posCamera;

varying vec3 Normal;
varying vec3 Position;

void main()
{
    vec3 I = u_posCamera - Position;
    vec3 R = reflect(normalize(-I), normalize(Normal));
    gl_FragColor = vec4(textureCube(u_s_texture, R).rgb, 1.0);
}
