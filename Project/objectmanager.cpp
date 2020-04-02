#include "objectmanager.h"
#include "pavement.h"
#include "grass.h"
#include "woodchips.h"
#include "plane.h" 


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

}

vector<object*>* objectmanager::create_house()
{
    vector<object*>* house = new vector<object*>();

    return house;
}

vector<object*>* objectmanager::create_playground()
{
    vector<object*>* playground = new vector<object*>();

    return playground;
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






