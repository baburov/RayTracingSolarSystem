#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include "object.h" // Базовый класс для всех объектов
#include "background.h"
#include <iostream>

glm::vec3 trace_ray(const glm::vec3& ray_origin, glm::vec3& ray_direction, int depth, std::vector<Object*>& objects, glm::vec3& light_position, BackgroundTexture& background) {
    if (depth > 6) return glm::vec3(0.0f); // Ограничиваем глубину рекурсии
    float base_light = 0.2f;
    float t_min = 1e9;
    Object* hit_object = nullptr;
    glm::vec3 hit_point, hit_normal(0,0,0);
    glm::vec3 hit_color(0,0,0);

    // Находим ближайшее пересечение
    for (Object* object : objects) {
        float t = object->intersect(ray_origin, ray_direction);
        if (t > 0.001f && t < t_min) {
            t_min = t;
            hit_object = object;
            hit_point = ray_origin + t * ray_direction;
            hit_normal = object->get_normal(hit_point, glm::normalize(light_position - hit_point));
            hit_color = object->get_color(hit_point);
        }
    }

    if (!hit_object) return background.get_pixel(ray_origin, ray_direction); // Цвет фона, если пересечений нет

    // Проверка на тень с учётом полупрозрачных объектов
    glm::vec3 light_dir = glm::normalize(light_position - hit_point);
    float light_intensity = 1.0f; // Начальная интенсивность света

    for (Object* object : objects) {
        if (object == hit_object || object->dynamic_param.x == 0) continue; // Пропускаем сам объект

        float shadow_t = object->intersect(hit_point + 0.001f * hit_normal, light_dir);
        if (shadow_t > 0.001f && shadow_t < glm::length(light_position - hit_point)) {
            // Если объект непрозрачен, полностью блокируем свет
            if (object->transparency == 0.0f) {
                light_intensity = base_light;
                break;
            }
            // Уменьшаем интенсивность света на основе прозрачности объекта, но оставляем немного тени
            light_intensity *= glm::mix(0.2f, 1.0f, object->transparency); // где 0.2f - минимальный уровень тени
        }
    }

    // Диффузное освещение с учётом теней и интенсивности света
    float diff_intensity = glm::max(glm::dot(hit_normal, light_dir), base_light) * light_intensity;
    if (hit_object->dynamic_param.x == 0 )
        diff_intensity = 1;
    diff_intensity = glm::max(diff_intensity, base_light);
    glm::vec3 diffuse_light = hit_color * diff_intensity;

    // Вычисление блика
    glm::vec3 view_dir = glm::normalize(ray_origin - hit_point);
    glm::vec3 reflect_dir = glm::reflect(-light_dir, hit_normal);
    float specular_intensity = pow(glm::max(glm::dot(view_dir, reflect_dir), 0.0f), hit_object->shininess);
    glm::vec3 specular_light = hit_object->specular_color * specular_intensity * light_intensity;

    // Отражение
    glm::vec3 reflection_color(0.0f);
    if (hit_object->reflectivity > 0) {
        glm::vec3 reflection_dir = glm::reflect(ray_direction, hit_normal);
        reflection_color = trace_ray(hit_point + 0.001f * hit_normal, reflection_dir, depth + 1, objects, light_position, background);
    }

    // Преломление
    glm::vec3 refraction_color(0.0f);
    if (hit_object->transparency > 0) {
        float ior = 1.01f; // Показатель преломления
        glm::vec3 refraction_dir = glm::refract(ray_direction, hit_normal, 1.0f / ior);
        refraction_color = trace_ray(hit_point - 0.001f * hit_normal, refraction_dir, depth + 1, objects, light_position, background);
    }

    // Итоговый цвет пикселя с добавлением блика
    return diffuse_light * (1.0f - hit_object->reflectivity - hit_object->transparency) +

           reflection_color * hit_object->reflectivity +
           refraction_color * hit_object->transparency +
           specular_light;  // Добавляем блик
}


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
) {
    // auto start = std::chrono::high_resolution_clock::now();
    for (int y = startY; y < endY; ++y) {
        for (int x = 0; x < width; ++x) {
            float px = (2 * (x + 0.5f) / (float)width - 1) * aspect_ratio * scale;
            float py = (1 - 2 * (y + 0.5f) / (float)height) * scale;

            glm::vec3 ray_direction = glm::normalize(glm::vec3(px, py, -1.0f));
            ray_direction = glm::vec3(camera_rotation * glm::vec4(ray_direction, 0.0f));

            glm::vec3 color = trace_ray(ray_origin, ray_direction, 0, scene_objects, LIGHT_POSITION, background);
            int index = (y * width + x) * 3;
            pixelBuffer[index] = static_cast<unsigned char>(glm::clamp(color.r * 255.0f, 0.0f, 255.0f));
            pixelBuffer[index + 1] = static_cast<unsigned char>(glm::clamp(color.g * 255.0f, 0.0f, 255.0f));
            pixelBuffer[index + 2] = static_cast<unsigned char>(glm::clamp(color.b * 255.0f, 0.0f, 255.0f));
        }
    }
    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // std::cout << "Время выполнения цикла: " << duration.count() << " микросекунд" << std::endl;
}