#include "pyCommsLib.h"
#include <Wire.h>  // Used to establish serial communication on the I2C bus
#include "SparkFun_TMAG5273_Arduino_Library.h" // Used to send and recieve specific information from our sensor

String msgName[] = {"hall","Dist_L_X", "Dist_L_Y", "Dist_L_Z", "Dist_R_X", "Dist_R_Y", "Dist_R_Z", "Dist_T_X", "Dist_T_Y", "Dist_T_Z"};
String dataCarrier[11];
// String dataCarrier[1];


#define TMAG_PIN 0 
#define PMOS_PIN 2

#define LeftFingerPart 0 //ProxL, MiddL, DistL
#define RightFingerPart 1 //ProxR, MiddR, DistR, DistT

//Right and Left as seen from top of PCB = back of the finger
uint8_t I2C_Add_DistT = 0x78;
uint8_t I2C_Add_DistR = 0x22;
uint8_t I2C_Add_DistL = 0x78;

TMAG5273 DistT; // Initialize hall-effect sensor
TMAG5273 DistR;
TMAG5273 DistL;


void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  delay(20);
}


void setup() {
  // Start the serial communication.
  Serial.begin(115200);
  analogReadResolution(12);

  pinMode(TMAG_PIN,OUTPUT); 
  pinMode(PMOS_PIN,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(TMAG_PIN, LOW); //Do not power on ProxL
  digitalWrite(PMOS_PIN, LOW);

  Wire.begin();
  TCA9548A(RightFingerPart);                    //RIGHT & TOP
  DistR.begin(I2C_Add_DistR, Wire);
  DistT.begin(I2C_Add_DistT, Wire);

  TCA9548A(LeftFingerPart);                     //LEFT;
  DistL.begin(I2C_Add_DistL, Wire);



  // Connect with the Python side
  init_python_communication();
}


void loop() {

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  float Dist_L_X=0;
  float Dist_L_Y=0;
  float Dist_L_Z=0;

  float Dist_R_X=0;
  float Dist_R_Y=0;
  float Dist_R_Z=0;

  float Dist_T_X=0;
  float Dist_T_Y=0;
  float Dist_T_Z=0;
  float value = 0;

  //Hall value for the spring
  for(int i = 0; i<100; i++) {
    value += analogRead(0);
  }
  value /= 100;
  dataCarrier[0] = String(value);

  // //Hall values for the finger

  TCA9548A(LeftFingerPart);
 
  if (DistL.getMagneticChannel() != 0)
  {
    Dist_L_X=DistL.getXData();
    Dist_L_Y=DistL.getYData();
    Dist_L_Z=DistL.getZData();
    dataCarrier[1]=String(Dist_L_X);
    dataCarrier[2]=String(Dist_L_Y);
    dataCarrier[3]=String(Dist_L_Z);
  }
  else
  {
    dataCarrier[1]=String(0);
    dataCarrier[2]=String(0);
    dataCarrier[3]=String(0);
  }

  TCA9548A(RightFingerPart); 

  if (DistR.getMagneticChannel() != 0)
  {
    Dist_R_X=DistR.getXData();
    Dist_R_Y=DistR.getYData();
    Dist_R_Z=DistR.getZData();
    dataCarrier[4]=String(Dist_R_X);
    dataCarrier[5]=String(Dist_R_Y);
    dataCarrier[6]=String(Dist_R_Z);
  }
  else
  {
    dataCarrier[4]=String(0);
    dataCarrier[5]=String(0);
    dataCarrier[6]=String(0);
  }


  if (DistT.getMagneticChannel() != 0)
  {
    Dist_T_X=DistT.getXData();
    Dist_T_Y=DistT.getYData();
    Dist_T_Z=DistT.getZData();
    dataCarrier[7]=String(Dist_T_X);
    dataCarrier[8]=String(Dist_T_Y);
    dataCarrier[9]=String(Dist_T_Z);
  }
  else
  {
    dataCarrier[7]=String(0);
    dataCarrier[8]=String(0);
    dataCarrier[9]=String(0);
  }

  load_msg_to_python(msgName, dataCarrier, size_of_array(msgName));
  sync();
}