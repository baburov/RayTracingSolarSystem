#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texture.h"

bool Texture::load_image(const std::string& filepath) {
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

glm::vec3 Texture::get_pixel(float u, float v) const {
    int x = static_cast<int>(u * (width - 1)) % width;
    int y = static_cast<int>(v * (height - 1)) % height;
    return pixels[y * width + x];
}
