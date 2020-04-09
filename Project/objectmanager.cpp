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
    object* cl = new skybox();
    cl->scale(50);
    cl->position(10, 0, 30);
    cl->rotate_z(180);
    objects.push_back(cl);

    std::vector<object*>* floor = create_floor();
    objects.insert(objects.end(), floor->begin(), floor->end());

    std::vector<object*>* chicken = create_chicken(14, 15);
    objects.insert(objects.end(), chicken->begin(), chicken->end());

    std::vector<object*>* bike = create_bike(1.5, 70);
    objects.insert(objects.end(), bike->begin(), bike->end());

    std::vector<object*>* house = create_house(32.5,2);
    objects.insert(objects.end(), house->begin(), house->end());

    std::vector<object*>* house2 = create_house(32.5, 12);
    objects.insert(objects.end(), house2->begin(), house2->end());
}

std::vector<object*>* objectmanager::create_other()
{
    object* cl = new football();
    cl->scale(0.2f);
    cl->position(16.0f, 0.2f, 31.0f);
    //house->push_back(cl);

    return nullptr;
}

vector<object*>* objectmanager::create_house(float x, float z)
{
    vector<object*>* house = new vector<object*>();

    object* placeholder;
    for (int width = -4; width < 4; width++)
    {
        // Create pole in front of the house
        if (width == -4 || width == 4)
        {
            placeholder = new pole();
            placeholder->position(x - 9, 3, z - width);
            placeholder->scale_y(2);
            placeholder->scale_x(0.2);
            placeholder->scale_z(0.2);
            house->push_back(placeholder);
        }

        // Create bush in front of the house
        if (width != 1 && width != 0) {
            placeholder = new bush();
            placeholder->position(x - 9, 0.5, z - width);
            placeholder->scale(0.5);
            house->push_back(placeholder);
        }

        if (width % 2 == 0)
        {
            // Create canpoy above the porch
            placeholder = new canopy();
            placeholder->position(x - 8, 5.5, z - width);
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

std::vector<object*>* objectmanager::create_floor()
{
    vector<object*>* floor_tiles = new vector<object*>();

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

            tile->position(x * 2.0f, 0, z * 2.0f);
            floor_tiles->push_back(tile);
        }

    return floor_tiles;
}






