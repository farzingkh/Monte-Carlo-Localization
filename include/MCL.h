#ifndef MCL_H
#define MCL_H

struct particle
{
    Robot r;
    double w;
}

struct command
{
    double forward;
    double turn;
}

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
    // Get Gaussian random
    double get_gaussian_random_number(double mean, double var);
    // Get normal distribution probability of x given mean and variance
    double get_gaussian_probability(double mean, double var, double x);
};

#endif /* MCL_H */
