#include "PID.h"

using namespace std;

/*
TODO: meet rubric requirements: https://review.udacity.com/#!/rubrics/824/view

Define general algorithm

Tune/optimize hyperparameters

Reflection
- Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?
- Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to
- Student discusses how they chose the final hyperparameters (P, I, D coefficients).
- This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination!

Driving
- No tire may leave the drivable portion of the track surface.
- The car may not pop up onto ledges or roll over any surfaces that would otherwise be considered unsafe (if humans were in the vehicle).


General flow
- set gains
- accept cte as input
- use previous two cte to calculate derivitive component
- use all (or a lot of) previous cte to calculate integral component
- calculate output steering angle


TODO: create a P-only controller first
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	// TODO: distinguish between Kp in this scope and the member variables
}

void PID::UpdateError(double cte) {
}

double PID::TotalError() {
}

