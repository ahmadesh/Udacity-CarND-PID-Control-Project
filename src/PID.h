#ifndef PID_H
#define PID_H

#include <uWS/uWS.h>

using namespace std::chrono;

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  bool run_twiddle; 
  int count; //counter
  double sum_cte;
  double best_sum_cte;
  double p[3]; // Kp/Ki/Kd
  double dp[3];
  bool inc_check; //check increasing
  bool dec_check; //chekc decreasing
  unsigned int ind; // index of p[3] Kp/Ki/Kd
  int data_start; // start of getting data
  int data_end; // end of getting data
  // server
  uWS::WebSocket<uWS::SERVER> server;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
    
  void twiddle();
    
    /*
     * Restarts simulator.
     */
  void RestartSim(uWS::WebSocket<uWS::SERVER> ws);

  void SetServer(uWS::WebSocket<uWS::SERVER> ws);

    
private:
  //error from previos step
  double prev_cte;

};

#endif /* PID_H */
