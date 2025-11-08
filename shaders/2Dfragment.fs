#version 460
layout(location = 0) out vec4 color;

layout(location = 40) uniform sampler2D in_texture;

in vec2 tex_coord;

void main(){
    color = texture(in_texture, tex_coord);
}