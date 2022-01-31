#version 450 core

layout(location = 0) out vec4 o_color;

uniform sampler2D texture;

in vec2 i_texCoord;
in vec4 i_color;

void main()
{
    vec4 pixel = texture2D(texture, i_texCoord);
	o_color = i_color;
}