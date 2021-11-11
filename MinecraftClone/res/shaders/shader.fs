#version 330 core

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[3];

void main() {
    int texIndex = int(v_TexIndex);
    o_Color = texture(u_Textures[texIndex], v_TexCoord);
}
