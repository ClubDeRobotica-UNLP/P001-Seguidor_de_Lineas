#define KP 1  
#define KD 10	// Probar con KD >> KP 
#define VEL_MAX 130
#define VEL VEL_MAX/3*2// con 200
#define DT 1000  // Cada 1 ms accion de control.

#define M1PWM P3_0
#define M1A P2_0
#define M2PWM P2_2
#define M2A P3_3
#define LED1 P3_2
#define LED2 P3_4
#define M1E P3_1
#define M2E P3_1

#define S1 P1_5
#define S2 P1_4
#define S3 P1_3
#define S4 P1_6
#define S5 P1_7
#define LEDON P2_6


#define DT2 50000 // 200000

#define LED1 P3_2
#define LED2 P3_4

#define BOTON P2_4

// TIME 
unsigned long dt = 0; 
unsigned long Now = 0;
unsigned long LastTime[1] = {0};
unsigned long LastTime2[1] = {0};

// CONTROLLER
float LastError[1] = {0};
float Error[1] = {0};
int Constantes[4] = {KP,KD,DT,VEL};
int Vel_filtrada[1] = {0};

// SENSORES
boolean Ledon_state = false;

// STATES
byte Flags[1] = {0};
boolean Flag = false;

void setup(){
  
  Serial.begin(9600);
  Serial.println("/*** sigue_linea_PD ***/");
  Serial.println("*** INITS ***");
  LEDsInit();
  MotoresInit(M1A, M2A, M1E, M2E);
  digitalWrite(M1E, 0);
  digitalWrite(M2E, 0);
  pinMode(BOTON,INPUT_PULLUP); // Boton para programa
  pinMode(LEDON, OUTPUT); 	   // Salida para encender CNY

  while(digitalRead(BOTON) == 1)
  { 
	LEDsBlink(1, 1, 1, 200);
  }

  LEDsDrive(1,1);

  
  while(digitalRead(BOTON) == 1){}
  
  Serial.println("*** GO! ***");
  LEDsDrive(0,0);
  
}

void loop(){
  
  if(digitalRead(BOTON) == 0)
  {
   Flag = !Flag;
   Ledon_state = !Ledon_state;
   digitalWrite(LEDON,Ledon_state); // Apago Sensores si Ledon_state = 1 !
   digitalWrite(M1E, 1);
   digitalWrite(M2E, 1);
   delay(200); 
  }
  
  if(Flag == true)
  {
    Now = micros();
    dt = Now - *LastTime;     

    if(dt > Constantes[2])
    {
      Vel_filtrada[0] = LecturaSensores2(1, 0, Error, LastError, LastTime2, Flags);
      SeguirLinea(M1PWM, M1A, M2PWM, M2A, M1E, M2E, Vel_filtrada[0], Constantes[3], 0);  // Probar varios delays
      *LastTime = Now;
    }
    
  }
  else
  {
    LEDsDrive(0,0);
    digitalWrite(M1E, 0);
    digitalWrite(M2E, 0);
  }
  
}
