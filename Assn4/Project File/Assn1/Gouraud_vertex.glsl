#version 330 core

//No ambient light
//Diffuse Reflection와 Specular Reflection을 모두 수행, ks(빛나는 정도)값을 조절
//Directional Light과 Point Light이 하나만 주어진다고 명시되어 있으므로, 각 광원타입의 정보를 저장할때 List를 안써도 됨.
//Light는 백색광이라고 가정

layout(location=0) in vec4 vPos;
layout(location=1) in vec3 vNorm;

uniform mat4 ModelView;
uniform mat4 Projection;

uniform vec4 DirLightPos, DirLightNorm; 
uniform vec4 PointLightPos;

uniform float sRef;//빛나는 정도
uniform float lAttC1,lAttC2;//Constant for Light Attenuation, [ min(1.0 / (1.0 + c1*d + c2*d*d)) ] (c1대신 1.0 쓰는 이유는 분모가 항상 분자보다 큼을 보장하기 위해서

out vec4 vertexColor;


void main()
{

}

