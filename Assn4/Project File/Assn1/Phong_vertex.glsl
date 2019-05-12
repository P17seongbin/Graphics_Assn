#version 330 core

//No ambient light
//Diffuse Reflection�� Specular Reflection�� ��� ����, ks(������ ����)���� ����
//Directional Light�� Point Light�� �ϳ��� �־����ٰ� ��õǾ� �����Ƿ�, �� ����Ÿ���� ������ �����Ҷ� List�� �Ƚᵵ ��.
//Light�� ������̶�� ����

layout(location=0) in vec3 vertexPos;
layout(location=2) in vec3 vertexNorm;
layout(location=1) in vec2 vertexUV;


uniform sampler2D Texture;

uniform mat4 MVP;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 Rotate;

out vec3 FragPos;  
out vec3 Normal;
out vec4 vertexColor;
out vec2 UV;


void main()
{

gl_Position =  MVP * vec4(vertexPos,1.0); 
FragPos = vec3(Model * vec4(vertexPos,1.0));
Normal = vec3(Rotate * vec4(vertexNorm,1.0));
UV = vertexUV;

}

