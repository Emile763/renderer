#version 460
layout(location = 0) in vec3 a_position;

layout(location = 4) uniform mat4 projection;
layout(location = 5) uniform mat4 translation;
layout(location = 6) uniform mat4 rotation;
layout(location = 7) uniform mat4 scale;

layout(location = 8) uniform mat4 view;


void main(){
    gl_Position =  projection * view * translation * vec4(a_position, 1.f);
}