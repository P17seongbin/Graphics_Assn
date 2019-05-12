#version 330 core

in vec3 FragPos;  
in vec3 Normal;
in vec4 vertexColor;
in vec2 UV;

uniform vec3 viewPos;

uniform vec4 defaultColor;
uniform sampler2D Texture;
uniform bool IsTexture;


uniform vec3 PointLightPos, DirLightPos;  

out vec4 color;

void main()
{
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

if (IsTexture) 
color = defaultColor * vec4((diffuse+specular),1.0);
else
color = texture(Texture,UV) * vec4((diffuse+specular),1.0);
}	
