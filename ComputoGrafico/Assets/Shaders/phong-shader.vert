#version 330 //establece la vercion de glsl

//linea de informacion que se le esta pasando al shader
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 tex;
layout (location = 2) in vec3 norm;
//layout (location = 3) in vec3 tangent;

//variables que se pasan a la siguiente etapa del shader
out vec3 FragPos;
out vec3 Normal1;

//variables que se van a compartir entre los shader
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model*vec4(pos,1.0);
	Normal1=norm;
	FragPos=(model*vec4(pos,1.0)).xyz;
}