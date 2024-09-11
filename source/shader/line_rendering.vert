#version 150
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec3 position;

uniform mat4 Projection;
uniform mat4 Modelview;

void main()
{
    vec4 Position = vec4(position, 1.0);
    gl_Position = Projection * Modelview * Position;
}