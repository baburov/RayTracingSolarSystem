#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include "object.h"
#include "background.h"
glm::vec3 trace_ray(const glm::vec3& ray_origin, glm::vec3& ray_direction, int depth, std::vector<Object*>& objects, glm::vec3& light_position, BackgroundTexture& background);
void renderSection(
    std::vector<unsigned char>& pixelBuffer,
    int startY, int endY,
    int width, int height,
    float aspect_ratio, float scale,
    const glm::mat4& camera_rotation,
    const glm::vec3& ray_origin,
    std::vector<Object*>& scene_objects,
    glm::vec3& LIGHT_POSITION,
    BackgroundTexture& background
);