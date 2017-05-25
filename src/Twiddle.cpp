#include "Twiddle.h"
#include <iostream>

using namespace std;


Twiddle::Twiddle() {}


Twiddle::~Twiddle() {}


void Twiddle::init(PID &pid, double _initial_error) {
  _pid = &pid;

  _size = (*_pid).coefficients.size();
  
  for(int i=0;i<_size;++i) {
    _dK.push_back(1);
  }

  _best_error = _initial_error;
  _new_error = _initial_error;

  _index = 0;

  _tweak_state = UP;

  _is_init = true;

}