#version 460
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_tex_coord;

layout(location = 4) uniform mat4 projection;
layout(location = 5) uniform mat4 translation;
layout(location = 6) uniform mat4 rotation;
layout(location = 7) uniform mat4 scale;
layout(location = 8) uniform mat4 view;

out vec3 w_pos;
out vec3 w_normal;
out vec2 tex_coord;

void main(){
    // TODO: move to CPU
    mat4 model = translation * rotation * scale;
    mat3 normale_mat = mat3(transpose(inverse(model)));


    w_normal    = normale_mat * a_normal;
    w_pos       = normalize(vec3(model * vec4(a_position, 1.f)));
    tex_coord   = a_tex_coord;
    gl_Position = projection * view * model * vec4(a_position, 1.f);
}