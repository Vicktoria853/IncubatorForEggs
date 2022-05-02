void printDisplay(){
    now = rtc.now();
    snprintf(currentTime, 50, "%d/%d %d:%d:%d", now.month(), now.day(), now.hour(), now.minute(), now.second());
    display.clearDisplay();
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);
    //display.println(currentTime);

    display.print("Temperature: ");
    dryTemp = getTemp(pinDB);
    wetTemp = getTemp(pinWB);
    display.print(dryTemp);  
    display.println(" C"); //°C

    display.print("Humidity Sensor: ");
    humiditySensor = getHumidSensor();
    display.print(humiditySensor);  
    display.println(" %"); 
    
    RelativeHumidity = calculateHumid(dryTemp, wetTemp);
    display.print("Humidity: ");
    display.print(RelativeHumidity);  
    display.println(" %");

    if(bnt_was_pressed == 1){
    display.println("Encoder was pressed");
    display.println(tempMode[now.day()%22][5] + 0.1*counter);
    }
    

    display.display();
  }

  void draw(float a){
    display.clearDisplay();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(0,0);
    display.print("   ");
    display.print(a);
    display.print("   ");   
    }
