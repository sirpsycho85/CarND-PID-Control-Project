#include "PID.h"
#include <iostream>

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

// TODO: am I correctly calculating integral error?
// TODO: should error used for twiddle not be integral, but be the acrued absolute value of error?
// TODO: twiddle should be separate class
// TODO: training wrapper around twiddle that restarts the simulator
// TODO: members should have TRAILING underscore

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  _cte_prior = 0;
  _d_error = 0;
  _i_error = 0;
  _abs_error = 0;

  coefficients.push_back(Kp);
  coefficients.push_back(Ki);
  coefficients.push_back(Kd);

  best_error = 0;
}

void PID::UpdateError(double cte) {
  _p_error = cte;
  _i_error += cte;
  _d_error = (cte - _cte_prior);
  _cte_prior = cte;
  _abs_error += fabs(cte);
}

double PID::TotalError() {
}