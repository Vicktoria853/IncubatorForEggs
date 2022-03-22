#ifndef TERMOMETER_CPP
#define TERMOMETER_CPP

#include "Arduino.h"
#include "Termometer.h"
  
  
  Termometer::Termometer(uint8_t pinn){
    pin = pinn;
    //lastResult = getTemp();
    Vo = 0;
    R1 = 10000; //
    logR2 = 0;
    R2 = 0;
    T = 0;
    c1 = 1.009249522e-03;
    c2 = 2.378405444e-04;
    c3 = 2.019202697e-07;
    helper = 0;
    //lastResult = getTemp();
    }
    
float Termometer::calculateTemp(uint16_t tempAvg[20]){
    Vo = 0;
    helper = 0;
    for(uint8_t i = 0; i < 10; i++ ){
      Vo+= tempAvg[i];
      helper += tempAvg[i+10];
      }
      Vo /= 10; // carefull 20 * 4096 = 81920 > 65 536
      Vo += (helper/10);
    R2 = R1 * (4095.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    T = T - 273.15;
    //lastResult = T;
    return T;
  
  }

  float Termometer::getTemp(){
    Vo = analogRead(pin);
    R2 = R1 * (4095.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    T = T - 273.15;
    //lastResult = T;
    return T;
    }

    uint8_t Termometer::getVo(){
      return analogRead(pin);
      }

  #endif
