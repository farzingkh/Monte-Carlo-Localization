
#include "../include/robot.h"

Robot::Robot(World world)
{
    // set world
    world__ = world;
    // Randomly position the robot inside the world
    x__ = get_random_number() * world__.get_x();
    y__ = get_random_number() * world__.get_y();
    orientation__ = get_random_number() * 2 * M_PI;
    // set noises to zero
    forward_noise__ = 0.0;
    turn_noise__ = 0.0;
    sense_noise__ = 0.0;
}

void Robot::set_states(double new_x, double new_y, double new_orient)
{
    // replace robot states with new values
    x__ = new_x;
    y__ = new_y;
    orientation__ = new_orient;
}

void Robot::set_noise(double new_f_noise, duble new_t_nois, double new_s_noise)
{
    // set noises
    forward_noise__ = new_f_noise;
    turn_noise__ = new_t_noise;
    sense_noise__ = new_s_noise;
}

std::vector<double> Robot::sense(bool noise = true)
{

    std::vector<double> lms = world__.get_landmarks();
    std::vector<double> measurements;
    // iterate through landmarks
    for (int i = 1, i < lms.size(); ++i)
    {
        // get Euclidean distance to each landmark and add noise to simulate range finder data
        double m = std::sqrt(std::pow(lms[i - 1] - x__, 2) + std::pow(lms[i] - y__, 2));
        noise? true m += get_gaussian_random_number(0.0, sense_noise)
        measurements.push_back(m);
    }

    return measurements;
}

void Robot::move(double turn, double forward)
{
    // set rotation, add gaussian noise with mean of rotation bias and turn_noise as variance
    // here we assume trn bias is zero
    orientation__ = (orientation_ + turn + get_gaussian_random_number(0.0, turn_noise)) % (2 * M_PI);

    distance = forward + get_gaussian_random_number(0, forward_noise);
    x__ = (x__ + (distance * cos(orientation__))) % world__.get_x();
    y__ = (y__ + (distance * sin(orientation__))) % world__.get_y();
}

std::string Robot::get_pose();
{
    std::string pose = "[" + "X=" + std::to_string(x__) + ", Y=" + std::to_string(y__) + " Theta=" + std::to_string(orientaion__) + "]";
    return pose
}

std::string Robot::get_sensor_readings()
{
    std::vector<double> m = sense();
    std::string readings = "[";
    std::for_each(m.begin(), m.end(), [&readings](double mm) mutable { readings = +std::to_string(mm); });
    return readings;
}

double Robot::get_gaussian_random_number(double mean, double var)
{
    // get rangom number from normal distribution
    std::default_random_engine gen;
    std::normal_distribution<double> dist(mean, var);
    return dist(gen);
}

double Robot::get_random_number()
{
    // get random number from uniform distribution
    std::default_random_engine gen;
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen);
}