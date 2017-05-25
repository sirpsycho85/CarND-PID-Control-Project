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

// TODO: twiddle should be separate class
// TODO: training wrapper around twiddle that restarts the simulator
// TODO: members should have TRAILING underscore

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  _cte_prior = 0;
  _d_error = 0;
  _i_error = 0;

  coefficients.push_back(0);
  coefficients.push_back(0);
  coefficients.push_back(0);

  twiddle_variables.push_back(1);
  twiddle_variables.push_back(1);
  twiddle_variables.push_back(1);

  twiddle_coefficient_index = 0;
  is_twiddle_initialized = false;
  best_error = 0;
  time_step = 0;
  max_time_steps = 200;
  twiddle_threshold = 1;
  twiddle_completed = false;
  step = UP;
}

void PID::UpdateError(double cte) {
  _p_error = cte;
  _i_error += cte;
  _d_error = (_cte_prior-cte);
  _cte_prior = cte;
}

double PID::TotalError() {
}

/*
Twiddle under 2 conditions:
- cte is too high
- _i_error goes above best _i_error for first N steps

check _i_error after N steps
initialize to best error and restart

add dKp to Kp
get new _i_error
if best:
  multiply dKp by 1.1
else:
  subtract 2*dKp from Kp
  if best:
    multiply dKp by 1.1
  else:
    multiple dKp by 0.9
move on to dKi

state:
- values of deltas
- pointer to the correct parameter to tweak
- best error

if time_step > T
  twiddle

twiddle()


*/
void PID::Twiddle(uWS::WebSocket<uWS::SERVER> ws) {
  //after required time, compare error to best error
  if (time_step == max_time_steps) {
    
    //if this is first run, initialize error
    if (is_twiddle_initialized == false) {
      best_error = _i_error;
      is_twiddle_initialized = true;
    }

    //if best error, move on to next coefficient
    if (_i_error < best_error) {
      twiddle_variables[twiddle_coefficient_index] *= 1.1;
      twiddle_next_coefficient();
    }

    // tweak up
    if (step == UP) {
      coefficients[twiddle_coefficient_index]
        += twiddle_variables[twiddle_coefficient_index];
      step = DOWN;
    }

    // tweak down
    else if(step == DOWN) {
      coefficients[twiddle_coefficient_index]
        -= 2*twiddle_variables[twiddle_coefficient_index];
      step = RESET;
    }

    // reset
    else if (step == RESET) {
      coefficients[twiddle_coefficient_index]
        += twiddle_variables[twiddle_coefficient_index];

      twiddle_variables[twiddle_coefficient_index] *= 0.9;
      
      twiddle_next_coefficient();
    }

    // print coefficients

    cout << "coefficients" << endl;
    for(int i = 0; i < coefficients.size(); ++i) {
      cout << coefficients[i] << endl;
    }
    cout << "_i_error: " << _i_error << endl;

    //stop twiddling if sum of variables fall below threshold
    
    double sum_twiddle_variables = 0;
    for(int i = 0; i < twiddle_variables.size(); ++i) {
      sum_twiddle_variables += twiddle_variables[i];
    }

    if(sum_twiddle_variables < twiddle_threshold) {
      cout << "twiddle compelted" << endl;
      exit(EXIT_FAILURE);
    }

    // restart simulator

    Restart(ws);
  }
  else {
    time_step++;
  }
}

void PID::twiddle_next_coefficient() {
  twiddle_coefficient_index =
    (twiddle_coefficient_index + 1) % 2;
  step = UP;
}

void PID::Restart(uWS::WebSocket<uWS::SERVER> ws){
  _cte_prior = 0;
  _d_error = 0;
  _i_error = 0;
  time_step = 0;
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}