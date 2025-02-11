#include "init_objects.h"
#include "sphere.h"
#include "ring.h"
#include <stack>

std::vector<Object*> init_objects_demo() {
    std::vector<Object*> objects;
    objects.push_back(new Sphere(glm::vec3(8, 0, -10), 1.0f, glm::vec3(0.0, 0.5, 1.0), 0.3f, 0.0f, glm::vec3(1, 0.0f, 0.0f))); // Земля
    objects[0]->texture = Texture("./textures/earth.jpg");
    objects[0]->name = "Земля";
    objects.push_back(new Ring(glm::vec3(16, 0, -10), glm::vec3(-0.5, 1, 0), 1.4f, 3.0f, glm::vec3(0.6, 0.5, 0.3), 0.0f, 0.2f, glm::vec3(1, 0.0f, 0.0f))); // Кольца Сатурна
    objects[1]->texture = Texture("./textures/saturn_rings.jpg");
    objects[1]->name = "Кольца Сатурна";
    objects.push_back(new Sphere(glm::vec3(8, 0, -10), 1.1f, glm::vec3(0.0, 0.5, 1.0), 0.0f, 0.7f, glm::vec3(1, 0.0f, 0.0f)));  // атмосфера
    objects[2]->name = "Атмосфера Земли";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 1.1f, glm::vec3(0.7, 0.7, 0.7), 1.0f, 0.0f, glm::vec3(2, 4.0f, -0.003f))); // Луна
    objects[3]->name = "Зеркальный шар";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 1.1f, glm::vec3(0.7, 0.7, 0.7), 0.0f, 1.0f, glm::vec3(2, 4.0f, 0.003f))); // Луна
    objects[4]->name = "Прозрачный шар";

    objects.push_back(new Sphere(glm::vec3(8, 0, -10), 1.1f, glm::vec3(0.7, 0.5, 1.0), 0.0f, 0.7f, glm::vec3(1, 2.0f, 4.0f)));  // атмосфера
    objects[2]->name = "Атмосфера Земли";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 1.1f, glm::vec3(0.3, 0.7, 0.7), 1.0f, 0.0f, glm::vec3(2, 6.0f, -0.003f))); // Луна
    objects[3]->name = "Зеркальный шар";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 1.1f, glm::vec3(0.7, 0.7, 0.7), 0.2f, 1.0f, glm::vec3(2, 2.0f, 3.003f))); // Луна
    objects[4]->name = "Прозрачный шар";



    int cur_main_ind = 0;
    std::stack<int> prev_main_inds;
    prev_main_inds.push(0);
    objects[0]->main_ind = -1;

    for (size_t i = 1; i < objects.size() - 1; ++i) {
        if (objects[i]->dynamic_param.x > objects[i - 1]->dynamic_param.x) {
            
            cur_main_ind = i - 1;
            prev_main_inds.push(cur_main_ind);
        } else if (objects[i]->dynamic_param.x == objects[i - 1]->dynamic_param.x)
        {
            // std::cout << prev_main_inds.top() << std::endl;
            cur_main_ind = prev_main_inds.top();
        }
        else {
            if (prev_main_inds.top() != 0)
                prev_main_inds.pop();
            cur_main_ind = prev_main_inds.top();
        }
        objects[i]->main_ind = cur_main_ind;
        // std::cout << cur_main_ind << std::endl;
    }
    return objects;
}


