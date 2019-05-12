#version 330 core

//No ambient light
//Diffuse Reflection와 Specular Reflection을 모두 수행, ks(빛나는 정도)값을 조절
//Directional Light과 Point Light이 하나만 주어진다고 명시되어 있으므로, 각 광원타입의 정보를 저장할때 List를 안써도 됨.
//Light는 백색광이라고 가정

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

