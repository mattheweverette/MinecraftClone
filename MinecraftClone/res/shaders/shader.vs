#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoord1;
layout(location = 2) in vec2 a_TexCoord2;

out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform int u_TexCoordIndex;

void main() {
    gl_Position = u_MVP * a_Position;
    if (u_TexCoordIndex == 0)
        v_TexCoord = a_TexCoord1;
    else
        v_TexCoord = a_TexCoord2;
}
