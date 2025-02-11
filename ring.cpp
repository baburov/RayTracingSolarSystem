#include <glm/glm.hpp>
#include <cmath>
#include "ring.h"
float Ring::intersect(const glm::vec3& ray_origin, const glm::vec3& ray_direction) {
    float denom = glm::dot(ray_direction, normal);
    if (fabs(denom) < 1e-6) {
        return -1.0f; 
    }
    float t = glm::dot(center - ray_origin, normal) / denom;
    if (t < 0) {
        return -1.0f; 
    }
    glm::vec3 p_hit = ray_origin + t * ray_direction;
    glm::vec3 v = p_hit - center;
    glm::vec3 v_plane = v - glm::dot(v, normal) * normal;
    float dist_to_center = glm::length(v_plane);
    if (dist_to_center >= inner_radius * scale && dist_to_center <= outer_radius * scale) {
        return t; 
    }
    return -1.0f;
}

void Ring::update_coord(Object* object, float delta_x, float delta_y, float delta_z) {
    center = glm::vec3(object->center.x + delta_x, object->center.y + delta_y, object->center.z + delta_z);
}

glm::vec3 Ring::get_normal(const glm::vec3& hit_point, glm::vec3 light_pos) {
    float diff_intensity = glm::max(glm::dot(normal, light_pos), 0.0f);
    if (diff_intensity == 0)
        return normal * -1.0f;
    return normal; 
}

glm::vec3 Ring::get_color(const glm::vec3& hit_point) {
    if (texture.height != 0) {
        // Вектор 
        glm::vec3 local_hit = hit_point - center;

        // Проецируем 
        glm::vec3 ring_x_axis = glm::normalize(glm::cross(glm::vec3(0, 1, 0), normal));
        if (glm::length(ring_x_axis) < 1e-6) {
            ring_x_axis = glm::normalize(glm::cross(glm::vec3(1, 0, 0), normal));
        }
        glm::vec3 ring_y_axis = glm::normalize(glm::cross(normal, ring_x_axis));

        // Локальные 
        float local_x = glm::dot(local_hit, ring_x_axis);
        float local_y = glm::dot(local_hit, ring_y_axis);

        // Полярные 
        float u = 0.5f + atan2(local_y, local_x) / (2 * M_PI);
        float radius = glm::length(glm::vec2(local_x, local_y));
        float v = (radius - inner_radius * scale) / (outer_radius * scale - inner_radius * scale);

        if (v < 0.0f || v > 1.0f) {
            return color;
        }
        return texture.get_pixel(v, u);
    } else {
        return color; 
    }
}
