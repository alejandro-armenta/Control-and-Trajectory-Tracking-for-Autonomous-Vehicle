/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
  Kpi_ = Kpi;
  Kii_ = Kii;
  Kdi_ = Kdi;
  
  output_lim_mini_ = output_lim_mini;
  output_lim_maxi_ = output_lim_maxi;
  
  e_Kpi = 0.0;
  e_Kdi = 0.0;
  e_Kii = 0.0;
  
  sum_cte = 0.0;
  prev_cte = 0.0;
  
  dt = 1.0;
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
  
  	sum_cte += cte;
  
  	//NOTE: Proportional part of the PID.
  	e_Kpi = -Kpi_ * cte;
  	
  	//NOTE: Derivative part of the PID.
  	e_Kdi = -Kdi_ * ((cte - prev_cte) / dt);
  
  	//NOTE: Integration part of the PID.
  	e_Kii = -Kii_ * sum_cte;
  	
  	prev_cte = cte;
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
    double control = e_Kpi + e_Kdi + e_Kii;
  
  	if(control < output_lim_mini_)
      control = output_lim_mini_;
  	
  	if(control > output_lim_maxi_)
      control = output_lim_maxi_;
  	
  	
    return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
  	dt = new_delta_time;
}