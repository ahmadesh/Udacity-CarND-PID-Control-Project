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
The simulator provides the cross track error (CTE) to the PID controler implemented at `PID.cpp`. The PID then calculates the P error (cte), I error (summation of cte) and D error (differentiation of cte) implemented at `UpdateError()` function. Finally the output is calulcalated at `TotalError()` function by adding the PID errors multiplied with the gains (Kp, Ki, Kd). The main function feeds the output of PID as the steering angle to the simulator for driving the car.

## Tuning the PID gains
I initially tunned the PID gains manually such that the car could successfully finish the track. For manual tunning, I first set Kd, Ki to zero and tunned the Kp gain to have a reasonable drive around the center of the track and then gradually increased Kd to remove the oscillations. Finally, I increased Ki to remove any steady state errors and decrease the rise time of tracking.

For fine tunning of the PID gains I used the Twiddle algorithm, described in the course. I use the `RestartSim()` function for restarting the simulator drive in the track and evaluation of the drive-run by summing the absolute values of the cte between the frames 1000 to 2000. I ran twiddle on the Kp, Ki and Kd separately and reached to the finall set of (Kp=0.2150, Ki=0.00022, Kd=3.95307). It is worth noting that the initial start of the twiddle algorithm is critical in this project as the car could crash to the sides and not finish the data collection if the PID gains are a not in the correct range.  

