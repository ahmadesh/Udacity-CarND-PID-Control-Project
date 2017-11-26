# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
* gcc/g++ >= 5.4
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## PID implementation
The simulator will provide you the cross track error (CTE) to the PID controler implemented at `PID.cpp`. The PID then calculates the P error (cte), I error (integration of cte) and d error (differentiation of cte) implemented at `UpdateError()` function. Finally the output is calulcalated at `TotalError()` function by adding the PID errors multiplied with the gains (Kp, Ki, Kd). The main function feeds the output as the steering angle to the simulator for driving the car.

## Tuning the PID gains
I initially tunned the PID gains manually such that the car could successfully finish the track. For mannuall tunning, I first set Kd, Ki to zero and tunned the Kp gain and then gradually increased Kd and Ki, respectively. For fine tunning of the PID gains I used the Twiddle algorithm, described in the course. I use the `RestartSim()` function for restarting the drive in the track and evaluation of the drive-run by summing all the absolute values of the cte between the frames 1000 to 2000. I ran twiddle on the Kp, Ki and Kd separately and came up with the finall set of (Kp=0.2150, Ki=0.00022, Kd=3.95307).   

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).
