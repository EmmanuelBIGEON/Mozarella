#version 460 core
out vec4 FragColor;

in vec3 aPosC;

void main()
{
    FragColor = vec4((aPosC.x + 2.0f) * 0.2f, (aPosC.y + 2.0f) * 0.2f, (aPosC.z + 2.0f) * 0.2f, 1.0f);
}