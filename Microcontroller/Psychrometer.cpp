#ifndef PSYCHROMETER_CPP
#define PSYCHROMETER_Cpp

#include "Psychrometer.h"

float PsychrometerCal::calculatePsat(float temp){
  helper = 0;
  helper = c8/temp + c9 + c10*temp + c11*(pow(temp, 2)) + c12*(pow(temp, 3)) + c13*(log(temp));
  return pow(helper, helper);
  }
  
//float PsychrometerCal::calculateOmegaSat(float Db, float Wb){
//  helper = 0;
//  helper = (2501 - (PsatTwb*Wb / 1000))*wSatTwb - 1.006*(Db - Wb); // why /1000 in video?
//  w = w/ (2501 + (1.805*Db) - (4.186*Wb));
//  
//  }


float PsychrometerCal::calculating(  float dryTempAdded, float wetTempAdded){
  dryTemp = dryTempAdded;
  dryTempK = dryTemp + K;
  wetTemp = wetTempAdded;
  wetTempK = wetTemp + K;
  
  PsatTwb = calculatePsat(wetTempK);
  wSatTwb = 0;
  wSatTwb = (0.622*PsatTwb)/(Pt - PsatTwb);

  w = (2501 - (PsatTwb*wetTemp / 1000))*wSatTwb - 1.006*(dryTemp - wetTemp); // why /1000 in video?
  w = w/ (2501 + (1.805*dryTemp) - (4.186*wetTemp));
  
  PsatTdb = calculatePsat(dryTempK);
  wSatTdb = 0;
  wSatTdb = (0.622*PsatTwb)/(Pt - PsatTdb);

  mu = w/wSatTdb; // degree of saturation

  RelativeHumidity = mu / (1 - (1 - mu)*(PsatTdb/Pt));
  
  
  }


  

#endif
