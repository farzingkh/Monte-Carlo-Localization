#include "../include/MCL.h"

MCL::MCL(std::vector<particle> X, command U, std::vector<double> Z) : X__(X), U__(U), Z__(Z), max_weight__(0.0) {}

void MCL::motion_update()
{
    // update particles with command input
    std::for_each(X__.begin(), X__.end(), [](particle &ptc) {
        ptc.r.move(U__.turn, U__.forward);
    });
}

void MCL::sensor_update()
{
    // keep track of maximum weight for resampling
    max_weight__ = 0.0;
    // update weights with probability of each observations using pdf
    std::for_each(X__.begin(), X__.end(), [](particle &ptc) {
        // sense environemnt with each particle
        std::vector<double> meas = ptc.r.sense(false);
        // calculate probability of robot measurements Z considering a pdf of mean observed distance from map and varance of sensor noise
        ptc.w = get_measurement_prob(meas);
        // update max weight
        ptc.w > max_weight ? max_weight__ = ptc.w : max_weight__ += 0.0;
    });
}

double MCL::get_measurement_pob(std::vector<double> measurement)
{
    std::assert(measurement.size() == Z__.size());
    // get sensor noise
    double var = X__[0].r.get_sensor_noise();
    double prob = 1.0;
    for (int i = 0; i < Z__.size(); ++i)
    {
        // compute the probability of observing Z[i] given sensed distance from known map and sensor noise
        prob *= get_gaussian_probability(measurement[i], var, Z__[i]);
    }

    return prob;
}

std::vector<particle> MCL::resample()
{
    // use resampling wheel algorithm 
    std::vector<paticle> p = X__;
    // get random index
    int index = get_random_number() * X__.size();
    double beta = 0.0;
    for (int i = 0; i < X__.size(); ++i)
    {
        beta += get_random_number() * 2 * max_weight__;
        while (beta > X__[index].w)
        {
            beta -= X__[index].w;
            index = (index + 1) % X__.size();
        }
        // select particle at index
        p[i] = X__[index];
    }

    return p;
}
