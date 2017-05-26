#ifndef PID_H
#define PID_H
#include <uWS/uWS.h>
#include <vector>
#include <cmath>

using namespace std;

class PID {
public:
  /*
  * Errors
  */
  double _p_error;
  double _i_error;
  double _d_error;
  double _abs_error;

  enum twiddle_step {UP, DOWN, RESET};
  vector<double> coefficients;
  vector<double> twiddle_variables;
  int twiddle_coefficient_index;
  twiddle_step step;
  double _cte_prior;
  double best_error;
  int time_step;
  
  int max_time_steps;
  bool is_twiddle_initialized;
  double twiddle_threshold;
  bool twiddle_completed;


  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  void Twiddle(uWS::WebSocket<uWS::SERVER> ws);

  void Restart(uWS::WebSocket<uWS::SERVER> ws);

  void twiddle_next_coefficient();
};

#endif /* PID_H */
