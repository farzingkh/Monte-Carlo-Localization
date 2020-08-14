

# Monte-Carlo-Localization
C++ implementation of Monte-Carlo localization and particle filter. Particles represent the posterior by a set of weighted samples. They can model arbitrary distributions and therefore are used when measurement or prediction distributions are non-Gausian. The localization can be summerized as follows:

 - __Particle Generation__: Particles are generated representing the robot with random pose uniformly distributed inside the map.
 - __Motion Update__: Particles are propogated based on the model of the system and motion model in case of localization
 - __Sensor Update__: Given the sensor readings of the robot and measurements from the known map particles are weighted based on the likelihood of observations
 - __Resampling__: Resampling results in the updated belief of the system state. Resamplig ensures that particles stay in the meaningful areas of the state space. New particles are drawn from the set of particles with a probability proportional to the likelihood of their observations. In case of the example implementation The resampling of the particles is done in a way similar to _Stochastic universal sampling_ with equal spacing at 2 times the maximum weight of the particles. 


### Compiling the Program

#### Step 1
Install openCV:

- Windows: [See insructions here](https://docs.opencv.org/master/d3/d52/tutorial_windows_install.html)

- Linux: [See instructions here](https://www.learnopencv.com/install-opencv3-on-ubuntu/)

 - Mac: You can use ```Homebrew```
```sh 
brew install opencv
```

#### Step 2
Clone the respository and build the ```cvplot``` package 

```sh
git clone https://github.com/farzingkh/Monte-Carlo-Localization.git
cd Monte-Carlo-Localization/cvplot
mkdir build
cd build
cmake ..
make
```
and then build and run the application.

on the main application directory:
```sh
mkdir build
cd build
cmake ..
make
./MCL
```

### Output
![output](./Images/out.gif)


### References

 - Ioannis M. Rekleitis. ["A Particle Filter Tutorial for Mobile Robot Localization."](http://www.cim.mcgill.ca/~yiannis/particletutorial.pdf) Centre for Intelligent Machines, McGill University, Tech. Rep. TR-CIM-04-02 (2004).
 - [Probabilistic Robotics.](https://mitpress.mit.edu/books/probabilistic-robotics) Sebastian Thrun, Wolfram Burgard, and Dieter Fox. (2005, MIT Press.) 647 pages
 - Wolfram Burgard, [Introduction to Mobile Robotics
Bayes Filter – Particle Filter and Monte Carlo Localization
](https://people.eecs.berkeley.edu/~pabbeel/cs287-fa19/slides/Lec14-particle-filters.pdf)

