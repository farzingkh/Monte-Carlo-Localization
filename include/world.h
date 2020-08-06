#ifndef WORLD_H
#define WORL_H

#include <vector>

class world
{
public:
    void set_landmarks(std::vector<std::vector<double>> landmarks);
    std::vector<std::vector<double> get_landmarks();
    int get_size();
    
private:
    std::vector<std::vector<double>> landmarks__;
    int size__;
};

#endif /* WORLD_H */