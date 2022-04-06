



#ifndef INCUBATOR_H
#define INCUBATOR_H

#include "Termometer.h"
#include "Packet.h"
#include <Wire.h>

// SI7021 I2C address is 0x40(64)
#define si7021Addr 0x40
#define TIME 30000 // 30 s


class Incubator{
  public:
    Incubator(uint8_t dryPinTemp, uint8_t wetPinTemp, uint8_t Heaterpin, uint8_t Fan);
    
    Termometer dryTemp;
    Termometer wetTemp;
    Packet packet;
    uint8_t pinHeater;
    uint8_t pinFan;

    unsigned int data[2];
    float tempMode[22][5]; // avg, min, max, alarm- min max
    float humidMode[22][5]; // avg, min, max, alarm- min max

    uint8_t sentPacket;
    uint8_t stepCircle;
    uint16_t tempAvg[20]; // every 30 sec 
    uint16_t humidTempAvg[20]; // every 30 sec 

    float humidSensorAvg[20]; // every 30 sec from Si7021
    float humidityAdded; // added by the customer


    //uint8_t positionEggs;
    //unsigned long doorOpen;
    //unsigned long doorClosed;
    unsigned long lastEggTurning;
    unsigned long lastStep;

    float helper;


    void stepArg();
    float readHumiditySensor();
    

  };

#endif
