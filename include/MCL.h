#ifndef MCL_H
#define MCL_H

#include "robot.h"

struct particle
{
    particle(Robot r, double w);
    Robot r;
    double w;
};

struct command
{
    command(double f, double t);
    double forward;
    double turn;
};

class MCL
{
public:
    MCL(std::vector<particle> X, command U, std::vector<double> Z); 
    // resample the particles and return the new belief
    std::vector<particle> resample();

private:
    // robot sensor measurements
    std::vector<double> Z__;
    // actuation command
    command U__;
    // belief
    std::vector<particle> X__;
    //maximum weight
    double max_weight__;
    // update
    void motion_update();
    // predict
    void sensor_update();
    // Get measurement probability
    double get_measurement_prob(std::vector<double> measurements);

};

#endif /* MCL_H */
