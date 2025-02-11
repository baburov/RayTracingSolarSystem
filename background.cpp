#include "background.h"

bool BackgroundTexture::load_image(const std::string& filepath) {
    int channels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 3);
    if (!data) return false;
    pixels.resize(width * height);
    for (int i = 0; i < width * height; ++i) {
        pixels[i] = glm::vec3(data[3 * i] / 255.0f, data[3 * i + 1] / 255.0f, data[3 * i + 2] / 255.0f);
    }
    stbi_image_free(data);
    return true;
}

glm::vec3 BackgroundTexture::get_pixel(const glm::vec3& ray_origin, const glm::vec3& ray_direction) const {
    float u = 0.5f + atan2(ray_direction.z, ray_direction.x) / (2.0f * M_PI);
    float v = 0.5f - asin(ray_direction.y) / M_PI;
    if (u > 1 || u < 0 || v > 1 || v < 0)
        return glm::vec3(0, 0, 0);
    int x = static_cast<int>(u * (width - 1)) % width;
    int y = static_cast<int>(v * (height - 1)) % height;
    return pixels[y * width + x];
}