std::vector<Object*> init_objects() {
    std::vector<Object*> objects;
    // Солнце
    objects.push_back(new Sphere(glm::vec3(0, 0, 0), 3.0f, glm::vec3(1.0, 1.0, 0.0), 0.0f, 0.0f, glm::vec3(0, 0, 0))); // Солнце
    objects[0]->texture = Texture("./textures/sun.jpg");
    objects[0]->name = "Солнце";
    // Меркурий
    objects.push_back(new Sphere(glm::vec3(4, 0, -10), 0.4f, glm::vec3(0.6, 0.6, 0.6), 0.1f, 0.01f, glm::vec3(1, 4 * 4.0f, 0.01f))); // Меркурий
    objects[1]->texture = Texture("./textures/mercury.jpg");
    objects[1]->name = "Меркурий";
    // Венера
    objects.push_back(new Sphere(glm::vec3(6, 0, -10), 0.9f, glm::vec3(1.0, 0.9, 0.6), 0.1f, 0.007f, glm::vec3(1, 4 * 6.0f, 0.007f))); // Венера
    objects[2]->texture = Texture("./textures/venus.jpg");
    objects[2]->name = "Венера";
    // Земля
    objects.push_back(new Sphere(glm::vec3(8, 0, -10), 1.0f, glm::vec3(0.0, 0.5, 1.0), 0.3f, 0.0f, glm::vec3(1, 4 * 8.0f, 0.005f))); // Земля
    objects[3]->texture = Texture("./textures/earth.jpg");
    objects[3]->name = "Земля";
    objects.push_back(new Sphere(glm::vec3(8, 0, -10), 1.1f, glm::vec3(0.0, 0.5, 1.0), 0.0f, 0.7f, glm::vec3(1, 4 * 8.0f, 0.005f)));  // атмосфера
    objects[4]->name = "Атмосфера Земли";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 0.1f, glm::vec3(0.7, 0.7, 0.7), 0.3f, 0.005f, glm::vec3(2, 2.0f, -0.3f))); // Луна
    objects[5]->name = "Луна";

    objects.push_back(new Sphere(glm::vec3(10, 0, -10), 0.7f, glm::vec3(1.0, 0.3, 0.3), 0.2f, 0.0f, glm::vec3(1,  4 * 10.0f, 0.003f))); // Марс
    objects[6]->texture = Texture("./textures/mars.jpg");
    objects[6]->name = "Марс";
    objects.push_back(new Sphere(glm::vec3(10, 0, -10), 0.8f, glm::vec3(1.0, 0.3, 0.3), 0.0f, 0.7f, glm::vec3(1,  4 * 10.0f, 0.003f))); // Марс атмосфера
    objects[7]->name = "Атмосфера Марса";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 0.15f, glm::vec3(0.7, 0.7, 0.7), 0.3f, 0.0f, glm::vec3(2, 1.5f, -0.15f))); // Фобос
    objects[8]->name = "Фобос";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 0.1f, glm::vec3(0.75, 0.7, 0.7), 0.3f, 0.0f, glm::vec3(2, 2.0f, -0.3f))); // Деймос
    objects[9]->name = "Деймос";

    // Юпитер
    objects.push_back(new Sphere(glm::vec3(13, 0, -10), 1.5f, glm::vec3(0.9, 0.5, 0.2), 0.3f, 0.001f, glm::vec3(1, 4 * 12.0f, 0.002f))); // Юпитер
    objects[10]->texture = Texture("./textures/jupiter.jpg");
    objects[10]->name = "Юпитер";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 0.15f, glm::vec3(1.0, 0.8, 0.7), 0.35f, 0.0f, glm::vec3(2, 2.5f, -0.15f))); // Ио
    objects[11]->name = "Ио";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 0.1f, glm::vec3(0.8, 0.8, 0.7), 0.3, 0.0f, glm::vec3(2, 3.5f, -0.3f))); // Европа
    objects[12]->name = "Европа";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 0.15f, glm::vec3(0.8, 0.7, 0.8), 0.35f, 0.0f, glm::vec3(2, 4.5f, -0.2f))); // Ганимед
    objects[13]->name = "Ганимед";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 0.1f, glm::vec3(0.75, 0.7, 0.7), 0.3, 0.0f, glm::vec3(2, 5.5f, -0.35f))); // Калисто
    objects[14]->name = "Калисто";

    // Сатурн
    objects.push_back(new Sphere(glm::vec3(16, 0, -10), 1.2f, glm::vec3(1.0, 0.8, 0.3), 0.3f, 0.0f, glm::vec3(1, 4 * 14.0f, 0.001f))); // Сатурн
    objects[15]->texture = Texture("./textures/saturn.jpg");
    objects[15]->name = "Сатурн";
    objects.push_back(new Ring(glm::vec3(16, 0, -10), glm::vec3(-0.5, 1, 0), 1.4f, 3.0f, glm::vec3(0.6, 0.5, 0.3), 0.0f, 0.2f, glm::vec3(1, 4 * 14.0f, 0.001f))); // Кольца Сатурна
    objects[16]->texture = Texture("./textures/saturn_rings.jpg");
    objects[16]->name = "Кольца Сатурна";
    objects.push_back(new Sphere(glm::vec3(9, 0, -10), 0.1f, glm::vec3(0.75, 0.7, 0.7), 0.4, 0.0f, glm::vec3(2, 5.5f, -0.3f))); // Титан
    objects[17]->name = "Титан";
    // Уран
    objects.push_back(new Sphere(glm::vec3(18, 0, -10), 1.0f, glm::vec3(0.4, 0.8, 1.0), 0.2f, 0.001f, glm::vec3(1, 4 * 16.0f, 0.0015f))); // Уран
    objects[18]->texture = Texture("./textures/uran.jpg");
    objects[18]->name = "Уран";
    // Нептун
    objects.push_back(new Sphere(glm::vec3(20, 0, -10), 1.0f, glm::vec3(0.1, 0.3, 0.8), 0.2f, 0.001f, glm::vec3(1, 4 * 18.0f, 0.004f))); // Нептун
    objects[19]->texture = Texture("./textures/neptune.jpg");
    objects[19]->name = "Нептун";

    int cur_main_ind = 0;
    std::stack<int> prev_main_inds;
    prev_main_inds.push(0);
    objects[0]->main_ind = -1;

    for (size_t i = 1; i < objects.size() - 1; ++i) {
        if (objects[i]->dynamic_param.x > objects[i - 1]->dynamic_param.x) {
            
            cur_main_ind = i - 1;
            prev_main_inds.push(cur_main_ind);
        } else if (objects[i]->dynamic_param.x == objects[i - 1]->dynamic_param.x)
        {
            // std::cout << prev_main_inds.top() << std::endl;
            cur_main_ind = prev_main_inds.top();
        }
        else {
            if (prev_main_inds.top() != 0)
                prev_main_inds.pop();
            cur_main_ind = prev_main_inds.top();
        }
        objects[i]->main_ind = cur_main_ind;
        // std::cout << cur_main_ind << std::endl;
    }
    return objects;
}


