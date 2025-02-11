#ifndef OBJECT_H
#define OBJECT_H
#include "texture.h"
#include <glm/glm.hpp>
#include <string>
class Object {
public:
    glm::vec3 color;
    float reflectivity;
    float transparency;
    Texture texture;
    float scale;
    float orbit_scale;
    glm::vec3 dynamic_param; // rang, orbit_radius, speed
    glm::vec3 center;
    std::string name;
    int main_ind = 0;
    float shininess;
    glm::vec3 specular_color;
    // int rang; // ранг для реализации движения по орбитма. 
    // float orbit_radius;
    // float speed;
    Object(const glm::vec3& col, float refl, float trans, glm::vec3 dynamic_param, glm::vec3 center)
        : color(col), reflectivity(refl), transparency(trans), dynamic_param(dynamic_param), center(center){
            scale = 1.0f;
            orbit_scale = 1.0f;
            shininess = 80/reflectivity;
            specular_color = glm::vec3(1, 1, 1);
        }
        
    virtual void rotate_texture(float delta_time) = 0;
    virtual float intersect(const glm::vec3& origin, const glm::vec3& direction) = 0;
    virtual void update_coord(Object* object, float delta_x, float delta_y, float delta_z) = 0;
    float get_min_distance() {
        return 1.0f;
    }
    virtual glm::vec3 get_normal(const glm::vec3& hit_point, glm::vec3 light_pos = glm::vec3(0, 0, 0)) = 0;

    virtual glm::vec3 get_color(const glm::vec3& hit_point) = 0;
    virtual std::string get_name() = 0;
    virtual ~Object() {}
};

#endif
