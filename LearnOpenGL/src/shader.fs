#version 330 core
out vec4 FragColor;


uniform vec4 baseColor;
in vec3 ourColor;

void main()
{
    FragColor = baseColor + vec4(ourColor, 1.0f);
}