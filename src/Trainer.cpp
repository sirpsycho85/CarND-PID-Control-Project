#include "Trainer.h"

using namespace std;


//TODO: could not make trainer work - receive multiple onMessage and ends up twiddling multiple times per restart
//Switched to manual

Trainer::Trainer() {
}


Trainer::~Trainer() {}


void Trainer::init(PID &pid, vector<double> dK, double threshold, int max_timesteps) {
  _pid = &pid;
  _dK = dK;
  _max_timesteps = max_timesteps;
  _threshold = threshold;
  _timestep = 0;
  _error = 0;
}


void Trainer::run(uWS::WebSocket<uWS::SERVER> ws) {

  _timestep++;

  _error = 1.0/_timestep;

  if(fabs((*_pid)._cte_prior) > 1) {
    
    if(!_twiddle._is_init) {
      cout << "initializing twiddle" << endl;
      _twiddle.init(*_pid, _dK, _threshold, _error);
    }
    if(!_lock) {
      _lock = true;
      _twiddle.run(_error);
      restart(ws);
    }
  }
}


void Trainer::restart(uWS::WebSocket<uWS::SERVER> ws){
  cout << "restarting simulator" << endl;
  (*_pid)._cte_prior = 0;
  (*_pid)._d_error = 0;
  (*_pid)._i_error = 0;
  (*_pid)._abs_error = 0;
  _timestep = 0;
  _error = 0;
  std::string reset_msg = "42[\"reset\",{}]";
  ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
  int sleep_success = usleep(1000*1000);
  _lock = false;
}

// void init(PID &pid, vector<double> dK, double threshold, double initial_error);
// void run(double new_error);
// bool threshold_reached();