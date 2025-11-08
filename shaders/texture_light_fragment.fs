#version 460
layout(location = 0) out vec4 color;

layout(location = 9) uniform vec3 camera_pos;

layout(location = 40) uniform sampler2D in_texture;

in vec3 w_pos;
in vec3 w_normal;
in vec2 tex_coord;

const vec3 light_color = vec3(1.f,1.f,1.f); 

const vec3 light_dir = normalize(vec3(-1.f ,-1.f, -1.f));


const float ambiant_coef = 0.1;
const float specular_strength = 0.5; 
const int shininess = 32;

void main(){
    float diffuse_coef = max(dot(-light_dir, w_normal), 0.0); 
    
    vec3  viewDir    = normalize(camera_pos - w_pos);
    vec3  reflectDir = reflect(light_dir, w_normal);
    float spec       = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    vec3 result = (ambiant_coef + diffuse_coef + specular_strength * spec) * light_color;
    color = texture(in_texture, tex_coord) * vec4(result, 1.f);
}