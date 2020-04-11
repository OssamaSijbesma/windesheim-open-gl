#include "objectmanager.h"
#include "pavement.h"
#include "grass.h"
#include "woodchips.h"
#include "chickenleg.h"
#include "chickenbase.h"
#include "chickenbody.h"
#include "slide.h"
#include "football.h"
#include "bikeframe.h"
#include "wheel.h"
#include "skybox.h"
#include "firstfloor.h"
#include "groundfloor.h"
#include "bush.h"
#include "roof.h"
#include "canopy.h"
#include "pole.h"
#include "aircraft.h"

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
    // Add skybox
    objects.push_back(create_skybox());

    // Add floor
    std::vector<object*>* floor = create_floor();
    objects.insert(objects.end(), floor->begin(), floor->end());

    // Add terraces
    std::vector<object*>* terrace_west = create_terrace(22, 0, East, 9);
    objects.insert(objects.end(), terrace_west->begin(), terrace_west->end());
    
    std::vector<object*>* terrace_east = create_terrace(-22, -8, West, 7);
    objects.insert(objects.end(), terrace_east->begin(), terrace_east->end());

    // Add garages
    std::vector<object*>* garage = create_garage(-14, 21, North, 5);
    objects.insert(objects.end(), garage->begin(), garage->end());    
    
    std::vector<object*>* garage2 = create_garage(-10, 37, West, 4);
    objects.insert(objects.end(), garage2->begin(), garage2->end());

    // Add chicken
    std::vector<object*>* chicken = create_chicken(3, -20);
    objects.insert(objects.end(), chicken->begin(), chicken->end());

    // Add bike
    std::vector<object*>* bike = create_bike(10, 40);
    objects.insert(objects.end(), bike->begin(), bike->end());
    
    // Add football
    objects.push_back(create_football(5, 4));

    // Add aircraft
    objects.push_back(create_aircraft(0, 0));
}

std::vector<object*>* objectmanager::create_terrace(float x, float z, direction d, int amount)
{
    vector<object*>* terrace = new vector<object*>();
    std::vector<object*>* house;

    int start_z = amount * 4 - 3;

    for (int i = 0; i < amount; i++)
    {
        house = create_house(x, z + i * 8 - start_z, d);
        terrace->insert(terrace->end(), house->begin(), house->end());
    }

    return terrace;
}

vector<object*>* objectmanager::create_house(float x, float z, direction d)
{
    vector<object*>* house = new vector<object*>();

    object* placeholder;
    for (int width = -4; width < 4; width++)
    {
        // Create pole in front of the house
        if (width == -4 || width == 4)
        {
            placeholder = new pole();
            if (d == East)
                placeholder->position(x - 9, 3, z - width + 0.5);
            else
                placeholder->position(x + 9, 3, z - width + 0.5);
            placeholder->scale_y(2);
            placeholder->scale_x(0.2);
            placeholder->scale_z(0.2);
            house->push_back(placeholder);
        }

        // Create bush in front of the house
        if (width != 1 && width != 0) {
            placeholder = new bush();
            if (d == East)
                placeholder->position(x - 9, 0.5, z - width + 0.5);
            else
                placeholder->position(x + 9, 0.5, z - width + 0.5);
            placeholder->scale(0.5);
            house->push_back(placeholder);
        }

        if (width % 2 == 0 )
        {
            // Create canpoy above the porch
            placeholder = new canopy();
            if (d == East)
                placeholder->position(x - 8, 5.5, z - width);
            else
                placeholder->position(x + 8, 5.5, z - width);
            placeholder->scale_x(2);
            placeholder->scale_y(0.5);
            house->push_back(placeholder);


            for (int height = 1; height <= 9; height += 2)
            {
                for (int depth = -5; depth <= 5; depth += 10)
                {
                    if (height <= 6)
                    {
                        // Create the ground floor
                        placeholder = new groundfloor();
                        placeholder->position(x + depth, height, z - width);
                        house->push_back(placeholder);
                    }
                    else
                    {
                        // Create the first floor
                        placeholder = new firstfloor();
                        placeholder->position(x + depth, height, z - width);
                        placeholder->rotate_z(180);
                        house->push_back(placeholder);
                    }
                }
            }

            // Create the roof
            for (int height = 11, depth = 5; height <= 16; height += 2, depth -= 2)
            {
                placeholder = new roof();
                placeholder->position(x + depth, height, z - width);
                placeholder->rotate_z(-45);
                placeholder->scale_x(1.42);
                house->push_back(placeholder);

                placeholder = new roof();
                placeholder->position(x - depth, height, z - width);
                placeholder->rotate_z(45);
                placeholder->scale_x(1.42);
                house->push_back(placeholder);
            }
        }
    }

    return house;
}

