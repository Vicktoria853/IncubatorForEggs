#ifndef PSYCHROMETER_H
#define PSYCHROMETER_H

#include <math.h> 

class PsychrometerCal{
  public:
  float dryTemp;
  float dryTempK;// in Kelvins
  float wetTemp;
  float wetTempK; // in Kelvins

  float Pt; // 101 kPa, default 
  
  const float K = 273.15; 
  const float c8 = -5800.2206;// -5.8002206 * 1000
  const float c9 = 1.3914993;
  const float c10 = -0.048640239;  // -4.8640239 * (1/100)
  const float c11 = 4.1764768 * (1/10000);
  const float c12 = -1.4452093 * pow(10, -8);
  const float c13 = 6.5459673;

  const float e = 2.71828182;

  float helper;


  float PsatTwb; // 
  float PsatTdb;
  float wSatTwb;
  float wSatTdb;
  float w;

  float mu;

  float RelativeHumidity; // tthe result

  
  float calculatePsat(float temp);
  float calculating(  float dryTempAdded, float wetTempAdded);
  

  
  
  
  
  
};



#endif
