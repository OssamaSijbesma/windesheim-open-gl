#include "objectmanager.h"
#include "pavement.h"
#include "grass.h"
#include "woodchips.h"
#include "chickenleg.h"
#include "chickenbase.h"
#include "chickenbody.h"
#include "slide.h"

objectmanager::objectmanager()
{
}

objectmanager::~objectmanager()
{
}

std::vector<object*> objectmanager::get_objects()
{
    return objects;
}

void objectmanager::init_world()
{
    std::vector<object*>* floor = create_floor();
    objects.insert(objects.end(), floor->begin(), floor->end());

    std::vector<object*>* chicken = create_chicken(14, 15);
    objects.insert(objects.end(), chicken->begin(), chicken->end());

}

vector<object*>* objectmanager::create_house()
{
    vector<object*>* house = new vector<object*>();

    return house;
}

std::vector<object*>* objectmanager::create_chicken(float x, float z)
{
    vector<object*>* chicken = new vector<object*>();

    object* cl = new chickenleg();
    cl->position(x + 0.6f, 0.8f, z);
    chicken->push_back(cl);

    object* cl2 = new chickenleg();
    cl2->position(x - 0.6f, 0.8f, z);
    chicken->push_back(cl2);

    object* cb = new chickenbody();
    cb->position(x + 1.01f, 2.5f, z);
    cb->rotate_y(90);
    cb->scale(3);
    chicken->push_back(cb);

    object* cb2 = new chickenbody();
    cb2->position(x - 1.01f, 2.5f, z);
    cb2->rotate_y(90);
    cb2->scale(3);
    chicken->push_back(cb2);

    object* ci = new chickenbase();
    ci->position(x, 1.8f, z);
    ci->scale_y(0.2f);
    ci->scale_z(1.4f);
    chicken->push_back(ci);

    object* ci2 = new chickenbase();
    ci2->position(x, 2.5f, z + 1.2f);
    ci2->scale_y(0.6f);
    ci2->scale_z(0.5f);
    chicken->push_back(ci2);

    object* ci3 = new chickenbase();
    ci3->position(x, 2.2f, z + 0.7f);
    ci3->scale_y(0.3f);
    ci3->scale_z(0.5f);
    chicken->push_back(ci3);

    object* s1 = new slide();
    s1->position(x, 1.5f, z + 3.3f);
    s1->rotate_y(-90);
    s1->scale(0.9f);
    s1->scale_z(0.7f);
    chicken->push_back(s1);

    return chicken;
}

std::vector<object*>* objectmanager::create_floor()
{
    vector<object*>* floor_tiles = new vector<object*>();

    for (int z = 0; z < sizeof(floor) / sizeof(floor[0]); z++)
        for (int x = 0; x < sizeof(floor[0]) / sizeof(int); x++)
        {
            object* tile = nullptr;

            switch (floor[z][x])
            {
            case 0: tile = new pavement(); break;
            case 1: tile = new grass(); break;
            case 2: tile = new woodchips(); break;
            }

            tile->position(x * 2.0f, 0, z * 2.0f);
            floor_tiles->push_back(tile);
        }

    return floor_tiles;
}






