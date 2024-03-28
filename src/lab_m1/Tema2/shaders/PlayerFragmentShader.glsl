#version 330

in vec3 color;

out vec4 FragColor;

void main()
{
    // Afi?eazã culoarea din texturã utilizând coordonatele de texturã primite
    // ?i culoarea primitã de la shader-ul de vârfuri
    FragColor = vec4(color, 1.0);
}
