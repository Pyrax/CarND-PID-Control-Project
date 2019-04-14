#include "PID.h"

PID::PID(double Kp_, double Ki_, double Kd_, bool tune_parameters)
    : tune_parameters(tune_parameters),
      p_error(0.0), i_error(0.0), d_error(0.0),
      Kp(Kp_), Ki(Ki_), Kd(Kd_) {

}

PID::~PID() = default;

void PID::UpdateError(double cte) {
  const double last_cte = p_error;

  p_error = cte;
  i_error += cte;
  d_error = cte - last_cte;
}

double PID::TotalError() {
  return -Kp * p_error - Kd * d_error - Ki * i_error;
}