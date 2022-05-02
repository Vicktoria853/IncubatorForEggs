void Step(){
  lastStep = millis();
  tempTaken += analogRead(pinDB);
  humidTempTaken += analogRead(pinWB);
  humidSensorTaken += getHumidSensor();

  stepCircle++;
  if(stepCircle == 20){

      temperature = calTemp(tempTaken/20);
      RelativeHumidity = calculateHumid(temperature, calTemp(humidTempTaken/20));
      humiditySensor = humidSensorTaken/20;

        tempTaken = 0;
  humidTempTaken = 0;
  humidSensorTaken = 0;
    Sent();
    stepCircle = 0;
    }
 
  }
