#version 330 core

//No ambient light
//Diffuse Reflection�� Specular Reflection�� ��� ����, ks(������ ����)���� ����
//Directional Light�� Point Light�� �ϳ��� �־����ٰ� ��õǾ� �����Ƿ�, �� ����Ÿ���� ������ �����Ҷ� List�� �Ƚᵵ ��.
//Light�� ������̶�� ����

layout(location=0) in vec4 vPos;
layout(location=1) in vec3 vNorm;

uniform mat4 ModelView;
uniform mat4 Projection;

uniform vec4 DirLightPos, DirLightNorm; 
uniform vec4 PointLightPos;

uniform float sRef;//������ ����
uniform float lAttC1,lAttC2;//Constant for Light Attenuation, [ min(1.0 / (1.0 + c1*d + c2*d*d)) ] (c1��� 1.0 ���� ������ �и� �׻� ���ں��� ŭ�� �����ϱ� ���ؼ�

out vec4 vertexColor;


void main()
{

}

