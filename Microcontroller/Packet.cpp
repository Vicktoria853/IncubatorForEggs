#ifndef PACKET_CPP
#define PACKET_CPP

#include "Arduino.h"
#include "Packet.h"

     Packet::Packet(uint8_t dryTempPin, uint8_t wetTempPin): dryTemp(dryTempPin), wetTemp(wetTempPin) {
          idSeq = 0;
          dhtSensor = 0; 
          humidity = 0;
          positionEggs = 1;
          doorOpen = 0;
      }
       

#endif
