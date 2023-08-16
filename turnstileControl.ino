void turnstileControl() {
  
  if(isEntrance == 1){
    digitalWrite(relay1Pin, LOW);
    delay(500);
    digitalWrite(relay1Pin, HIGH);
  } else {
    digitalWrite(relay2Pin, LOW);
    delay(500);
    digitalWrite(relay2Pin, HIGH);
  }
    
}