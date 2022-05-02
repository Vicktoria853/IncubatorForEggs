float calculatePsat(float temp){
  helper = 0;
  helper = (-5.8002206 *pow(10, 3))/temp + (1.3914993) + (-4.8640239 * pow(10, -2))*temp + (4.1764768 * (pow(10, -5)))*(pow(temp, 2)) + (-1.4452093 *(pow(10, -8)))*(pow(temp, 3)) + (6.5459673)*(log(temp));
 
  //c8/temp + c9 + c10*temp + c11*(pow(temp, 2)) + c12*(pow(temp, 3)) + c13*(log(temp));
  //Serial.println(helper);
  return pow(e, helper);
  }
  


float calculateHumid(  float newDryTemp, float newWetTemp){
  dryTemp = newDryTemp;
  dryTempK = dryTemp + K;
  wetTemp = newWetTemp;
  wetTempK = wetTemp + K;
  
  PsatTwb = calculatePsat(wetTempK);
  //Serial.println(PsatTwb);
  wSatTwb = 0;
  wSatTwb = (0.622*PsatTwb)/(Pt - PsatTwb);
//  Serial.println(wSatTwb);

  w = (2501 - (PsatTwb*wetTemp / 1000))*wSatTwb - 1.006*(dryTemp - wetTemp); // why /1000 in video?
  w = w/ (2501 + (1.805*dryTemp) - (4.186*wetTemp));

//  Serial.println(w);
  
  PsatTdb = calculatePsat(dryTempK);
//Serial.println(PsatTdb);
  
  wSatTdb = 0;
  wSatTdb = (0.622*PsatTdb)/(Pt - PsatTdb);
 // Serial.println(wSatTdb);

  mu = w/wSatTdb; // degree of saturation
RelativeHumidity = 5;
//Serial.println(mu);
  RelativeHumidity = ( mu / (1 - (1 - mu)*(PsatTdb/Pt)) ) *100;
  //Serial.println(RelativeHumidity);
  return RelativeHumidity;
  
  }


