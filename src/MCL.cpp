#include "../include/MCL.h"
#include "../include/utility.h"
#include <assert.h>

particle::particle(Robot rr, double ww) : r(rr), w(ww) {}

command::command(double f, double t) : forward(f), turn(t) {}

MCL::MCL(std::vector<particle> X, command U, std::vector<double> Z) : X__(X), U__(U), Z__(Z), max_weight__(0.0) {}

void MCL::motion_update()
{
    // update particles with command input
    std::for_each(X__.begin(), X__.end(), [this](particle &ptc) { ptc.r.move(U__.turn, U__.forward); });
}

void MCL::sensor_update()
{
    // keep track of maximum weight for resampling
    max_weight__ = 0.0;
    // update weights with probability of each observations using pdf
    std::for_each(X__.begin(), X__.end(), [this](particle &ptc) {
        // sense environemnt with each particle
        std::vector<double> meas = ptc.r.sense(false);
        //std::cout << ptc.r.get_sensor_readings() << std::endl;
        // calculate probability of robot measurements Z considering a pdf of mean observed distance from map and varance of sensor noise
        ptc.w = get_measurement_prob(meas);
        // update max weight
        ptc.w > max_weight__ ? max_weight__ = ptc.w : max_weight__ += 0.0;
    });
}

double MCL::get_measurement_prob(std::vector<double> measurement)
{
    assert(measurement.size() == Z__.size());
    // get sensor noise
    double var = X__[0].r.get_sensor_noise();
    double prob = 1.0;
    for (int i = 0; i < Z__.size(); ++i)
    {
        // compute the probability of observing Z[i]s given sensed distance from known map and sensor noise
        prob *= utility::get_gaussian_probability(measurement[i], var, Z__[i]);
    }
    //std::cout << "[Prob] " << prob << std::endl;
    return prob;
}

std::vector<particle> MCL::resample()
{
    // move particles
    motion_update();
    // sense
    sensor_update();
    // use resampling wheel algorithm to resample particles
    std::vector<particle> p = X__;
    // get random index
    int index = utility::get_random_number() * X__.size();
    double beta = 0.0;
    for (int i = 0; i < X__.size(); ++i)
    {
        beta += utility::get_random_number() * 2 * max_weight__;
        while (beta > X__[index].w)
        {
            beta -= X__[index].w;
            index = (index + 1) % X__.size();
        }
        //std::cout << index << std::endl;
        // select particle at index
        p[i] = X__[index];
        //std::cout << p[i].r.get_pose() << std::endl;
    }
    // return new particle set
    return p;
}
