#version 330 core

//No ambient light
//Diffuse Reflection와 Specular Reflection을 모두 수행, ks(빛나는 정도)값을 조절
//Directional Light과 Point Light이 하나만 주어진다고 명시되어 있으므로, 각 광원타입의 정보를 저장할때 List를 안써도 됨.
//Light는 백색광이라고 가정

layout(location=0) in vec3 vertexPos;
layout(location=2) in vec3 vertexNorm;
layout(location=1) in vec2 vertexUV;

uniform vec3 viewPos;

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

uniform vec3 PointLightPos, DirLightPos;  

void main()
{

gl_Position =  MVP * vec4(vertexPos,1.0); 
FragPos = vec3(Model * vec4(vertexPos,1.0));
Normal = vec3(Rotate * vec4(vertexNorm,1.0));
UV = vertexUV;

float Ks = 0.5;
float shine = 32;

vec3 normal = normalize(Normal);
vec3 lightDir = normalize(PointLightPos - FragPos);

vec3 viewDir = normalize(viewPos - FragPos);
vec3 reflectDir = reflect(-lightDir, normal);  

float diff = max(dot(normal, lightDir), 0.0);
vec3 diffuse = diff * vec3(1,1,1);

float spec = pow(max(dot(viewDir, reflectDir), 0.0), shine);
vec3 specular = Ks * spec * vec3(1,1,1); 


vertexColor = vec4((diffuse+specular),1.0);
}
