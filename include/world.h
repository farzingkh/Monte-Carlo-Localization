#ifndef WORLD_H
#define WORL_H

#include <vector>

class World
{
public:
    void set_landmarks(double x, double y);
    std::vector<double> get_landmarks();
    
    int get_x();
    int get_y();
    
private:
    std::vector<double> landmarks__;
    // world size
    double x__;
    double y__;
};

#endif /* WORLD_H */