std::vector<object*>* objectmanager::create_garage(float x, float z, direction d, int amount)
{
    vector<object*>* garage = new vector<object*>();
    object* placeholder;

    int start_length = amount * 2 - 2;

    for (int i = 0; i < amount; i++)
    {
        // Create canpoy above the porch
        placeholder = new canopy();

        switch (d)
        {
        case North: placeholder->position(x, 5.5, z + i * 4); break;
        case East: placeholder->position(x - i * 4, 5.5, z); break;
        case South: placeholder->position(x, 5.5, z - i * 4); break;
        case West: placeholder->position(x + i * 4, 5.5, z); break;
        }

        placeholder->scale_x(2);
        placeholder->scale_z(2);
        placeholder->scale_y(0.5);
        garage->push_back(placeholder);


        for (int j = -2; j < 2; j++)
        {
            placeholder = new bush();
            placeholder->scale(0.5);

            switch (d)
            {
            case North: placeholder->position(x + 1, 0.5, z + i * 4 + j); break;
            case East: placeholder->position(x - i * 4 + j, 0.5, z + 1); break;
            case South: placeholder->position(x - 1, 0.5, z + i * 4 + j); break;
            case West: placeholder->position(x + i * 4 + j, 0.5, z - 1); break;
            }

            garage->push_back(placeholder);
        }

        placeholder = new pole();

        switch (d)
        {
        case West:placeholder->position(x + i * 4, 3, z - 1); break;
        case East: placeholder->position(x + i * 4, 3, z + 1); break;
        case North: placeholder->position(x + 1, 3, z + i * 4); break;
        case South: placeholder->position(x - 1, 3, z + i* 4); break;
        }

        placeholder->scale_y(2);
        placeholder->scale_x(0.2);
        placeholder->scale_z(0.2);
        garage->push_back(placeholder);
    }    
    return garage;
}

vector<object*>* objectmanager::create_bike(float x, float z)
{
    vector<object*>* bike = new vector<object*>();

    // Create bikeframe
    object* bike_frame = new bikeframe();
    bike_frame->scale(0.4f);
    bike_frame->position(x, 0.5f, z);
    bike_frame->rotate_y(90);
    bike->push_back(bike_frame);

    // Create front wheel
    object* front_wheel = new wheel();
    front_wheel->scale(0.4f);
    front_wheel->rotate_y(90);
    front_wheel->position(x, 0.5f, z - 0.51f);
    bike->push_back(front_wheel); 
    
    // Create back wheel
    object* back_wheel = new wheel();
    back_wheel->scale(0.4f);
    back_wheel->rotate_y(90);
    back_wheel->position(x , 0.5f, z + 0.85f);
    bike->push_back(back_wheel);

    return bike;
}

std::vector<object*>* objectmanager::create_chicken(float x, float z)
{
    vector<object*>* chicken = new vector<object*>();

    object* chickenleg1 = new chickenleg();
    chickenleg1->position(x + 0.6f, 0.8f, z);
    chicken->push_back(chickenleg1);

    object* chickenleg2 = new chickenleg();
    chickenleg2->position(x - 0.6f, 0.8f, z);
    chicken->push_back(chickenleg2);

    object* chickenbody1 = new chickenbody();
    chickenbody1->scale(3);
    chickenbody1->rotate_y(90);
    chickenbody1->position(x + 1.01f, 2.5f, z);
    chicken->push_back(chickenbody1);

    object* chickenbody2 = new chickenbody();
    chickenbody2->position(x - 1.01f, 2.5f, z);
    chickenbody2->rotate_y(90);
    chickenbody2->scale(3);
    chicken->push_back(chickenbody2);

    object* chickenbase1 = new chickenbase();
    chickenbase1->position(x, 1.8f, z);
    chickenbase1->scale_y(0.2f);
    chickenbase1->scale_z(1.4f);
    chicken->push_back(chickenbase1);

    object* chickenbase2 = new chickenbase();
    chickenbase2->position(x, 2.5f, z + 1.2f);
    chickenbase2->scale_y(0.6f);
    chickenbase2->scale_z(0.5f);
    chicken->push_back(chickenbase2);

    object* chickenbase3 = new chickenbase();
    chickenbase3->position(x, 2.2f, z + 0.7f);
    chickenbase3->scale_y(0.3f);
    chickenbase3->scale_z(0.5f);
    chicken->push_back(chickenbase3);

    object* chickenslide = new slide();
    chickenslide->position(x, 1.5f, z + 3.3f);
    chickenslide->rotate_y(-90);
    chickenslide->scale(0.9f);
    chickenslide->scale_z(0.7f);
    chicken->push_back(chickenslide);

    return chicken;
}

object* objectmanager::create_football(float x, float z)
{
    object* cl = new football();
    cl->scale(0.2f);
    cl->position(x, 0.2f, z);
    return cl;
}

object* objectmanager::create_aircraft(float x, float z)
{
    object* p = new aircraft();
    p->scale(0.2f);
    p->rotate_y(225);
    p->position(x, 25.0f, z);
    return p;
}

object* objectmanager::create_skybox()
{
    object* cl = new skybox();
    cl->scale(50);
    cl->position(0, 0, 0);
    cl->rotate_z(180);
    return cl;
}

std::vector<object*>* objectmanager::create_floor()
{
    vector<object*>* floor_tiles = new vector<object*>();

    int start_z = sizeof(floor) / sizeof(floor[0]) - 1;
    int start_x = sizeof(floor[0]) / sizeof(int) - 1;


    // Create the floor based on a two dimensional array from the header
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

            tile->position(x * 2.0f - start_x, 0, z * 2.0f - start_z);
            floor_tiles->push_back(tile);
        }

    return floor_tiles;
}






