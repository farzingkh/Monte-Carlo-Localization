#ifndef UTILITY_H
#define UTILITY_H

#include <vector>

class World;
struct particle;
class Robot;

namespace utility
{
    // Get random number from normal distribution given its mean and variance
    double get_gaussian_random_number(double mean, double var);
    // get random number between [0,1.0]
    double get_random_number();
    // Get normal distribution probability of x given mean and variance
    double get_gaussian_probability(double mean, double var, double x);
    // evaluate each belief
    double evaluation(Robot *r, std::vector<particle> *belief, World *w);

} // namespace utility

#endif