#include "../include/utility.h"
#include "../include/world.h"
#include "../include/MCL.h"
#include "../include/matplotlibcpp.h" //Graph Library

#include <iostream>
#include <math.h>
#include <random>

namespace plt = matplotlibcpp;

double utility::get_gaussian_random_number(double mean, double var)
{
    // Random Generators
    std::random_device rd;
    std::mt19937 gen(rd());
    // get rangom number from normal distribution
    std::normal_distribution<double> dist(mean, var);
    return dist(gen);
}

double utility::get_random_number()
{
    // Random Generators
    std::random_device rd;
    std::mt19937 gen(rd());
    // get random number from a uniform distribution
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen);
}

double utility::get_gaussian_probability(double mean, double var, double x)
{
    //std::cout << mean << " " << var << " " << x << std::endl;
    // Probability of x given normal ditribution with mean and variance
    double p = exp(-(pow((mean - x), 2)) / (pow(var, 2)) / 2.0) / sqrt(2.0 * M_PI * (pow(var, 2)));
    //std::cout << p << std::endl;
    return p;
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

void utility::visualization(Robot *robot, int step, std::vector<particle> *belief, std::vector<particle> *new_belief, World *w)
{
    //Draw the robot, landmarks, particles and resampled particles on a graph
    int n = belief->size();

    //Graph Format
    plt::title("MCL, step " + std::to_string(step));
    plt::xlim(0, 100);
    plt::ylim(0, 100);

    //Draw particles in green
    for (int i = 0; i < n; i++)
    {
        plt::plot({(*belief)[i].r.get_x()}, {(*belief)[i].r.get_y()}, "go");
    }

    //Draw resampled particles in yellow
    for (int i = 0; i < n; i++)
    {
        plt::plot({(*new_belief)[i].r.get_x()}, {(*new_belief)[i].r.get_y()}, "yo");
    }

    //Draw landmarks in red
    std::vector<double> lm = w->get_landmarks();
    for (int i = 1; i < sizeof(lm) / sizeof(lm[0]); ++i)
    {
        plt::plot({lm[i - 1]}, {lm[i]}, "ro");
    }

    //Draw robot position in blue
    plt::plot({robot->get_x()}, {robot->get_y()}, "bo");

    //Save the image and close the plot
    plt::save("./Images/Step" + std::to_string(step) + ".png");
    plt::clf();
}