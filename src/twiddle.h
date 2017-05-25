#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <vector>
#include "PID.h"

using namespace std;


class Twiddle {

public:
  Twiddle();
  virtual ~Twiddle();

  void init(PID &pid, vector<double> dK, double threshold, double initial_error);
  void run(double new_error);
  bool threshold_reached();
  bool _is_init;

private:
  enum tweak_state {UP, DOWN, RESTORE};

  PID *_pid;
  int _size;
  vector<double> _dK;
  double _threshold;
  double _best_error;
  int _index;
  tweak_state _tweak_state;

  void next_index();
};

#endif