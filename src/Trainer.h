#ifndef TRAINER_H
#define TRAINER_H

#include <uWS/uWS.h>
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

	void init(PID &pid, vector<double> dK, double threshold, int max_timesteps, uWS::WebSocket<uWS::SERVER> &ws);
	void run();

private:
	PID *_pid;
	vector<double> _dK;
	Twiddle _twiddle;
	int _max_timesteps;
	double _threshold;
	int _timestep;
	bool _is_init;
	uWS::WebSocket<uWS::SERVER> *_ws;

	void restart();
};

#endif