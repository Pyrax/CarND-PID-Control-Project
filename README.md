# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Writeup

In this project a PID Controller is used to control the steering angle of a car driving through a track in the 
Udacity Term 2 simulator. 

### Reflection

The following describes the concept of the individual components of a PID controller in terms of impact on the car:
1. P - Proportional component:  
This component makes the car steer proportional to the so called "cross-track error" (CTE). The CTE in this case 
determines how far the car is away from the center of the road. Thereas, a higher CTE leads to higher steering angles to 
minimize error and get back to the center. If only a P-Controller is used the car will oscillate because it constantly 
overshoots it desired direction.
2. I - Integral component:  
The integral component takes the sum of all previous errors which can be used to prevent bias in the system. If the car 
keeps driving off to a specific side, the system might have a bias. Therefore, an integral component can help preventing 
this. However, its factor must be set carefully. Otherwise, it leads to an extreme overshooting at the beginning driving 
the car off track.
3. D - Derivative component:  
The derivative component is essentially a counter force of the proportional component. As the name implies it describes 
the change rate of CTE. Hence, it prevents the car from oscillating too much by preventing the overshooting.

In order to tune the hyper parameters for each component I manually tried out different values. 

I started with a simple P-Controller and set the parameter P as high as possible without having too much oscillation so 
that the car does not leave the road as long as possible. I ended up with `PID pid{0.1, 0.0, 0.0};` where the 
parameter Kp is 0.1.

Then I extended this controller with a D-Component and only tuned the parameter of D. I found that a value of 2.5 is 
enough to prevent most overshooting: `PID pid{0.1, 0.0, 2.5};`.

Afterwards, I have completed the PID controller by adding the integral part. As mentioned above its parameter must be 
carefully tuned otherwise it will completely steer off the track. So, I chose a small value of 0.0005.

From this point on the PID-Controller with all his parameters was set `PID pid{0.1, 0.0005, 2.5};` and able to drive 
around the track without leaving road. However, I was not satisfied enough with the result because in the larger curves 
the car almost hit the corners. So I evaluated the performance of different parameter values by taking the average CTE 
over a specific time span. The following values show all improvements I got:

Parameter set | Performance (average error - lower is better)
------------------------------|--------------------------------------
PID pid{0.1, 0.0005, 2.5};    | Average CTE: 0.458677 at 1028 values
PID pid{0.2, 0.0005, 2.5};    | Average CTE: 0.286144 at 1026 values
PID pid{0.25, 0.0005, 3.0};   | Average CTE: 0.258713 at 1028 values
PID pid{0.3, 0.0005, 3.5};    | Average CTE: 0.249481 at 1028 values

Finally, I ended up with `Kp = 0.3`, `Ki = 5e-4`, `Kd = 3.5`.

With different approaches than manual tuning these values could probably be improved further. For example, the "Twiddle" 
algorithm could take these values as starting point to then adjust them. However, in lack of time I will postpone this 
for now.


## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)
