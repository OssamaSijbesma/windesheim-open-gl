#version 430 core

in VS_OUT
{
   vec3 N;
   vec3 L;
   vec3 V;
} fs_in;

uniform vec3 mat_ambient;
uniform vec3 mat_diffuse;
uniform vec3 mat_specular;
uniform float mat_power;

void main()
{
    // Normalize the incoming N and L vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Calculate R locally
    vec3 R = reflect(-L, N);

    // Compute the diffuse component for each fragment
    vec3 diffuse = max(dot(N, L), 0.0) * mat_diffuse;

    // Compute the specular component for each fragment
    vec3 specular = pow(max(dot(R, V), 0.0), mat_power) * mat_specular;

    // Write final color to the framebuffer
    gl_FragColor = vec4(mat_ambient + diffuse + specular, 1.0);
}
