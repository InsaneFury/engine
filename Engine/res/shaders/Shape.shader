#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
in vec4 color;


out vec4 Color;
uniform mat4 myMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	Color = color;
	gl_Position = proj * view * model * position;
	
};

#shader fragment
#version 330 core

in vec4 Color;
layout(location = 0) out vec4 outColor;


void main()
{
	outColor = Color;
};