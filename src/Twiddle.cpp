#include "Twiddle.h"

using namespace std;


Twiddle::Twiddle() {
  _is_init = false;
}


Twiddle::~Twiddle() {}


void Twiddle::init(PID &pid, vector<double> dK, double threshold, double initial_error) {
  _pid = &pid;

  _size = (*_pid).coefficients.size();
  
  _dK = dK;

  _threshold = threshold;

  _best_error = initial_error;

  _index = 0;

  _tweak_state = UP;

  _is_init = true;
}


void Twiddle::run(double new_error) {

  if(!threshold_reached()) {
    
    if(new_error < _best_error) {
      _best_error = new_error;
      _dK[_index] *= 1.1;
      next_index();
    }
    else if(_tweak_state == RESTORE) {
      _dK[_index] *= 0.9;
      (*_pid).coefficients[_index] += _dK[_index];
      next_index();
    }

    if(_tweak_state == UP) {
      (*_pid).coefficients[_index] += _dK[_index];
      _tweak_state = DOWN;
    }
    else if(_tweak_state == DOWN) {
      (*_pid).coefficients[_index] -= 2*_dK[_index];
      _tweak_state = RESTORE;
    }
  }
}


bool Twiddle::threshold_reached() {
  double sum_dK = 0;
  for(int i = 0; i < _size; ++i){
    sum_dK += _dK[i];
  }
  return(sum_dK < _threshold);
}


void Twiddle::next_index() {
  _index = (_index + 1) % _size;
  _tweak_state = UP;
}