float getHumidSensor(){
  Wire.beginTransmission(si7021Addr);
  Wire.write(0xF5);
  Wire.endTransmission();
  delay(500);
     
  Wire.requestFrom(si7021Addr, 2);
  if(Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  helper = ((data[0] * 256.0) + data[1]);
  helper = ((125 * helper) / 65536.0) - 6;
  
  //Serial.println(helper);
  return helper;
  
  }
