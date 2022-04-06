#ifndef INCUBATOR_CPP
#define INCUBATOR_CPP

#include "Arduino.h"
#include "Incubator.h"
//#include "Packet.h"

void Incubator::stepArg(){
    tempAvg[stepCircle] = dryTemp.getVo();    
    humidTempAvg[stepCircle] = wetTemp.getVo();  

    humidSensorAvg[stepCircle] = 0;


    ///////////////////////////////

  humidSensorAvg[stepCircle] = readHumiditySensor();
    ///////////////////////////
    

  
  stepCircle ++;
  if(stepCircle == 20){
    stepCircle = 0;
    packet.humidityCurrent = wetTemp.calculateTemp(tempAvg); // TODO
    packet.tempCurrent = dryTemp.calculateTemp(tempAvg);
    packet.humiditySensorCurrent = 0;
    for(uint8_t i = 0; i < 20; i++ ){
      packet.humiditySensorCurrent += humidSensorAvg[i];
      }
      packet.humiditySensorCurrent /= 20;
    sentPacket = 1;
    }
    //lsd
  lastStep = millis();
  }

  Incubator::Incubator(uint8_t dryPinTemp, uint8_t wetPinTemp, uint8_t Heaterpin, uint8_t Fan)
  : dryTemp(dryPinTemp), wetTemp(wetPinTemp){
    Serial.begin(115200);
 // avg, min, max, alarm- min max
  Wire.begin();
  //Serial.begin(9600);
  Wire.beginTransmission(si7021Addr);
  Wire.endTransmission();
    sentPacket = 0;
    stepCircle = 0;

    pinHeater = Heaterpin;
    pinFan = Fan;
    tempAvg[20] = {0}; 
    humidTempAvg[20] = {0}; 
    humidSensorAvg[20] = {0}; 

    
    humidityAdded = wetTemp.getTemp(); //TODO 
    packet.humidityCurrent = wetTemp.getTemp(); //TODO
    packet.tempCurrent = dryTemp.getTemp();
    packet.humiditySensorCurrent =  readHumiditySensor();
    lastEggTurning = millis();
    lastStep = millis();
    
    
    
    //tables //TODO
   // tempMode[22][5]; // avg, min, max, alarm- min max
   // humidMode[22][5];  
    }


 float Incubator::readHumiditySensor(){
  Wire.beginTransmission(si7021Addr);
  //Send humidity measurement command
  Wire.write(0xF5);
  Wire.endTransmission();
  delay(500);
     
  // Request 2 bytes of data
  Wire.requestFrom(si7021Addr, 2);
  // Read 2 bytes of data to get humidity
  if(Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
     
  // Convert the data
  
  helper = ((data[0] * 256.0) + data[1]);
  helper = ((125 * helper) / 65536.0) - 6;
  
  return helper;
  }



       

#endif
