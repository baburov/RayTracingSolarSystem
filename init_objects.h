#ifndef INIT_OBJECTS_H
#define INIT_OBJECTS_H
#include "object.h"
std::vector<Object*> init_objects();
std::vector<Object*> init_objects_demo();
void update_planet_positions(std::vector<Object*>& objects, float delta_time);
void rotate_objects(std::vector<Object*>& objects, float delta_time);
void set_scale(std::vector<Object*>& objects, float scale);
void set_orbit_scale(std::vector<Object*>& objects, float orbit_scale);
std::vector<std::string> getObjectDescriptions();
#endif
