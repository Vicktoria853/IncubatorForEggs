void receivedCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received: ");
  Serial.println(topic);
  Serial.print("payload: ");
  //ok = 0;
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    received_msg[100] = (char)payload[i];
  }
}

void mqttconnect() {
  while (!client.connected()) {
    Serial.print("MQTT connecting ...");
//    String clientId = "ESP32Client";

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


void setting() {
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

void Sent(){
    if (!client.connected()) {
    mqttconnect();
  }
  client.loop();

  
  //snprintf (msg, 100, "%u %u %f %f %f %u %s",id, idSeq++, temperature, RelativeHumidity, humiditySensor, eggTurning, currentTime);
 snprintf (msg, 100, "%u %u %f %f %f %u %s",1, 1, 12.3, 12.3, 12.3, 0, "12:13 09:18:08");
  if(eggTurning == 1){
    eggTurning = 0;
    }
    //client.publish("test", msg);
  
  client.publish("Incubator", msg);
  Serial.print("Sent message: ");
  Serial.println(msg);
  }
  


//void Packeting(uint16_t idSeq, float temp, float rh, float humidSensor, uint8_t eggTurning, String currentTime){
//  snprintf (msg, 100, "%u %u %f %f %f %u %s",id, idSeq, temp, rh, humidSensor, eggTurning, currentTime.c_str());
//  if(eggTurning == 1){
//    eggTurning = 0;
//    }
//  }

 
