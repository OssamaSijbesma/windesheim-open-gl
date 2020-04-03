#include "objectmanager.h"
#include "pavement.h"
#include "grass.h"
#include "woodchips.h"
#include "plane.h" 
#include "chickenleg.h"
#include "chickenbody.h"

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

    std::vector<object*>* chicken = create_chicken();
    objects.insert(objects.end(), chicken->begin(), chicken->end());

}

vector<object*>* objectmanager::create_house()
{
    vector<object*>* house = new vector<object*>();

    return house;
}

std::vector<object*>* objectmanager::create_chicken()
{
    vector<object*>* chicken = new vector<object*>();

    object* cl = new chickenleg();
    cl->position(12,0.8f,14);
    chicken->push_back(cl);

    object* cl2 = new chickenleg();
    cl2->position(14, 0.8f, 14);
    chicken->push_back(cl2);

    object* cb = new chickenbody();
    cb->position(14.5f, 2.5f, 14);
    cb->rotate_z(270);
    //cb->rotate_x(-90);
    cb->rotate_y(90);
    cb->scale(3);
    chicken->push_back(cb);

    object* cb2 = new chickenbody();
    cb2->position(11.5f, 2.5f, 14);
    cb2->rotate_z(270);
    //cb->rotate_x(-90);
    cb2->rotate_y(90);
    cb2->scale(3);
    chicken->push_back(cb2);

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






