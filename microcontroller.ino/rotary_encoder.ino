void rotary_encoder(){
  aState = digitalRead(outputA);
  oldCounter = counter;
  if ( aState != aLastState)
  {
    if (digitalRead(outputB) != aState)
      counter--;
    else
      counter++;
    Serial.println(counter);
  }
  aLastState = aState;
}

void rotary_switch() {
  if (digitalRead(pinEncoder) == LOW )
  {
    if(bnt_was_pressed == 1){
      Serial.println("Hold");
      }
    time_now = millis();
    if (hold + hold_timer < time_now){
      //TODO
      return;
    }
    
    if (bnt_was_pressed == 0){
      bnt_was_pressed = 1;
      Serial.println("Pressed");
    }
  }
  else{
    bnt_was_pressed = 0;
    hold = millis();
  }

}
