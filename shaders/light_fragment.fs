#version 460
layout(location = 0) out vec4 color;

layout(location = 9) uniform vec3 camera_pos;



in vec3 w_pos;
in vec3 w_normal;

const vec3 object_color = vec3(0.5f,0.f,0.f); 
const vec3 light_color = vec3(1.f,1.f,1.f); 

const vec3 light_dir = normalize(vec3(-1.f ,-1.f, -1.f));


const float ambiant_coef = 0.1;
const float specular_strength = 0.5; 
const int shininess = 32;

void main(){
    float diffuse_coef = max(dot(w_normal, light_dir), 0.0); 
    
    vec3  viewDir    = normalize(camera_pos - w_pos);
    vec3  reflectDir = reflect(light_dir, w_normal);
    float spec       = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    vec3 result = (ambiant_coef + diffuse_coef + specular_strength * spec) * object_color * light_color;
    color = vec4(result, 1.f);
}