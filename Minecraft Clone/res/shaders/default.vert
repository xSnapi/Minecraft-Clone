#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 color;

out vec2 i_texCoord;
out vec4 i_color;

uniform mat4 u_transform;
uniform mat4 u_projection;

void main() {
	gl_Position = u_projection * u_transform * position;
	i_texCoord  = texCoord;
	i_color		= color;
}