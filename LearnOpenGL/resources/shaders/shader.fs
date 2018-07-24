#version 330 core
out vec4 FragColor;

uniform vec4 baseColor;
uniform sampler2D texture0;
uniform sampler2D texture1;

in vec2 TexCoord;
in vec3 ourColor;

void main()
{
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.5);
}