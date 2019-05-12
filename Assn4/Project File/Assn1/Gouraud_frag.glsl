#version 330 core

in vec2 UV;

in vec4 vertexColor;

uniform sampler2D Texture;

out vec4 color;
void main()
{
//vec4(0.8,0.8,0.8,0.8) *
color =  texture(Texture,UV);
}	