#version 330

in vec3 color;

out vec4 FragColor;

void main()
{
    // Afi?eaz� culoarea din textur� utiliz�nd coordonatele de textur� primite
    // ?i culoarea primit� de la shader-ul de v�rfuri
    FragColor = vec4(color, 1.0);
}
