#ifndef MCL_H
#define MCL_H

class MCL
{
public:
    MCL(Robot r, world w);  
    void set_iteration_num(int num);
    void set_particles_num(int num);
    // Evaluate the prediction error
    void evaluate();
    // Visualize particles and predictions
    void visualize();

private:
    // world
    world w__;
    // robot model
    Robot r__;
    // number of iterations
    int iterations_num__;
    // number of particles
    int particle_num__;
    // Random Generators
    std::random_device rd__;
    mt19937 gen__(rd__());
    // Get measurement probability
    double get_measurement_prob(std::vector<double> measurements);
    // Get Gaussian random
    double get_gaussian_random_number(double mean, double var);
    // Get normal distribution probability of x given mean and variance
    double get_gaussian_probability(double mean, double var, double x);
};

#endif /* MCL_H */
