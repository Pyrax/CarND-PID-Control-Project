#ifndef PID_H
#define PID_H

class PID {
 public:
  /**
   * Constructor
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  PID(double Kp_, double Ki_, double Kd_);

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  /**
   * Calculate the average cross track error.
   * @output The average CTE
   */
  double AverageError();

  /**
   * @output Number of values captured by the controller.
   */
  double getCount();

 private:

  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;

  /**
   * Variables for evaluating average error
   */
  double abs_error; // takes the absolute value of CTE (unlike i_error)
  int count;
};

#endif  // PID_H