void rotate_objects(std::vector<Object*>& objects, float delta_time) {
    for (auto& object : objects) { 
        object->rotate_texture(delta_time);
    }
}

void set_scale(std::vector<Object*>& objects, float scale){
    for (auto& object : objects) {
        object->scale = scale;
    }
}


void set_orbit_scale(std::vector<Object*>& objects, float orbit_scale){
    for (auto& object : objects) {
        object->orbit_scale = orbit_scale;
    }
}

void update_planet_positions(std::vector<Object*>& objects, float delta_time) {
    for (auto& object : objects) {
        if (object->main_ind != -1) {
            Object* main_object = objects[object->main_ind];
            float angle = object->dynamic_param.z * delta_time;
            if (angle >= 360)
                angle = 0.0f;
            float delta_x = object->dynamic_param.y * object->orbit_scale * cos(angle);
            float delta_z = object->dynamic_param.y * object->orbit_scale * sin(angle);

            // Обновляем положение планеты
            object->update_coord(main_object, delta_x, 0, delta_z);
        }
    }
}

#include <vector>
#include <string>

std::vector<std::string> getObjectDescriptions() {
    return {
        "Солнце:\nРазмеры: диаметр около 1 392 700 км.\nСостав: в основном водород и\nгелий.\nФакты: \n"
        "1. Солнце содержит более 99% массы\nвсей Солнечной системы.\n"
        "2. Энергия от Солнца достигает Земли за ~8 минут.\n"
        "3. Поверхность Солнца называется фотосферой.",
        
        "Меркурий:\nРазмеры: диаметр около 4 880 км.\nСостав: каменистая кора и железное \nядро.\nФакты: \n"
        "1. Самая высокая температура днем - до 430°C.\n"
        "2. Ночью температура падает до -180°C.\n"
        "3. Нет атмосферы, только экзосфера.",
        
        "Венера:\nРазмеры: диаметр около 12 104 км.\nСостав: каменистая планета с плотной атмосферой\nиз углекислого газа.\nФакты: \n"
        "1. Средняя температура на поверхности - \nоколо 470°C.\n"
        "2. Атмосферное давление в 92 раза \nбольше земного.\n"
        "3. Облака содержат серную кислоту.",
        
        "Земля:\nРазмеры: диаметр около 12 742 км.\nСостав: ядро, мантия и кора.\nФакты: \n"
        "1. Единственная известная планета с \nжидкой водой на поверхности.\n"
        "2. Имеет сильное магнитное поле.\n"
        "3. Обладает атмосферой, богатой \nкислородом.",
        
        "Атмосфера Земли:\nСостав: 78% азота, 21% кислорода\nи следы других газов.\nФакты: \n"
        "1. Содержит озоновый слой, защищающий \nот ультрафиолета.\n"
        "2. Делится на тропосферу, стратосферу \nи другие слои.\n"
        "3. Обеспечивает условия для жизни.",
        
        "Луна:\nРазмеры: диаметр около 3 474 км.\nСостав: каменистая поверхность с реголитом.\nФакты: \n"
        "1. Постоянно обращена к Земле одной \nстороной.\n"
        "2. На поверхности есть кратеры от \nметеоритов.\n"
        "3. Нет атмосферы, только тонкий \nслой газов.",
        
        "Марс:\nРазмеры: диаметр около 6 779 км.\nСостав: каменистая кора и железно-никелевое ядро.\nФакты: \n"
        "1. Известен как «Красная планета» \nиз-за оксида железа.\n"
        "2. Имеет самую высокую гору в Солнечной \nсистеме - Олимп.\n"
        "3. Есть следы древних водных \nпотоков.",
        
        "Атмосфера Марса:\nСостав: 95% углекислого газа, азот и аргон.\nФакты: \n"
        "1. Очень разрежена, давление \nсоставляет менее 1% от земного.\n"
        "2. Часто возникают пылевые бури.\n"
        "3. Содержит мало кислорода.",
        
        "Фобос:\nРазмеры: 27×22×18 км.\nСостав: камень и пыль.\nФакты: \n"
        "1. Орбита постепенно уменьшается, \nи спутник упадет на Марс.\n"
        "2. На поверхности есть крупный \nкратер Стикни.\n"
        "3. Оборот вокруг Марса занимает \nвсего 7,7 часа.",
        
        "Деймос:\nРазмеры: 15×12×11 км.\nСостав: камень и пыль.\nФакты: \n"
        "1. Орбита медленно удаляется от \nМарса.\n"
        "2. Поверхность более гладкая, \nчем у Фобоса.\n"
        "3. Имеет вытянутую форму.",
        
        "Юпитер:\nРазмеры: диаметр около 139 820 км.\nСостав: водород и гелий.\nФакты: "
        "1. Самая большая планета Солнечной \nсистемы.\n"
        "2. Имеет Большое Красное Пятно - \nогромный шторм.\n"
        "3. Обладает сильным магнитным \nполем.",
        
        "Ио:\nРазмеры: диаметр около 3 643 км.\nСостав: вулканическая поверхность.\nФакты: "
        "1. Самое вулканически активное тело \nв Солнечной системе.\n"
        "2. Поверхность покрыта серой и лавой.\n"
        "3. Влияет на магнитное поле Юпитера.",
        
        "Европа:\nРазмеры: диаметр около 3 121 км.\nСостав: ледяная кора и жидкий океан под ней.\nФакты: "
        "1. Возможное наличие подледной жизни.\n"
        "2. Поверхность покрыта трещинами.\n"
        "3. Орбита подвергается сильным \nприливным силам.",
        
        "Ганимед:\nРазмеры: диаметр около 5 268 км.\nСостав: лед и камень.\nФакты: "
        "1. Крупнейший спутник в Солнечной \nсистеме.\n"
        "2. Имеет собственное магнитное поле.\n"
        "3. Внешняя кора состоит изо льда.",
        
        "Калисто:\nРазмеры: диаметр около 4 821 км.\nСостав: лед и камень.\nФакты: "
        "1. Поверхность покрыта множеством \nкратеров.\n"
        "2. Очень старая, почти не меняется \nмиллиарды лет.\n"
        "3. Орбита находится вне радиационного \nпояса Юпитера.",
        
        "Сатурн:\nРазмеры: диаметр около \n116 460 км.\nСостав: водород и гелий.\nФакты: "
        "1. Известен своими кольцами.\n"
        "2. Самая низкая плотность среди \nпланет.\n"
        "3. Ветры на Сатурне достигают 1800 км/ч.",
        
        "Кольца Сатурна:\nСостав: лед и \nпыль.\nФакты: "
        "1. Простираются на сотни тысяч \nкилометров.\n"
        "2. Состоят из миллиардов частиц.\n"
        "3. Возраст колец - несколько \nсотен миллионов лет.",
        
        "Титан:\nРазмеры: диаметр около 5 151 км.\nСостав: плотная атмосфера из\nазота и метана.\nФакты: "
        "1. Имеет реки и озера из жидкого \nметана.\n"
        "2. Самый крупный спутник \nСатурна.\n"
        "3. Атмосфера плотнее земной.",
        
        "Уран:\nРазмеры: диаметр около \n50 724 км.\nСостав: водород, гелий и метан.\nФакты: "
        "1. Ось вращения наклонена \nпочти на 98°.\n"
        "2. Метан придает планете \nголубой цвет.\n"
        "3. Имеет слабую систему колец.",
        
        "Нептун:\nРазмеры: диаметр около 49 244 км.\nСостав: водород, гелий и метан.\nФакты: "
        "1. Самые сильные ветры в \nСолнечной системе - до 2 100 км/ч.\n"
        "2. Обладает темно-синим \nцветом из-за метана.\n"
        "3. Имеет активную атмосферу \nс яркими штормами."
    };
}
