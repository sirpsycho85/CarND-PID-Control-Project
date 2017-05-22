#ifndef PID_H
#define PID_H
#include <uWS/uWS.h>
#include <vector>

using namespace std;

class PID {
public:
  /*
  * Errors
  */
  double _p_error;
  double _i_error;
  double _d_error;

  /*
  * Coefficients
  */ 
  double _Kp;
  double _Ki;
  double _Kd;

  vector<double> dK;
  int dK_index;
  double _cte_prior;
  double best_error;
  int time_step;
  int max_time_steps;
  bool is_twiddle_initialized;

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
};

#endif /* PID_H */
