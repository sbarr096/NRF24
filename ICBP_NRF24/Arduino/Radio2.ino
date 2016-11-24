#include<SPI.h>
#include<RF24.h>

//CE & CSN Pins
RF24 radio2(9,10);

/* ===================================
************PUBLIC DOMAIN*************
=====================================*/

//Setup Pins Functionality
  int Analog_Vin0_Pin = 0;  //Pin used for Voltage Sensor Yellow
  int Analog_Vin1_Pin = 2;  //Pin used for Current Sensor White connected to Neutral
  int Analog_Vin2_Pin = 1;  //Pin used for Current Sensor Green connected to higher point

//  int Triac_CTRL_Pin = 10;  //Pin used for Triac Gate Control
  
//Testing Variables
  int V_testsensor = 0;
  float V_test = 0;
  int Analog_Vout_Pin = 3;  //Pin used for Triac Gate Control

//Setup Variables. Initializing 
  int V_sensor = 0; // volatge sensor
  int V_sensor1 = 0;  // positive voltage used for current sensor
  int V_sensor2 = 0;  // negative volatge used for current sensor
  int i=0; // counter
  float MAX =0;         // Max Voltage value founded

  float Vsensor = 0;  //Real Voltage read at the sensor
  float V1sensor = 0; //Real Volatge read at the sensor
  float V2sensor = 0; //Real Volatge read at the sensor
  float V = 0;    //Real Voltage going to the load
  float I = 0;    //Real Current going to the load
  float P = 0;    //Real Total Power Consumed

  
/* ==========================================
********RESET RUNS ONCE WHEN PRESSED*********
=============================================*/

void setup() 
  {
  // SETTING DIGITAL PINS AS OUTPUT PINS AND INITIALIZING TO 0.
 // pinMode(Triac_CTRL_Pin, OUTPUT);      // sets the digital pin 10 as output
  pinMode(2, OUTPUT);  // sets the digital pin as output
  pinMode(3, OUTPUT);  // sets the digital pin as output
  pinMode(4, OUTPUT);  // sets the digital pin as output
  pinMode(5, OUTPUT);  // sets the digital pin as output
  pinMode(6, OUTPUT);  // sets the digital pin as output
  pinMode(7, OUTPUT);  // sets the digital pin as output
  pinMode(8, OUTPUT);  // sets the digital pin as output


  // INITIALIZING DIGTAL PINS TO 0.
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);

  
//---NRF24 SPI comm-------

  Serial.begin(9600);              // initialize serial communication at 9600 bits per second

  radio2.begin();
  radio2.setPALevel(RF24_PA_MAX);
  radio2.setChannel(0x76);
  radio2.openWritingPipe(0xF0F0F0F0B5LL);
  const uint64_t pipe = 0xE8E8F0F0E1LL;
  radio2.openReadingPipe (1, pipe);
  
  radio2.enableDynamicPayloads();
  radio2.powerUp();

  }

/* ===================================
***********INFINITIVE LOOP************
=====================================*/
void loop() 
{
  radio2.startListening();
  Serial.println("starting loop. radio2 ON Listening for command from RPi");
  Serial.println("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------");

  char receivedMsg[32] = {0};

  
  i++; //COUNTER
 // digitalWrite(Triac_CTRL_Pin, HIGH);   // SETS THE TRIAC OFF
  
// Read the input on analog Pins:   
  V_sensor = analogRead(Analog_Vin0_Pin);
  V_sensor1 = analogRead(Analog_Vin1_Pin);
  V_sensor2 = analogRead(Analog_Vin2_Pin);

// CONVERT TO ACTUAL VOLTAGE READING BY THE CHIP
  Vsensor = V_sensor*(5.0/1023.0);
  V1sensor = V_sensor1*(5.0/1023.0);
  V2sensor = V_sensor2*(5.0/1023.0);

//CONVERTING TO BREAKER REAL INPUT VALUES

 I = 22.22;
 V = 222.22;
 // I = (V1sensor-V2sensor)*4; 
 // V = (Vsensor*30);
//  P = V*I;
/*  

if (i<=5)
  {
  //digitalWrite(Triac_CTRL_Pin, LOW);   // sets the TRIAC ON
   analogWrite(Analog_Vout_Pin, 0);    // SETS THE TRIAC OFF
  
  }
if (i>5 && i<=10)
  {
  // digitalWrite(Triac_CTRL_Pin, HIGH);   // sets the TRIAC OFF
    analogWrite(Analog_Vout_Pin, 1023);    // SETS THE TRIAC OFF
  }
if (i>=10)
  {
    i=0;
  }
*/
  
//PRINT OUT VALUES:
  Serial.print("TEST #: ");
  Serial.println(i);
  Serial.print("INPUT:  VOLTAGE: ");
  Serial.println(V);
  Serial.print("REAL INPUT CURRENT:  ");
  Serial.println(I); 
  Serial.print("POWER CONSUMED: ");
  Serial.println(P);
  Serial.print("SENSOR: VOLTAGE: ");
  Serial.println(Vsensor);
  Serial.print("1ST PIN CURRENT: ");
  Serial.println(V1sensor);
  Serial.print("2ND PIN CURRENT: ");
  Serial.print(V2sensor);
  Serial.print("  ||");  
  Serial.println(" ");
  Serial.println("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  Serial.println("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
  Serial.println("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------");


  if (radio2.available()){
    radio2.read(receivedMsg, sizeof(receivedMsg));
    Serial.print("Meesage received from RPi is: ");
    Serial.println(receivedMsg);
    Serial.println("Turning OFF radio2");
    radio2.stopListening();

    Serial.println("Test to send data to Rpi");
    String stringMsg(receivedMsg);
    if (stringMsg == "radio2"){
        
        float MyArray[] = {V, I};  
        radio2.write (&MyArray, sizeof(MyArray));  
      
      }
    
    }

/* =====================================
************PIN VOLTAGE TEST*************
=======================================*/
 

delay(100);        // delay in between reads for stability ( 9600 -->  t = 1 SEG )
}


