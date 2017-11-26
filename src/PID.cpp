#include "PID.h"
#include <iostream>
#include "cmath"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {
    p_error = 0;
    i_error = 0;
    d_error = 0;
    prev_cte = 0;
}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    
    run_twiddle = false;
    p[0] = Kp;
    p[1] = Ki;
    p[2] = Kd;
    dp[0] = 0.1*Kp;
    dp[1] = 0.1*Ki;
    dp[2] = 0.1*Kd;
    count = 1;
    sum_cte = 0;
    best_sum_cte = -1; //initial best cte
    inc_check = false; // check increasing K
    dec_check = false; // check decreasing K
    ind = 2; // run on Kp/Ki/Kd
    data_start = 1000; // start count for summing error
    data_end = 2000; // end count for summing error
}

void PID::UpdateError(double cte) {
    if (run_twiddle) {
        count += 1;
    
        if (count>data_start & count<data_end)
            sum_cte += fabs(cte);
    
        if (count % data_end == 0) {
            count = 1;
            twiddle();
            RestartSim(server);
            sum_cte = 0;
            Kp = p[0];
            Ki = p[1];
            Kd = p[2];
        }
    }
    p_error = cte;
    d_error = cte - prev_cte;
    prev_cte = cte;
    i_error += cte;
}

void PID::twiddle() {
    cout<<"best sum "<<best_sum_cte<<endl;
    cout<<"cur sum "<<sum_cte<<endl;
    cout<<"K "<<p[2]<<endl;

    if (best_sum_cte==-1)
        best_sum_cte =  sum_cte;
    
    if (!inc_check) {
        p[ind] += dp[ind];
        inc_check = true;
        return;
    } else {
        if (sum_cte<best_sum_cte) {
            best_sum_cte = sum_cte;
            dp[ind] *= 1.1;
            inc_check = true;
            dec_check = false;
            p[ind] += dp[ind];
            cout<<"minnnn"<<std::endl;

        } else {
            if (!dec_check) {
                p[ind] -= 2*dp[ind];
                dec_check = true;
            } else {
                p[ind] += dp[ind];
                dp[ind] *= 0.9;
                dec_check = false;
                inc_check = false;
            }
        }
    }
}

double PID::TotalError() {
    return Kp * p_error + Kd * d_error + Ki * i_error;
}

void PID::RestartSim(uWS::WebSocket<uWS::SERVER> ws) {
    std::string reset_msg = "42[\"reset\",{}]";
    ws.send(reset_msg.data(), reset_msg.length(), uWS::OpCode::TEXT);
}

void PID::SetServer(uWS::WebSocket<uWS::SERVER> ws) {
    server = ws;
}

