#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

class Texture {
private:

    std::vector<glm::vec3> pixels; // RGB data
public:
    int width, height;
    Texture() {}
    Texture(const std::string& filepath) {
        load_image(filepath);
    }
    bool load_image(const std::string& filepath);
    glm::vec3 get_pixel(float u, float v) const;
};

#endif // TEXTURE_H
