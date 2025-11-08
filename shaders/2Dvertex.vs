#version 460
layout(location = 0) in vec2 a_position;
layout(location = 2) in vec2 a_tex_coord;

layout(location = 4) uniform mat3 projection;
layout(location = 5) uniform mat3 translation;
layout(location = 6) uniform mat3 rotation;
layout(location = 7) uniform mat3 scale;
layout(location = 8) uniform mat3 view;

out vec2 tex_coord;

void main(){
    tex_coord = a_tex_coord;
    // TODO: move to CPU
    mat3 model = translation * rotation * scale;
    // gl_Position =  vec4( (projection * (view * (model * vec3(a_position, 1)))).xy, -1.f, 1.f);
    gl_Position =  vec4(( projection * (view *(model * vec3(a_position, 1)))).xy, -1.f, 1.f);
}