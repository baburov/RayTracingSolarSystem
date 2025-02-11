#include "sphere.h"
#include <iostream>

float Sphere::intersect(const glm::vec3& ray_origin, const glm::vec3& ray_direction)  {
    glm::vec3 oc = ray_origin - center;
    float a = glm::dot(ray_direction, ray_direction);
    float b = 2.0f * glm::dot(oc, ray_direction);
    float c = glm::dot(oc, oc) - radius * radius * scale * scale;
    float discriminant = b * b - 4 * a * c;
    return (discriminant < 0) ? -1.0f : (-b - sqrt(discriminant)) / (2.0f * a);
}

void Sphere::update_coord(Object* object, float delta_x, float delta_y, float delta_z) {
    center = glm::vec3(object->center.x + delta_x, object->center.y + delta_y, object->center.z + delta_z);
}

glm::vec3 Sphere::get_normal(const glm::vec3& hit_point, glm::vec3 light_pos) {
    return glm::normalize(hit_point - center); 
}

void Sphere::rotate_texture(float delta_time) {
    float rotation_speed = 0.00001f; // cкорость 
    texture_rotation += rotation_speed * delta_time;
    if (texture_rotation > 2 * M_PI) {
        texture_rotation -= 2 * M_PI; // cбрасываем угол 
    }
}

glm::vec3 Sphere::get_color(const glm::vec3& hit_point) {
    if (texture.height != 0) {
        glm::vec3 dir = glm::normalize(hit_point - center);
        float u = 0.5f + atan2(dir.z, dir.x) / (2 * M_PI);
        float v = 0.5f - asin(dir.y) / M_PI;
        u += texture_rotation / (2 * M_PI);
        if (u > 1.0f) u -= 1.0f;

        return texture.get_pixel(u, 1 - v);
    } else {
        return color;
    }
}