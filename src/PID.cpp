#include "PID.h"
#include <cmath>

PID::PID(double Kp_, double Ki_, double Kd_)
    : p_error(0.0), i_error(0.0), d_error(0.0),
      Kp(Kp_), Ki(Ki_), Kd(Kd_),
      abs_error(0.0), count(0) {

}

PID::~PID() = default;

void PID::UpdateError(double cte) {
  const double last_cte = p_error;

  p_error = cte;
  i_error += cte;
  d_error = cte - last_cte;

  abs_error += std::abs(cte);
  count++;
}

double PID::TotalError() {
  return -Kp * p_error - Kd * d_error - Ki * i_error;
}

double PID::AverageError() {
  if (!count) {
    return 0;
  }
  return abs_error / count;
}

double PID::getCount() {
  return count;
}
