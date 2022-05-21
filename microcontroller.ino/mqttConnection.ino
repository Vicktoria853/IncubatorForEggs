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
  wifiWaiting = millis();
  while (!client.connected()){
    
  if (WiFi.status() != WL_CONNECTED) {
  WiFi.begin(ssid, password);
  }
      
    Serial.print("MQTT connecting ...");

    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      //okToSent = 1;
      client.subscribe("Incubator");
    } else {
      Serial.print("failed, status code =");
      Serial.println(client.state());
//      if(wifiWaiting + 5000 < millis()){
//           Serial.println("Could not connect");
//           okToSent = 0;
//           break;
//        }
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
   // if (!client.connected()) {
    mqttconnect();
  //}
  client.loop();

    //if(okToSent == 1){
      snprintf(msg, 100, "%u %u %f %f %f %u %s",id, idSeq++, temperature, RelativeHumidity, humiditySensor, eggTurning, currentTime);
    // snprintf(msg, 100, "%u %u %f %f %f %u %s",1, idSeq++, 12.3564577, 12.3, 12.3, 0, "12:13 09:18:08");
      if(eggTurning == 1){
        eggTurning = 0;
        }
      
      client.publish("Incubator", msg);
      Serial.print("Sent message: ");
      Serial.println(msg);
    //}
  }

  //snprintf (msg, 100, "%u %u %f %f %f %u %s",1, 1, 12.3, 12.3, 12.3, 0, "12:13 09:18:08");


//void Packeting(uint16_t idSeq, float temp, float rh, float humidSensor, uint8_t eggTurning, String currentTime){
//  snprintf (msg, 100, "%u %u %f %f %f %u %s",id, idSeq, temp, rh, humidSensor, eggTurning, currentTime.c_str());
//  if(eggTurning == 1){
//    eggTurning = 0;
//    }
//  }

 
