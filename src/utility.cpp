#include "../include/utility.h"
#include "../include/world.h"
#include "../include/MCL.h"
#include <math.h>
#include <random>

double utility::get_gaussian_random_number(double mean, double var)
{
    // get rangom number from normal distribution
    std::default_random_engine gen;
    std::normal_distribution<double> dist(mean, var);
    return dist(gen);
}

double utility::get_random_number()
{
    // get random number from a uniform distribution
    std::default_random_engine gen;
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen);
}

double utility::get_gaussian_probability(double mean, double var, double x)
{
    // Probability of x given normal ditribution with mean and variance
    return exp(-(pow((mean - x), 2)) / (pow(var, 2)) / 2.0) / sqrt(2.0 * M_PI * (pow(var, 2)));
}

double utility::evaluation(Robot *r, std::vector<particle> *p, World *world)
{
    //Calculate the mean error of the system
    double sum = 0.0;
    for (int i = 0; i < p->size(); i++)
    {
        //the second part is because of world's cyclicity
        double dx = fmod(((*p)[i].r.get_x() - r->get_x() + (world->get_x() / 2.0)), world->get_x()) - (world->get_x() / 2.0);
        double dy = fmod(((*p)[i].r.get_y() - r->get_y() + (world->get_y() / 2.0)), world->get_y()) - (world->get_y() / 2.0);
        double err = sqrt(pow(dx, 2) + pow(dy, 2));
        sum += err;
    }
    return sum / p->size();
}