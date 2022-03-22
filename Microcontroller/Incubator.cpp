#ifndef INCUBATOR_CPP
#define INCUBATOR_CPP

#include "Arduino.h"
#include "Incubator.h"
#define DHTTYPE DHT11 
//#include "Packet.h"

void Incubator::stepArg(){
    tempAvg[stepCircle] = dryTemp.getVo();    
    humidTempAvg[stepCircle] = wetTemp.getVo();  

    humidDHTAvg[stepCircle] = dht.readHumidity(); 

  
  stepCircle ++;
  if(stepCircle == 20){
    stepCircle = 0;
    humidityCurrent = wetTemp.calculateTemp(tempAvg); // TODO
    tempCurrent = dryTemp.calculateTemp(tempAvg);
    humidityDHTCurrent = 0;
    for(uint8_t i = 0; i < 20; i++ ){
      humidityDHTCurrent += humidDHTAvg[i];
      }
      humidityDHTCurrent /= 20;
    sentPacket = 1;
    }
    //lsd
  lastStep = millis();
  }

  Incubator::Incubator(uint8_t dryPinTemp, uint8_t wetPinTemp, uint8_t dhtPin)
  : dryTemp(dryPinTemp), wetTemp(wetPinTemp), dht(dhtPin, DHTTYPE){
 // avg, min, max, alarm- min max

    sentPacket = 0;
    stepCircle = 0;
    
    tempAvg[20] = {0}; 
    humidTempAvg[20] = {0}; 
    humidDHTAvg[20] = {0}; 

    
    humidityAdded = wetTemp.getTemp(); //TODO 
    humidityCurrent = wetTemp.getTemp(); //TODO
    tempCurrent = dryTemp.getTemp();
    humidityDHTCurrent =  dht.readHumidity();
    lastEggTurning = millis();
    lastStep = millis();
    
    
    
    //tables //TODO
   // tempMode[22][5]; // avg, min, max, alarm- min max
   // humidMode[22][5];  
    }


  



       

#endif
