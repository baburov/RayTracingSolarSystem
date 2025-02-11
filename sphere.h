#ifndef SPHERE_H
#define SPHERE_H
#include "texture.h"
#include "object.h"

class Sphere : public Object {
public:

    float radius;
    float texture_rotation = 0.0f;
    Sphere(const glm::vec3& c, float r, const glm::vec3& col, float refl, float trans, glm::vec3 dynamic_param)
        : Object(col, refl, trans, dynamic_param, c), radius(r) {
            texture = Texture();
            texture.width = 0;
            texture.height = 0;
            dynamic_param.y *= orbit_scale;
            radius *= scale;
        }

    float intersect(const glm::vec3& ray_origin, const glm::vec3& ray_direction)  override;
    void update_coord(Object* object, float delta_x, float delta_y, float delta_z) override;
    glm::vec3 get_normal(const glm::vec3& hit_point, glm::vec3 light_pos = glm::vec3(0, 0, 0)) override;
    void rotate_texture(float delta_time);

    glm::vec3 get_color(const glm::vec3& hit_point);
    std::string get_name() {
        return "sphere";
    }
    float get_min_distance() {
        return radius + 1.0f;
    }
};

#endif
