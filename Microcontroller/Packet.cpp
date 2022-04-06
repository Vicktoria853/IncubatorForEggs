#ifndef PACKET_CPP
#define PACKET_CPP

#include <WiFi.h>
#include <PubSubClient.h>
#include "Arduino.h"
#include "Packet.h"

char received_msg[100];

     Packet::Packet(): client(espClient) {
          idSeq = 0;
          eggTurning = 0;
          humidityCurrent = 0;
          tempCurrent = 0;
          humiditySensorCurrent = 0;
          
      }


void receivedCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received: ");
  Serial.println(topic);
  Serial.print("payload: ");
  //ok = 0;
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    received_msg[100] = (char)payload[i];
  }
//    if((char)payload[i] != msg[i]){
//      ok++;
//      }


//  if(ok> 0){
//      Serial.println("Error with message " + idSeq);
//    }
}

void Packet::mqttconnect() {
  while (!client.connected()) {
    Serial.print("MQTT connecting ...");
    String clientId = "ESP32Client";
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("Incubator");
    } else {
      Serial.print("failed, status code =");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(500);
    }
  }
}


void Packet::setting() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
  client.setCallback(receivedCallback);
}

void Packet::Sent(){
    if (!client.connected()) {
    mqttconnect();
  }
  client.loop();
  Packeting();
  client.publish("Incubator", msg);
  Serial.print("Sent message: ");
  Serial.println(msg);
  }


void Packet::Packeting(){
  snprintf (msg, 30, "%u %f %f %f %u", idSeq, humidityCurrent, tempCurrent, humiditySensorCurrent, eggTurning );
  if(eggTurning == 1){
    eggTurning = 0;
    }
  }

       

#endif
