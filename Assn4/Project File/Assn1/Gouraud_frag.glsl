#version 330 core

in vec2 UV;

in vec4 vertexColor;

uniform vec4 defaultColor;
uniform sampler2D Texture;
uniform bool IsTexture;

out vec4 color;
void main()
{
if (IsTexture) 
color = defaultColor;
else
color = texture(Texture,UV);
}	