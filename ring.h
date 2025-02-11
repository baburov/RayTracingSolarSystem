#include <glm/glm.hpp>
#include "object.h"

class Ring : public Object {
public:
    glm::vec3 normal;
    float inner_radius;
    float outer_radius;

    Ring(const glm::vec3& c, const glm::vec3& n, float inner_r, float outer_r, const glm::vec3& col, float refl, float trans, glm::vec3 dynamic_param)
        : Object(col, refl, trans, dynamic_param, c), normal(glm::normalize(n)), inner_radius(inner_r), outer_radius(outer_r) {
            dynamic_param.y *= orbit_scale;
            inner_radius *= scale;
            outer_radius *= scale;
        }


    float intersect(const glm::vec3& ray_origin, const glm::vec3& ray_direction)  override;
    void update_coord(Object* object, float delta_x, float delta_y, float delta_z) override;
    
    glm::vec3 get_normal(const glm::vec3& hit_point, glm::vec3 light_pos = glm::vec3(0, 0, 0))  override;
    void rotate_texture(float delta_time) {}

    glm::vec3 get_color(const glm::vec3& hit_point) override;

    std::string get_name() { return "ring"; }
    float get_min_distance() {
        return outer_radius + 1.0f;
    }
};
