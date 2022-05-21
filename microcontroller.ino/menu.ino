void menu(){
  display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);

    display.print("Temperature: ");
    dryTemp = getTemp(pinDB);
    wetTemp = getTemp(pinWB);

    //dryTemp = 19.789767;
   // wetTemp = 11.789767;
    display.print(dryTemp); 
  
  
  
  
  }
