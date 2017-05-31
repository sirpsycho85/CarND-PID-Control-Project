#include "Trainer.h"

using namespace std;


//TODO: train for more timesteps and save the best coefficients.
//TODO: coefficients should be positive...consider what it means in the sim
//TODO: try PI only
//TODO: quit faster if the error is horrendous
//TODO: maybe the error should be mean(abs(cte)) and let it run until abs(cte) is too big?


Trainer::Trainer() {
  _is_init = false;
}


Trainer::~Trainer() {}


void Trainer::init(PID &pid, vector<double> dK, double threshold, int max_timesteps) {
  _pid = &pid;
  _dK = dK;
  _max_timesteps = max_timesteps;
  _threshold = threshold;
  _timestep = 0;
  _is_init = true;
  _error = 0;
  _is_ready = false;
}


void Trainer::run(uWS::WebSocket<uWS::SERVER> ws) {

  if(_is_ready) {

    _error = (_error*_timestep + fabs((*_pid)._cte_prior))/(_timestep+1);

    if(_timestep >= _max_timesteps || fabs((*_pid)._cte_prior) > 1) {
      
      if(!_twiddle._is_init) {
        cout << "initializing twiddle" << endl;
        _twiddle.init(*_pid, _dK, _threshold, _error);
      }
      run_twiddle(ws);
    }
    else {
      _timestep++;
    }
  }
  else {
    int sleep_success = usleep(1000*1000);
    _is_ready = true;
    cout << "trainer is ready\n";
  }
}


void Trainer::run_twiddle(uWS::WebSocket<uWS::SERVER> ws) {
  cout << "\nrunning twiddle" << endl;
  _twiddle.run(_error);
  restart(ws);
}


void Trainer::restart(uWS::WebSocket<uWS::SERVER> ws){
  cout << "restarting simulator" << endl;
  (*_pid)._cte_prior = 0;
  (*_pid)._d_error = 0;
  (*_pid)._i_error = 0;
  (*_pid)._abs_error = 0;
  _timestep = 0;
  _error = 0;
  _is_ready = false;
  int sleep_success = usleep(1000*1000);
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}

// void init(PID &pid, vector<double> dK, double threshold, double initial_error);
// void run(double new_error);
// bool threshold_reached();