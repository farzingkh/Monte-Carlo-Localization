#ifndef ROBOT_H
#define ROBO_H

#include <vector>
#include <random>
#include <string>
#include <iostream>
#include <math.h>
#include <exception>

class Robot
{
public:
    // Initialize robot in a random position in the world
    Robot();
    // Set robot's states
    void set_states(double new_x, double new_y, double new_orient);
    // Set robots state transition noise
    void set_noise(double forward_nois, double turn_noise, double sensor_noise);
    // Sense the environment; return a vecotr of measurements from landmarks
    std::vector<double> sense();
    // Move the robot
    void move(double turn, double forward);
    // Get pose readings
    std::string get_pose();
    // Get sensor readings
    std::string get_sensor_readings();

private:

    // robot states
    double x__;
    double y__;
    double orientation__;
};

#endif /* ROBOT_H */