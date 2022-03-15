#ifndef PACKET_H
#define PACKET_H

#include "Termometer.h"


class Packet{
  public:
    Packet(uint8_t dryTempPin, uint8_t wetTempPin);
    uint16_t idSeq;
    Termometer dryTemp;
    Termometer wetTemp;
    float dhtSensor; //not sure, 250 ms to read
    float humidity;
    uint8_t positionEggs;
    uint8_t doorOpen;

  };

#endif