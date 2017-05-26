#ifndef TRAINER_H
#define TRAINER_H

#include <uWS/uWS.h>
#include <iostream>
#include "PID.h"
#include "Twiddle.h"

using namespace std;

/*
wrapper takes care of
- initialization
- managing timesteps
- passing in error
- restarting simulator
- resetting pid variables
*/

class Trainer {

public:
	Trainer();
	virtual ~Trainer();

	void init(PID &pid, vector<double> dK, double threshold, int max_timesteps);
	void run(uWS::WebSocket<uWS::SERVER> ws);

private:
	PID *_pid;
	vector<double> _dK;
	Twiddle _twiddle;
	int _max_timesteps;
	double _threshold;
	int _timestep;
	bool _is_init;

	void restart(uWS::WebSocket<uWS::SERVER> ws);
};

#endif