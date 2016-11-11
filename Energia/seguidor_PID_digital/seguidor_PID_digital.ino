#define KP 0.8  
#define KD KP/5.0 
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

#define N_UMBRALES 8

#define DT2 50000 // 200000

#define LED1 P3_2
#define LED2 P3_4

#define BOTON P2_4

//int SensorMin[5] = {200,200,200,200,200};
//int SensorMax[5] = {0,0,0,0,0};
//int* SensorMinMax;
//int* SensorMaxMin;
//int Sensores_raw[5] = {0,0,0,0,0};
//int Umbrales[3] = {0};
float LastError[1] = {0};
float Error[1] = {0};
//int FlagFueraPista[1] = {0};
int Constantes[4] = {KP,KD,DT,VEL};
unsigned long dt = 0; 
unsigned long Now = 0;
unsigned long LastTime[1] = {0};
unsigned long LastTime2[1] = {0};
byte Flags[1] = {0};
boolean Flag_case_1[1] = {0};
int Vel_filtrada[1] = {0};
//int Input;
//int LastInput[1] = {0};
boolean Flag = false;
boolean Ledon_state = false;

void setup(){
  
  Serial.begin(9600);
  Serial.println("/*** sigue_linea_PD ***/");
  Serial.println("*** SETUP ***");
  LEDsInit();
  MotoresInit(M1A, M2A, M1E, M2E);
  ApagarMotores(M1PWM, M1A, M2PWM, M2A);
  pinMode(BOTON,INPUT_PULLUP);
  
  Serial.println("- Presione boton para comenzar con la calibración de sensores...");
  while(digitalRead(BOTON) == 1){}
  Serial.println("*** CALIBRACION ***");
  delay(1000);
  LEDsDrive(1,0);
  pinMode(LEDON, OUTPUT); // Salida para encender CNY
  digitalWrite(LEDON,1); // Prendo Sensores
  /*
    MoverMotores(M1PWM, M1A, M2PWM, M2A, 50, -50);
    for(int j = 0;j <= 20; j++)
    {
      CalibrarSensores(SensorMin, SensorMax);
      delay(30);
    }
    MoverMotores(M1PWM, M1A, M2PWM, M2A, -50, 50);
    for(int j = 0;j <= 40; j++)
    {
      CalibrarSensores(SensorMin, SensorMax);
      delay(30);
    }
    MoverMotores(M1PWM, M1A, M2PWM, M2A, 50, -50);
    for(int j = 0;j <= 20; j++)
    {
      CalibrarSensores(SensorMin, SensorMax);
      delay(30);
    }

  SensorMinMax = detectarSensorMin(SensorMax);  
  SensorMaxMin = detectarSensorMax(SensorMin);  
    */
  ApagarMotores(M1PWM, M1A, M2PWM, M2A);
  //DeterminarUmbrales(&SensorMin[0], &SensorMax[0], &Umbrales[0], N_UMBRALES);
  digitalWrite(LEDON,0); // Apago Sensores
  LEDsDrive(0,0);
  Serial.println("*** FIN CALIBRACION ***");
  Serial.println("*** READY ***");
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
   delay(200); 
  }
  
  if(Flag == true)
  {
    Now = micros();
    dt = Now - *LastTime;     

    if(dt > Constantes[2])
    {
      /**Vel_filtrada = LecturaSensores(1, 0, 0, SensorMaxMin, SensorMinMax, LastError, FlagFueraPista, false, LastTime2); // Esta funcion tarda 1 ms aprox      
      SeguirLinea(M1PWM, M1A, M2PWM, M2A, M1E, M2E, Vel_filtrada[0], Constantes[3]);  // Esta funcion tarda 50 us aprox.
      *LastTime = Now;*/
      Vel_filtrada[0] = LecturaSensores2(1, 0, Error, LastError, LastTime2, Flags, Flag_case_1);
      SeguirLinea(M1PWM, M1A, M2PWM, M2A, M1E, M2E, Vel_filtrada[0], Constantes[3]);  // Esta funcion tarda 50 us aprox.
      *LastTime = Now;
    }
    
  }
  else
  {
    LEDsDrive(0,0);
    ApagarMotores(M1PWM, M1A, M2PWM, M2A);
  }
  
}
