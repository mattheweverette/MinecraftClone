#version 330 core

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main() {
        o_Color = texture(u_Texture1, v_TexCoord) + texture(u_Texture2, v_TexCoord) * vec4(0.0, 1.0, 0.0, 1.0);
}
