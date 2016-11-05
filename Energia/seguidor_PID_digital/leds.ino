

/*
    1 - LEDsInit
    2 - LEDsDrive
*/

void LEDsInit(){
 
 pinMode(LED1,OUTPUT);
 pinMode(LED2,OUTPUT); 
 digitalWrite(LED1,0);
 digitalWrite(LED2,0);
 
}

void LEDsDrive(bool stateLED1, bool stateLED2){
 
  digitalWrite(LED1, stateLED1);
  digitalWrite(LED2, stateLED2);
  
}
