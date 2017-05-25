#include "Trainer.h"

using namespace std;


Trainer::Trainer() {
  _is_init = false;
}


Trainer::~Trainer() {}


void Trainer::init(PID &pid, vector<double> dK, double threshold, int max_timesteps, uWS::WebSocket<uWS::SERVER> &ws) {
  _pid = &pid;
  _dK = dK;
  _max_timesteps = max_timesteps;
  _threshold = threshold;
  _timestep = 0;
  _ws = &ws;
  _is_init = true;
}


void Trainer::run() {

  if(_timestep >= _max_timesteps) {

    double error = (*_pid)._i_error;
    
    if(!_twiddle._is_init) {
      _twiddle.init(*_pid, _dK, _threshold, error);
    }

    else {
      _twiddle.run(error);
      restart();
    }
  }
  else {
    _timestep++;
  }
}


void Trainer::restart(){
  (*_pid)._cte_prior = 0;
  (*_pid)._d_error = 0;
  (*_pid)._i_error = 0;
  _timestep = 0;
  std::string reset_msg = "42[\"reset\",{}]";
  (*_ws).send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}

// void init(PID &pid, vector<double> dK, double threshold, double initial_error);
// void run(double new_error);
// bool threshold_reached();