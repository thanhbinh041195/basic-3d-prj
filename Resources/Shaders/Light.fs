precision mediump float;

varying vec2 v_uv;
varying vec3 v_viewDirection;
varying vec3 v_lightDirection;

uniform sampler2D  u_s_texture,u_s_texture1;
void main()
{
    vec4 u_ambient = vec4(1.0,1.0,1.0,1.0);
    vec4 u_specular = vec4(1.0,1.0,1.0,1.0);
    vec4 u_diffuse= vec4(1.0,1.0,1.0,1.0);
    float u_specularPower = 1.0;
    
    vec4 a = texture2D(u_s_texture,v_uv);

    // Fetch basemap color
    vec4 baseColor = vec4(0.0,0.7,1.0,1.0);

    // Fetch the tangent-space normal from normal map
    vec3 normal = vec4(1.0,0.0,0.0,1.0).xyz;

    // Scale and bias from [0, 1] to [-1, 1] and normalize
    normal = normalize(normal * 2.0 - 1.0);

    // Normalize the light direction and view direction
    vec3 lightDirection = normalize(v_lightDirection);
    vec3 viewDirection = normalize(v_viewDirection);

    // Compute N.L
    float nDotL = dot(normal, lightDirection);

    // Compute reflection vector
    vec3 reflection = (2.0 * normal * nDotL) - lightDirection;

    // Compute R.V
    float rDotV = max(0.0, dot(reflection, viewDirection));

    // Compute Ambient term
    vec4 ambient = u_ambient * baseColor;

    // Compute Diffuse term
    vec4 diffuse = u_diffuse * nDotL * baseColor;

    // Compute Specular term
    vec4 specular = u_specular * pow(rDotV, u_specularPower);

	gl_FragColor = ambient + diffuse + specular;
}
