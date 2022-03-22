#ifndef TERMOMETER_H
#define TERMOMETER_H

#include "Arduino.h"

class Termometer{
   public:
    Termometer(uint8_t pinn);
    uint8_t pin;
    //float lastResult;

    float getTemp();
    float calculateTemp(uint16_t tempAvg[20]);
    uint8_t getVo();
  
 private:
     uint16_t Vo;
     float R1;// = 10000; //
     float logR2, R2, T;
     float c1;
     float c2;
     float c3;
     uint16_t helper;
     //float lastResult;
      //

};
  
 #endif
