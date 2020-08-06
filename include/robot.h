#ifndef ROBOT_H
#define ROBO_H

#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <math.h>
#include <exception>

class World; // forward declaration

class Robot
{
public:
    // Initialize robot in a random position in the world
    Robot(World world);
    // Set robot's states
    void set_states(double new_x, double new_y, double new_orient);
    // Set robots state transition noise
    void set_noise(double forward_nois, double turn_noise, double sensor_noise);
    // Sense the environment with sensors
    std::vector<double> sense(bool noise = true);
    // Move the robot
    void move(double turn, double forward);
    // get sensor noise
    double get_sensor_noise();
    // get x
    double get_x();
    // get y
    double get_y();
    // Get pose readings
    std::string get_pose();
    // Get sensor readings
    std::string get_sensor_readings();

private:
    // Get random number from normal distribution given its mean and variance
    double get_gaussian_random_number(double mean, double var);
    // get random number between [0,1.0]
    double get_random_number();
    // robot states
    double x__;
    double y__;
    double orientation__;
    // noise
    static double forward_noise__;
    static double turn_noise__;
    static double sense_noise__;
    //size of the wolrd
    World world__;

};

#endif /* ROBOT_H */