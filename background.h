#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <vector>
#include <string>
#include "stb_image.h"
#include <glm/glm.hpp>

class BackgroundTexture {
private:
    std::vector<glm::vec3> pixels; // RGB data
public:
    int width, height;

    BackgroundTexture() {}

    BackgroundTexture(const std::string& filepath) {
        load_image(filepath);
    }

    bool load_image(const std::string& filepath);
    glm::vec3 get_pixel(const glm::vec3& ray_origin, const glm::vec3& ray_direction) const;
};


#endif
