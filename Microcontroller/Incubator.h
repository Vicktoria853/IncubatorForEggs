

#ifndef INCUBATOR_H
#define INCUBATOR_H

#include "Termometer.h"

#include <DHT.h>
#include <DHT_U.h>
#define TIME 30000 // 30 s

class Incubator{
  public:
    Incubator(uint8_t dryPinTemp, uint8_t wetPinTemp, uint8_t dhtPin);
    
    Termometer dryTemp;
    Termometer wetTemp;

    DHT dht;
    float tempMode[22][5]; // avg, min, max, alarm- min max
    float humidMode[22][5]; // avg, min, max, alarm- min max

    uint8_t sentPacket;
    uint8_t stepCircle;
    uint16_t tempAvg[20]; // every 30 sec 
    uint16_t humidTempAvg[20]; // every 30 sec 

    float humidDHTAvg[20]; // every 30 sec from DHT
    float humidityAdded; // added by the customer
    float humidityCurrent;
    float tempCurrent;
    float humidityDHTCurrent;
    //uint8_t positionEggs;
    //unsigned long doorOpen;
    //unsigned long doorClosed;
    unsigned long lastEggTurning;
    unsigned long lastStep;


    void stepArg();
    

  };

#endif
