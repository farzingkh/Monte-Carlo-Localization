#include "../include/world.h"
#include <assert.h>

void World::set_landmarks(double x, double y)
{
    landmarks__.push_back(x);
    landmarks__.push_back(y);
    // check invariant condition
    assert(landmarks__.size() % 2 == 0);
}

std::vector<double> World::get_landmarks()
{
    return landmarks__;
}

double World::get_x() { return x__; }

double World::get_y() { return y__; }

