#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <thread>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include <sstream>
#include "texture.h"
#include "object.h"
#include "sphere.h"
#include "ring.h"
#include "ray_tracing_utils.h"
#include "init_objects.h"
#include "background.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

static int selected_object_index = 0;
static std::string object_info;

// Функция для получения информации об объекте
std::string getObjectInfo(const Object* obj, int index) {
    std::ostringstream info;
    info << getObjectDescriptions()[index];
    return info.str();
}

void setupImGuiFonts() {
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("./fonts/Roboto-Regular.ttf", 16.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
    ImGui_ImplOpenGL3_CreateFontsTexture();
}





int main() {
    std::vector<Object*> scene_objects;
    BackgroundTexture background("./textures/big_space.png");
    glm::vec3 LIGHT_POSITION(0.0f, 0.0f, 0.0f);
    const glm::vec3 LIGHT_COLOR(1.0f, 1.0f, 1.0f);
    const glm::vec3 BACKGROUND_COLOR(0.0f, 0.0f, 0.0f);
    float camera_angle_x = 0.0f;
    float camera_angle_y = 0.0f;
    float time_speed = 1.0f;
    glm::vec3 folow_direction(0, 10, 0);
    static float radius = 10.0f;  // Радиус (расстояние от объекта)
    static float theta = 0.0f;    // Азимутальный угол (вокруг объекта по горизонтали)
    static float phi = glm::radians(90.0f);  // Зенитный угол (вверх-вниз)
    glm::mat4 rotation_x = glm::rotate(glm::mat4(1.0f), camera_angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rotation_y = glm::rotate(glm::mat4(1.0f), camera_angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 camera_rotation = rotation_y * rotation_x;


    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(1600, 800, "Ray Tracing with GUI", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    setupImGuiFonts(); 

    float delta_time = 20100.0f;
    scene_objects = init_objects();
    int width = 1600, height = 800;
    float fov = 50.0f;
    float aspect_ratio = float(width) / float(height);
    float scale = tan(glm::radians(fov * 0.5f));
    glm::vec3 ray_origin = glm::vec3(0.0f, -1.0f, 100.0f);
    glm::vec3 follow_direction = glm::vec3(0.0f, 0.0f, 15.0f);
    static bool follow_object = false;  
    static bool real_size = false;
    static bool demo_size = false;
    static float orbit_scale = 1.0f;
    static float radius_scale = 1.0f;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwGetFramebufferSize(window, &width, &height);
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) camera_angle_y += 0.05f;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) camera_angle_y -= 0.05f;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) camera_angle_x -= 0.05f;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) camera_angle_x += 0.05f;
        if (!follow_object) {

            rotation_x = glm::rotate(glm::mat4(1.0f), camera_angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
            rotation_y = glm::rotate(glm::mat4(1.0f), camera_angle_y, glm::vec3(0.0f, 1.0f, 0.0f));
            camera_rotation = rotation_y * rotation_x;

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) ray_origin += glm::vec3(rotation_y * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) ray_origin -= glm::vec3(rotation_y * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) ray_origin += glm::vec3(rotation_y * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) ray_origin -= glm::vec3(rotation_y * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) ray_origin += glm::vec3(rotation_y * glm::vec4(0.0f, -1.0f, 0.0f, 0.0f));
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ray_origin -= glm::vec3(rotation_y * glm::vec4(0.0f, -1.0f, 0.0f, 0.0f));
        }
        else {
            rotation_x = glm::rotate(glm::mat4(1.0f), camera_angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
            rotation_y = glm::rotate(glm::mat4(1.0f), camera_angle_y + 90, glm::vec3(0.0f, 1.0f, 0.0f));
            camera_rotation = rotation_y * rotation_x;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) phi += 0.02f;  // Вверх
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) phi -= 0.02f;  // Вниз
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) theta += 0.02f; // Влево
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) theta -= 0.02f; // Вправо
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) radius += 0.5f; // Увеличить радиус
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) radius -= 0.5f; // Уменьшить радиус

            // Ограничения
            radius = glm::max(radius, 1.0f); // Радиус не меньше 1
            phi = glm::clamp(phi, glm::radians(10.0f), glm::radians(170.0f)); // Угол phi в диапазоне [10°, 170°]
            folow_direction = glm::vec3(
                radius * sin(phi) * cos(theta), // X
                radius * cos(phi),              // Y
                radius * sin(phi) * sin(theta)  // Z
            );

            ray_origin = scene_objects[selected_object_index]->center + folow_direction;

        }
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame(); 
        ImGui::NewFrame();  

        ImGui::Begin("Управление");  


        if (ImGui::Button("Солнечная система")) {
            glm::vec3 ray_origin = glm::vec3(0.0f, -1.0f, 100.0f);
            glm::vec3 follow_direction = glm::vec3(0.0f, 0.0f, 15.0f);
            selected_object_index = 0;
            real_size = true;
            demo_size = false;
            orbit_scale = 1.0f; 
            radius_scale = 1.0f;
            scene_objects = init_objects();
            ray_origin = glm::vec3(0.0f, -1.0f, 100.0f);
            LIGHT_POSITION = glm::vec3(0.0f, 0.0f, 4.0f);
        }

        if (ImGui::Button("Демонстрационный режим")) {
            selected_object_index = 0;
            demo_size = true;
            real_size = false;
            orbit_scale = 10.0f; 
            radius_scale = 5.0f; 
            scene_objects = init_objects_demo();
            ray_origin = glm::vec3(0.0f, -1.0f, 100.0f);
            LIGHT_POSITION = glm::vec3(0.0f, 4.0f, 4.0f);
        }
        if (demo_size)
            LIGHT_POSITION.y = 15 * sin(delta_time/4);

        // Выпадающий список с объектами
        if (ImGui::BeginCombo("Выбрать объект", selected_object_index >= 0 ? scene_objects[selected_object_index]->name.c_str() : "None")) {
            for (int i = 0; i < scene_objects.size(); ++i) {
                bool is_selected = (selected_object_index == i);
                if (ImGui::Selectable(scene_objects[i]->name.c_str(), is_selected)) {
                    selected_object_index = i;
                    folow_direction = glm::vec3(0.0f, 0.0f, 15.0f);
                    ray_origin = scene_objects[i]->center + folow_direction; 
                    object_info = getObjectInfo(scene_objects[i], selected_object_index);
                }
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::Checkbox(u8"Следовать", &follow_object);
        ImGui::End();

        if (selected_object_index >= 0) {
            ImGui::Begin("Информация об объекте");
            ImGui::Text("%s", object_info.c_str());
            ImGui::End();
        }
        ImGui::Begin("Настройки сцены");
        ImGui::SliderFloat("Скорость", &time_speed, 0.1f, 10.0f);
        ImGui::SliderFloat("Масштаб орбит", &orbit_scale, 0.1f, 20.0f);
        ImGui::SliderFloat("Масштаб объектов", &radius_scale, 0.1f, 20.0f);
        ImGui::SliderFloat("Угол обзора", &fov, 10.0f, 100.0f);
        ImGui::Text("Управление камерой: \n W, A, S, D  - перемещение\n стрелки  - поворот\n Shift - вниз/n Space - вверх");
        ImGui::End();
        scale = tan(glm::radians(fov * 0.5f));
        std::vector<unsigned char> pixelBuffer(width * height * 3);

        int numThreads = std::thread::hardware_concurrency() * 2;
        int linesPerThread = height / numThreads;
        std::vector<std::thread> threads;


        for (int t = 0; t < numThreads; ++t) {
            int startY = t * linesPerThread;
            int endY = (t == numThreads - 1) ? height : startY + linesPerThread;
            threads.emplace_back(renderSection, std::ref(pixelBuffer), startY, endY, width, height, aspect_ratio, scale,
                                 camera_rotation, ray_origin, std::ref(scene_objects), std::ref(LIGHT_POSITION), std::ref(background));
        }

        for (auto& thread : threads) {
            thread.join();
        }
        // scene_objects[0]->center.y += 1;
        delta_time += time_speed;
        set_scale(scene_objects, radius_scale);
        set_orbit_scale(scene_objects, orbit_scale);
        update_planet_positions(scene_objects, delta_time);
        rotate_objects(scene_objects, delta_time);
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixelBuffer.data());
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (auto* obj : scene_objects) {
        delete obj;
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
