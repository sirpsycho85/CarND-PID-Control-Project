#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <vector>
#include "PID.h"

using namespace std;


class Twiddle {

public:
  bool _is_completed;

  Twiddle();
  virtual ~Twiddle();
  void Init(PID pid, double _initial_error);

private:
  enum tweak_state {UP, DOWN, RESET};

  PID _pid;
  int _size;
  vector<double> _dK;
  double _best_error;
  double _new_error;
  int _index;
  tweak_state _tweak_state;
  bool _is_init;
};

#endif