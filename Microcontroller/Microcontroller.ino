

#include <WiFi.h>
#include <PubSubClient.h>
#include <stdint.h>
//#include "Packet.h"


const char* ssid = "VikiWIFI";
const char* password = "viki1234";

const char* mqtt_server = "192.168.95.253";

WiFiClient espClient;
PubSubClient client(espClient);

int sent = 0;
long lastMsg = 0;
char msg[20];
//Packet p(1, 2);



void receivedCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received: ");
  Serial.println(topic);
  Serial.print("payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
}

void mqttconnect() {
  while (!client.connected()) {
    Serial.print("MQTT connecting ...");
    String clientId = "ESP32Client";
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("test");
    } else {
      Serial.print("failed, status code =");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(500);
    }
  }
}


void setup() {
  Serial.begin(115200);
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

void loop() {
  if (!client.connected()) {
    mqttconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    float temp = 10;
    Serial.println(temp);
    snprintf (msg, 20, "%f", temp);
    /* publish the message */
    client.publish("test", msg);
    Serial.println(msg);
    
  }
}
