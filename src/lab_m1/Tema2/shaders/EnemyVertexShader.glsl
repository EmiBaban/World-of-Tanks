#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec2 tex_coord;
layout(location = 2) in vec3 v_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform float enemy_hp;

// Output value to fragment shader
out vec3 color;

void main()
{
    vec3 damaged_color = vec3(object_color.x, object_color.y - enemy_hp * 0.1, object_color.z);

    color = damaged_color;

    float deformationFactor = enemy_hp * 0.2;
    vec3 deformation = normalize(v_normal) * deformationFactor;

    vec3 deformedPosition = v_position + deformation;

    gl_Position = Projection * View * Model * vec4(deformedPosition, 1.0);
}
