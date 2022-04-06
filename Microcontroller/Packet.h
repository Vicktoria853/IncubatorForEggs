#ifndef PACKET_H
#define PACKET_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <stdint.h>




class Packet{
  public:
    Packet();
    void Packeting();
    void Sent();
    //void receivedCallback(char* topic, byte* payload, unsigned int length);
    void mqttconnect();
        void setting();

        
    uint16_t idSeq;
    float humidityCurrent;
    float tempCurrent;
    float humiditySensorCurrent;
    uint8_t eggTurning; // yes - no
    const char* ssid = "VikiWIFI";//TODO
    const char* password = "viki1234";//TODO
    
    const char* mqtt_server = "192.168.95.253";//TODO
    const char* topic = "Incubator";
    uint8_t ok = 0;
    
    WiFiClient espClient;
    PubSubClient client;//(espClient);
    
    int sent = 0;
    long lastMsg = 0;
    char msg[30];
  };

#endif
