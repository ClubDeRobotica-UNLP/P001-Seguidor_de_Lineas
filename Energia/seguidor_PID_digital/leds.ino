

/*
    1 - LEDsInit
    2 - LEDsDrive
	3 - LEDsBlink
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

void LEDsBlink(bool stateLED1, bool stateLED2, byte blinks, byte blinkDelay){
 
 for(int k=1 ; k <= blinks ; k++)
 {
	digitalWrite(LED1, stateLED1);
	digitalWrite(LED2, stateLED2);
	stateLED1=!stateLED1;
	stateLED2=!stateLED2;
	delay(blinkDelay);
  }
  
}