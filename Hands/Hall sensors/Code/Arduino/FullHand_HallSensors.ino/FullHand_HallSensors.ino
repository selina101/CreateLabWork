
#include <Wire.h>  // Used to establish serial communication on the I2C bus
#include "SparkFun_TMAG5273_Arduino_Library.h" // Used to send and recieve specific information from our sensor
#include "pyCommsLib.h"

#include "I2CScanner.h"

#define PYTHON_MODE 0
#define DEBUG_MODE 1

int mode = DEBUG_MODE;
// int mode = PYTHON_MODE;
bool scan_I2C = false;

// I2CScanner scanner;

#define THUMB_CONNECTED true
#define IDX_CONNECTED true
#define MIDD_CONNECTED true
#define RING_CONNECTED true
#define PINKY_CONNECTED true


#define PMOS_PIN 5

#define THUMB_PIN 0
#define INDEX_PIN 1
#define MIDDLE_PIN 2
#define RING_PIN 3
#define PINKY_PIN 4

#define THUMB_BUS 0
#define THUMB_MUX 0x70

#define IDX_LEFT_BUS 2
#define IDX_RIGHT_BUS 3
#define IDX_MUX 0x70

#define MIDD_LEFT_BUS 4
#define MIDD_RIGHT_BUS 5
#define MIDD_MUX 0x70

#define RING_LEFT_BUS 0
#define RING_RIGHT_BUS 1
#define RING_MUX 0x71

#define PINKY_LEFT_BUS 2
#define PINKY_RIGHT_BUS 3
#define PINKY_MUX 0x71



String msgName[] = {"Th_Dist_L_X", "Th_Dist_R_X", "Th_Dist_T_X", 
    "Idx_Dist_L_X", "Idx_Dist_R_X", "Idx_Dist_T_X","Idx_Midd_L_X", "Idx_Midd_R_X","Idx_Prox_L_X", "Idx_Prox_R_X", 
    "Midd_Dist_L_X", "Midd_Dist_R_X", "Midd_Dist_T_X", "Midd_Midd_L_X", "Midd_Midd_R_X","Midd_Prox_L_X", "Midd_Prox_R_X",  
    "Ring_Dist_L_X", "Ring_Dist_R_X", "Ring_Dist_T_X", "Ring_Midd_L_X", "Ring_Midd_R_X","Ring_Prox_L_X", "Ring_Prox_R_X",  
    "Pinky_Dist_L_X", "Pinky_Dist_R_X", "Pinky_Dist_T_X","Pinky_Prox_L_X", "Pinky_Prox_R_X"};

String dataCarrier[29];

uint8_t I2C_Add_Th_Dist_L = 0x35;
uint8_t I2C_Add_Th_Dist_R = 0x78;
uint8_t I2C_Add_Th_Dist_T = 0x22;



uint8_t I2C_Add_Idx_Dist_L = 0x78;
uint8_t I2C_Add_Idx_Dist_R = 0x22;
uint8_t I2C_Add_Idx_Dist_T = 0x78;
uint8_t I2C_Add_Idx_Midd_L = 0x22;
uint8_t I2C_Add_Idx_Midd_R = 0x35;
uint8_t I2C_Add_Idx_Prox_L = 0x35;
uint8_t I2C_Add_Idx_Orriginal_Prox_R = 0x35;
uint8_t I2C_Add_Idx_Prox_R = 0x18;
// uint8_t I2C_Add_Idx_Prox_R = 0x22;



uint8_t I2C_Add_Midd_Dist_L = 0x78;
uint8_t I2C_Add_Midd_Dist_R = 0x22;
uint8_t I2C_Add_Midd_Dist_T = 0x78;
uint8_t I2C_Add_Midd_Midd_L = 0x22;
uint8_t I2C_Add_Midd_Midd_R = 0x35;
uint8_t I2C_Add_Midd_Prox_L = 0x35;
uint8_t I2C_Add_Midd_Orriginal_Prox_R = 0x35;
uint8_t I2C_Add_Midd_Prox_R = 0x18;



uint8_t I2C_Add_Ring_Dist_L = 0x78;
uint8_t I2C_Add_Ring_Dist_R = 0x22;
uint8_t I2C_Add_Ring_Dist_T = 0x78;
uint8_t I2C_Add_Ring_Midd_L = 0x22;
uint8_t I2C_Add_Ring_Midd_R = 0x35;
uint8_t I2C_Add_Ring_Prox_L = 0x35;
uint8_t I2C_Add_Ring_Orriginal_Prox_R = 0x35;
uint8_t I2C_Add_Ring_Prox_R = 0x18;

uint8_t I2C_Add_Pinky_Dist_L = 0x22;
uint8_t I2C_Add_Pinky_Dist_R = 0x22;
uint8_t I2C_Add_Pinky_Dist_T = 0x78;
uint8_t I2C_Add_Pinky_Prox_L = 0x35;
uint8_t I2C_Add_Pinky_Prox_R = 0x35;


TMAG5273 Th_Dist_L;
TMAG5273 Th_Dist_R;
TMAG5273 Th_Dist_T;

TMAG5273 Idx_Dist_L;
TMAG5273 Idx_Dist_R;
TMAG5273 Idx_Dist_T;
TMAG5273 Idx_Midd_R;
TMAG5273 Idx_Midd_L;
TMAG5273 Idx_Prox_R;
TMAG5273 Idx_Prox_L;

TMAG5273 Midd_Dist_L;
TMAG5273 Midd_Dist_R;
TMAG5273 Midd_Dist_T;
TMAG5273 Midd_Midd_R;
TMAG5273 Midd_Midd_L;
TMAG5273 Midd_Prox_R;
TMAG5273 Midd_Prox_L;

TMAG5273 Ring_Dist_L;
TMAG5273 Ring_Dist_R;
TMAG5273 Ring_Dist_T;
TMAG5273 Ring_Midd_R;
TMAG5273 Ring_Midd_L;
TMAG5273 Ring_Prox_R;
TMAG5273 Ring_Prox_L;

TMAG5273 Pinky_Dist_L;
TMAG5273 Pinky_Dist_R;
TMAG5273 Pinky_Dist_T;
TMAG5273 Pinky_Prox_L;
TMAG5273 Pinky_Prox_R;


float Th_Dist_L_X_init=0;
float Th_Dist_R_X_init=0;
float Th_Dist_T_X_init=0;

float Idx_Dist_L_X_init=0;
float Idx_Dist_R_X_init=0;
float Idx_Dist_T_X_init=0;
float Idx_Midd_L_X_init=0;
float Idx_Midd_R_X_init=0;
float Idx_Prox_R_X_init=0;
float Idx_Prox_L_X_init=0;

float Midd_Dist_L_X_init=0;
float Midd_Dist_R_X_init=0;
float Midd_Dist_T_X_init=0;
float Midd_Midd_L_X_init=0;
float Midd_Midd_R_X_init=0;
float Midd_Prox_R_X_init=0;
float Midd_Prox_L_X_init=0;

float Ring_Dist_L_X_init=0;
float Ring_Dist_R_X_init=0;
float Ring_Dist_T_X_init=0;
float Ring_Midd_L_X_init=0;
float Ring_Midd_R_X_init=0;
float Ring_Prox_R_X_init=0;
float Ring_Prox_L_X_init=0;

float Pinky_Dist_L_X_init=0;
float Pinky_Dist_R_X_init=0;
float Pinky_Dist_T_X_init=0;
float Pinky_Prox_R_X_init=0;
float Pinky_Prox_L_X_init=0;


void TCA9548A(uint8_t bus, uint8_t address){
  Wire.beginTransmission(address);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  // Serial.print("bus: ");
  // Serial.print(bus);
  // Serial.print(" of MUX address: ");
  // Serial.println(address, HEX);
  // delay(20);
}

void TCA9548A_disconnect(uint8_t address){
  Wire.beginTransmission(address);
  Wire.write(0);  // no channel selected
  Wire.endTransmission();
}

float get_sensor_value(TMAG5273 TMAG, bool print=false){
  float X_sensor_value=0;
  if(TMAG.getMagneticChannel() != 0)
    {
      X_sensor_value=TMAG.getXData();
      if(print==true)
      {
        Serial.print(X_sensor_value);
        Serial.print(", ");
      }
      
    }
    else
    {
      X_sensor_value=0;
      // Serial.print("not available ");
    }

  // Serial.print("returned value: ");  
  // Serial.println(X_sensor_value);  
  return X_sensor_value;
}

void get_initial_values(){
  if (THUMB_CONNECTED==true)
  {
    TCA9548A(THUMB_BUS,THUMB_MUX); 
    Th_Dist_L_X_init = get_sensor_value(Th_Dist_L);
    Th_Dist_R_X_init = get_sensor_value(Th_Dist_R);
    Th_Dist_T_X_init = get_sensor_value(Th_Dist_T);
  }
  // Serial.print(" | ");

  if (IDX_CONNECTED==true)
  {
    TCA9548A(IDX_LEFT_BUS,IDX_MUX); 
    Idx_Dist_L_X_init = get_sensor_value(Idx_Dist_L);
    Idx_Midd_L_X_init = get_sensor_value(Idx_Midd_L);
    Idx_Prox_L_X_init = get_sensor_value(Idx_Prox_L);

    TCA9548A(IDX_RIGHT_BUS,IDX_MUX); 
    Idx_Dist_R_X_init = get_sensor_value(Idx_Dist_R);
    Idx_Dist_T_X_init = get_sensor_value(Idx_Dist_T);
    Idx_Midd_R_X_init = get_sensor_value(Idx_Midd_R);
    Idx_Prox_R_X_init = get_sensor_value(Idx_Prox_R);
  }
  // Serial.print(" | ");

  if (MIDD_CONNECTED==true)
  {
    TCA9548A(MIDD_LEFT_BUS,MIDD_MUX);
    Midd_Dist_L_X_init = get_sensor_value(Midd_Dist_L);
    Midd_Midd_L_X_init = get_sensor_value(Midd_Midd_L);
    Midd_Prox_L_X_init = get_sensor_value(Midd_Prox_L);

    TCA9548A(MIDD_RIGHT_BUS,MIDD_MUX); 
    Midd_Dist_R_X_init = get_sensor_value(Midd_Dist_R);
    Midd_Dist_T_X_init = get_sensor_value(Midd_Dist_T);
    Midd_Midd_R_X_init = get_sensor_value(Midd_Midd_R);
    Midd_Prox_R_X_init = get_sensor_value(Midd_Prox_R);
  }
  // Serial.print(" | ");

  TCA9548A_disconnect(0x70);

  if (RING_CONNECTED==true)
  {
    TCA9548A(RING_LEFT_BUS,RING_MUX);
    Ring_Dist_L_X_init = get_sensor_value(Ring_Dist_L);
    Ring_Midd_L_X_init = get_sensor_value(Ring_Midd_L);
    Ring_Prox_L_X_init = get_sensor_value(Ring_Prox_L);

    TCA9548A(RING_RIGHT_BUS,RING_MUX); 
    Ring_Dist_R_X_init = get_sensor_value(Ring_Dist_R);
    Ring_Dist_T_X_init = get_sensor_value(Ring_Dist_T);
    Ring_Midd_R_X_init = get_sensor_value(Ring_Midd_R);
    Ring_Prox_R_X_init = get_sensor_value(Ring_Prox_R);
  }
  // Serial.print(" | ");

  if (PINKY_CONNECTED==true)
  {
    TCA9548A(PINKY_LEFT_BUS,PINKY_MUX);
    Pinky_Dist_L_X_init = get_sensor_value(Pinky_Dist_L);
    Pinky_Prox_L_X_init = get_sensor_value(Pinky_Prox_L);

    TCA9548A(PINKY_RIGHT_BUS,PINKY_MUX); 
    Pinky_Dist_R_X_init = get_sensor_value(Pinky_Dist_R);
    Pinky_Dist_T_X_init = get_sensor_value(Pinky_Dist_T);
    Pinky_Prox_R_X_init = get_sensor_value(Pinky_Prox_R);
  }
  
  TCA9548A_disconnect(0x71);
}

void setup() {

  Serial.begin(9600);

  // put your setup code here, to run once:
  pinMode(PMOS_PIN,OUTPUT);
  pinMode(INDEX_PIN,OUTPUT);
  pinMode(MIDDLE_PIN,OUTPUT);
  pinMode(RING_PIN,OUTPUT);
  
  pinMode(LED_BUILTIN,OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);


  digitalWrite(PMOS_PIN, HIGH); //TURN OFF THE POWER FOR TMAGs

  digitalWrite(INDEX_PIN, LOW); //TURN OFF THE POWER FOR INDEX TMAG
  digitalWrite(MIDDLE_PIN, LOW); //TURN OFF THE POWER FOR MIDDLE TMAG
  digitalWrite(RING_PIN, LOW); //TURN OFF THE POWER FOR RING TMAG


  Wire.begin();


  TCA9548A_disconnect(0x70);
  TCA9548A_disconnect(0x71);

  // scanner.Init();

  // delay(200);
  TCA9548A(IDX_RIGHT_BUS,IDX_MUX); 
  //  delay(200);
  digitalWrite(INDEX_PIN, HIGH); //TURN ON THE POWER FOR INDEX TMAG
  delay(100);
  Idx_Prox_R.begin(I2C_Add_Idx_Orriginal_Prox_R, Wire);
  // Serial.println(Idx_Prox_R.setI2CAddress(0x18), HEX);
  Idx_Prox_R.setI2CAddress(I2C_Add_Idx_Prox_R);
  // delay(100);
  // scanner.Scan();
  // Idx_Prox_R.setI2CAddress(I2C_Add_Idx_Prox_R);

  TCA9548A(MIDD_RIGHT_BUS,MIDD_MUX); 
  digitalWrite(MIDDLE_PIN, HIGH); //TURN ON THE POWER FOR INDEX TMAG
  delay(100);
  Midd_Prox_R.begin(I2C_Add_Midd_Orriginal_Prox_R, Wire);
  // Serial.println(Midd_Prox_R.setI2CAddress(0x18), HEX);
  Midd_Prox_R.setI2CAddress(I2C_Add_Midd_Prox_R);
  // delay(100);
  // scanner.Scan();
  // Midd_Prox_R.setI2CAddress(I2C_Add_Midd_Prox_R);
  
  TCA9548A_disconnect(0x70);

  TCA9548A(RING_RIGHT_BUS,RING_MUX); 
  digitalWrite(RING_PIN, HIGH); //TURN ON THE POWER FOR INDEX TMAG
  delay(100);
  Ring_Prox_R.begin(I2C_Add_Ring_Orriginal_Prox_R, Wire);
  // Serial.println(Ring_Prox_R.setI2CAddress(0x18), HEX);
  Ring_Prox_R.setI2CAddress(I2C_Add_Ring_Prox_R);
  // delay(100);
  // scanner.Scan();
  // Idx_Prox_R.setI2CAddress(I2C_Add_Ring_Prox_R);

  TCA9548A_disconnect(0x71);


  
  

  digitalWrite(PMOS_PIN, LOW); //TURN ON THE POWER FOR TMAGs

  TCA9548A(THUMB_BUS,THUMB_MUX); 
  Th_Dist_L.begin(I2C_Add_Th_Dist_L, Wire);
  Th_Dist_R.begin(I2C_Add_Th_Dist_R, Wire);
  Th_Dist_T.begin(I2C_Add_Th_Dist_T, Wire);


  TCA9548A(IDX_LEFT_BUS,IDX_MUX); 
  Idx_Dist_L.begin(I2C_Add_Idx_Dist_L, Wire);
  Idx_Midd_L.begin(I2C_Add_Idx_Midd_L, Wire);
  Idx_Prox_L.begin(I2C_Add_Idx_Prox_L, Wire);
  
  TCA9548A(IDX_RIGHT_BUS,IDX_MUX);
  Idx_Dist_R.begin(I2C_Add_Idx_Dist_R, Wire);
  Idx_Dist_T.begin(I2C_Add_Idx_Dist_T, Wire);
  Idx_Midd_R.begin(I2C_Add_Idx_Midd_R, Wire);


  TCA9548A(MIDD_LEFT_BUS,MIDD_MUX); 
  Midd_Dist_L.begin(I2C_Add_Midd_Dist_L, Wire);
  Midd_Midd_L.begin(I2C_Add_Midd_Midd_L, Wire);
  Midd_Prox_L.begin(I2C_Add_Midd_Prox_L, Wire);
  
  TCA9548A(MIDD_RIGHT_BUS,MIDD_MUX);
  Midd_Dist_R.begin(I2C_Add_Midd_Dist_R, Wire);
  Midd_Dist_T.begin(I2C_Add_Midd_Dist_T, Wire);
  Midd_Midd_R.begin(I2C_Add_Midd_Midd_R, Wire);
  

  TCA9548A_disconnect(0x70);



  TCA9548A(RING_LEFT_BUS,RING_MUX); 
  Ring_Dist_L.begin(I2C_Add_Ring_Dist_L, Wire);
  Ring_Midd_L.begin(I2C_Add_Ring_Midd_L, Wire);
  Ring_Prox_L.begin(I2C_Add_Ring_Prox_L, Wire);
  
  TCA9548A(RING_RIGHT_BUS,RING_MUX);
  Ring_Dist_R.begin(I2C_Add_Ring_Dist_R, Wire);
  Ring_Dist_T.begin(I2C_Add_Ring_Dist_T, Wire);
  Ring_Midd_R.begin(I2C_Add_Ring_Midd_R, Wire);




  TCA9548A(PINKY_LEFT_BUS,PINKY_MUX); 
  Pinky_Dist_L.begin(I2C_Add_Pinky_Dist_L, Wire);
  Pinky_Prox_L.begin(I2C_Add_Pinky_Prox_L, Wire);
  
  TCA9548A(PINKY_RIGHT_BUS,PINKY_MUX);
  Pinky_Dist_R.begin(I2C_Add_Pinky_Dist_R, Wire);
  Pinky_Dist_T.begin(I2C_Add_Pinky_Dist_T, Wire);
  Pinky_Prox_R.begin(I2C_Add_Pinky_Prox_R, Wire);
  
  TCA9548A_disconnect(0x71);

  get_initial_values();
  
  delay(2000);

  // Serial.println("HERE");
  
  if(mode==PYTHON_MODE){
    init_python_communication();
  }

  // Serial.println("HERE 1");

  /*if (mode==DEBUG_MODE && scan_I2C==true)
  {
    Serial.println("HERE 2");
    scanner.Init();
    Serial.println("HERE 3");


    TCA9548A(0,0x70);
    Serial.println("Thumb Left");
    scanner.Scan();
    delay(5000);

    TCA9548A(1,0x70);
    Serial.println("Thumb Right");
    scanner.Scan();
    delay(5000);

    TCA9548A(2,0x70);
    Serial.println("Idx Left");
    scanner.Scan();
    delay(5000);

    TCA9548A(3,0x70);
    Serial.println("Idx Right");
    scanner.Scan();
    delay(5000);

    TCA9548A(4,0x70);
    Serial.println("Middle Left");
    scanner.Scan();
    delay(5000);

    TCA9548A(5,0x70);
    Serial.println("Middle right");
    scanner.Scan();
    delay(5000);

    Wire.beginTransmission(0x70);
    Wire.write(0);  // no channel selected
    Wire.endTransmission();

    TCA9548A(0,0x71);
    Serial.println("Ring Left");
    scanner.Scan();
    delay(5000);

    TCA9548A(1,0x71);
    Serial.println("Ring right");
    scanner.Scan();
    delay(5000);

    TCA9548A(2,0x71);
    Serial.println("Pinky Left");
    scanner.Scan();
    delay(5000);

    TCA9548A(3,0x71);
    Serial.println("Pinky right");
    scanner.Scan();
    delay(5000);

    Wire.beginTransmission(0x71);
    Wire.write(0);  // no channel selected
    Wire.endTransmission();
  }*/
}

void loop() {

  float Th_Dist_L_X=0;
  float Th_Dist_R_X=0;
  float Th_Dist_T_X=0;

  float Idx_Dist_L_X=0;
  float Idx_Dist_R_X=0;
  float Idx_Dist_T_X=0;
  float Idx_Midd_R_X=0;
  float Idx_Midd_L_X=0;
  float Idx_Prox_R_X=0;
  float Idx_Prox_L_X=0;

  float Midd_Dist_L_X=0;
  float Midd_Dist_R_X=0;
  float Midd_Dist_T_X=0;
  float Midd_Midd_R_X=0;
  float Midd_Midd_L_X=0;
  float Midd_Prox_R_X=0;
  float Midd_Prox_L_X=0;


  float Ring_Dist_L_X=0;
  float Ring_Dist_R_X=0;
  float Ring_Dist_T_X=0;
  float Ring_Midd_R_X=0;
  float Ring_Midd_L_X=0;
  float Ring_Prox_R_X=0;
  float Ring_Prox_L_X=0;

  float Pinky_Dist_L_X=0;
  float Pinky_Dist_R_X=0;
  float Pinky_Dist_T_X=0;
  float Pinky_Prox_L_X=0;
  float Pinky_Prox_R_X=0;

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  if (THUMB_CONNECTED==true)
  {
    TCA9548A(THUMB_BUS,THUMB_MUX); 
    Th_Dist_L_X = get_sensor_value(Th_Dist_L)-Th_Dist_L_X_init;
    Th_Dist_R_X = get_sensor_value(Th_Dist_R)-Th_Dist_R_X_init;
    Th_Dist_T_X = get_sensor_value(Th_Dist_T)-Th_Dist_T_X_init;

    if (mode==DEBUG_MODE){
      Serial.print(Th_Dist_L_X);
      Serial.print(", ");
      Serial.print(Th_Dist_R_X);
      Serial.print(", ");
      Serial.print(Th_Dist_T_X);
      Serial.print(" | ");
    }
    if (mode==PYTHON_MODE){
      dataCarrier[0]=String(Th_Dist_L_X);
      dataCarrier[1]=String(Th_Dist_R_X);
      dataCarrier[2]=String(Th_Dist_T_X);
    }
  }

  if (IDX_CONNECTED==true)
  {
    TCA9548A(IDX_LEFT_BUS,IDX_MUX); 
    Idx_Dist_L_X = get_sensor_value(Idx_Dist_L)-Idx_Dist_L_X_init;
    Idx_Midd_L_X = get_sensor_value(Idx_Midd_L)-Idx_Midd_L_X_init;
    Idx_Prox_L_X = get_sensor_value(Idx_Prox_L)-Idx_Prox_L_X_init;

    TCA9548A(IDX_RIGHT_BUS,IDX_MUX); 
    Idx_Dist_R_X = get_sensor_value(Idx_Dist_R)-Idx_Dist_R_X_init;
    Idx_Dist_T_X = get_sensor_value(Idx_Dist_T)-Idx_Dist_T_X_init;
    Idx_Midd_R_X = get_sensor_value(Idx_Midd_R)-Idx_Midd_R_X_init;
    Idx_Prox_R_X = get_sensor_value(Idx_Prox_R)-Idx_Prox_R_X_init;

    if (mode==DEBUG_MODE){
      Serial.print(Idx_Dist_L_X);
      Serial.print(", ");
      Serial.print(Idx_Dist_R_X);
      Serial.print(", ");
      Serial.print(Idx_Dist_T_X);
      Serial.print(", ");
      Serial.print(Idx_Midd_L_X);
      Serial.print(", ");
      Serial.print(Idx_Midd_R_X);
      Serial.print(", ");
      Serial.print(Idx_Prox_L_X);
      Serial.print(", ");
      Serial.print(Idx_Prox_R_X);
      Serial.print(" | ");
    }
    if (mode==PYTHON_MODE){
      dataCarrier[3]=String(Idx_Dist_L_X);
      dataCarrier[4]=String(Idx_Dist_R_X);
      dataCarrier[5]=String(Idx_Dist_T_X);
      dataCarrier[6]=String(Idx_Midd_L_X);
      dataCarrier[7]=String(Idx_Midd_R_X);
      dataCarrier[8]=String(Idx_Prox_L_X);
      dataCarrier[9]=String(Idx_Prox_R_X);
    }
  }


  if (MIDD_CONNECTED==true)
  {
    TCA9548A(MIDD_LEFT_BUS,MIDD_MUX);
    Midd_Dist_L_X = get_sensor_value(Midd_Dist_L)-Midd_Dist_L_X_init;
    Midd_Midd_L_X = get_sensor_value(Midd_Midd_L)-Midd_Midd_L_X_init;
    Midd_Prox_L_X = get_sensor_value(Midd_Prox_L)-Midd_Prox_L_X_init;

    TCA9548A(MIDD_RIGHT_BUS,MIDD_MUX); 
    Midd_Dist_R_X = get_sensor_value(Midd_Dist_R)-Midd_Dist_R_X_init;
    Midd_Dist_T_X = get_sensor_value(Midd_Dist_T)-Midd_Dist_T_X_init;
    Midd_Midd_R_X = get_sensor_value(Midd_Midd_R)-Midd_Midd_R_X_init;
    Midd_Prox_R_X = get_sensor_value(Midd_Prox_R)-Midd_Prox_R_X_init;

    if (mode==DEBUG_MODE){
      Serial.print(Midd_Dist_L_X);
      Serial.print(", ");
      Serial.print(Midd_Dist_R_X);
      Serial.print(", ");
      Serial.print(Midd_Dist_T_X);
      Serial.print(", ");
      Serial.print(Midd_Midd_L_X);
      Serial.print(", ");
      Serial.print(Midd_Midd_R_X);
      Serial.print(", ");
      Serial.print(Midd_Prox_L_X);
      Serial.print(", ");
      Serial.print(Midd_Prox_R_X);
      Serial.print(" | ");
    }
    if (mode==PYTHON_MODE){
      dataCarrier[10]=String(Midd_Dist_L_X);
      dataCarrier[11]=String(Midd_Dist_R_X);
      dataCarrier[12]=String(Midd_Dist_T_X);
      dataCarrier[13]=String(Midd_Midd_L_X);
      dataCarrier[14]=String(Midd_Midd_R_X);
      dataCarrier[15]=String(Midd_Prox_L_X);
      dataCarrier[16]=String(Midd_Prox_R_X);
    }
  }

  TCA9548A_disconnect(0x70);

  if (RING_CONNECTED==true)
  {
    TCA9548A(RING_LEFT_BUS,RING_MUX);
    Ring_Dist_L_X = get_sensor_value(Ring_Dist_L)-Ring_Dist_L_X_init;
    Ring_Midd_L_X = get_sensor_value(Ring_Midd_L)-Ring_Midd_L_X_init;
    Ring_Prox_L_X = get_sensor_value(Ring_Prox_L)-Ring_Prox_L_X_init;

    TCA9548A(RING_RIGHT_BUS,RING_MUX); 
    Ring_Dist_R_X = get_sensor_value(Ring_Dist_R)-Ring_Dist_R_X_init;
    Ring_Dist_T_X = get_sensor_value(Ring_Dist_T)-Ring_Dist_T_X_init;
    Ring_Midd_R_X = get_sensor_value(Ring_Midd_R)-Ring_Midd_R_X_init;
    Ring_Prox_R_X = get_sensor_value(Ring_Prox_R)-Ring_Prox_R_X_init;

    if (mode==DEBUG_MODE){
      Serial.print(Ring_Dist_L_X);
      Serial.print(", ");
      Serial.print(Ring_Dist_R_X);
      Serial.print(", ");
      Serial.print(Ring_Dist_T_X);
      Serial.print(", ");
      Serial.print(Ring_Midd_L_X);
      Serial.print(", ");
      Serial.print(Ring_Midd_R_X);
      Serial.print(", ");
      Serial.print(Ring_Prox_L_X);
      Serial.print(", ");
      Serial.print(Ring_Prox_R_X);
      Serial.print(" | ");
    }
    if (mode==PYTHON_MODE){
      dataCarrier[17]=String(Ring_Dist_L_X);
      dataCarrier[18]=String(Ring_Dist_R_X);
      dataCarrier[19]=String(Ring_Dist_T_X);
      dataCarrier[20]=String(Ring_Midd_L_X);
      dataCarrier[21]=String(Ring_Midd_R_X);
      dataCarrier[22]=String(Ring_Prox_L_X);
      dataCarrier[23]=String(Ring_Prox_R_X);
    }
  }


  if (PINKY_CONNECTED==true)
  {
    TCA9548A(PINKY_LEFT_BUS,PINKY_MUX);
    Pinky_Dist_L_X = get_sensor_value(Pinky_Dist_L)-Pinky_Dist_L_X_init;
    Pinky_Prox_L_X = get_sensor_value(Pinky_Prox_L)-Pinky_Prox_L_X_init;

    TCA9548A(PINKY_RIGHT_BUS,PINKY_MUX); 
    Pinky_Dist_R_X = get_sensor_value(Pinky_Dist_R)-Pinky_Dist_R_X_init;
    Pinky_Dist_T_X = get_sensor_value(Pinky_Dist_T)-Pinky_Dist_T_X_init;
    Pinky_Prox_R_X = get_sensor_value(Pinky_Prox_R)-Pinky_Prox_R_X_init;
    
    
    if (mode==DEBUG_MODE){
      Serial.print(Pinky_Dist_L_X);
      Serial.print(", ");
      Serial.print(Pinky_Dist_R_X);
      Serial.print(", ");
      Serial.print(Pinky_Dist_T_X);
      Serial.print(", ");
      Serial.print(Pinky_Prox_L_X);
      Serial.print(", ");
      Serial.print(Pinky_Prox_R_X);
      Serial.print(" | ");
    }
    if (mode==PYTHON_MODE){
      dataCarrier[24]=String(Pinky_Dist_L_X);
      dataCarrier[25]=String(Pinky_Dist_R_X);
      dataCarrier[26]=String(Pinky_Dist_T_X);
      dataCarrier[27]=String(Pinky_Prox_L_X);
      dataCarrier[28]=String(Pinky_Prox_R_X);
    }
  }
  
  TCA9548A_disconnect(0x71);

  if (mode==DEBUG_MODE){
      Serial.println("");
      // delay(200);
  }

  if (mode==PYTHON_MODE){
      load_msg_to_python(msgName, dataCarrier, size_of_array(msgName));
      sync();
    }
}





// #include <Wire.h>  // Used to establish serial communication on the I2C bus
// #include "SparkFun_TMAG5273_Arduino_Library.h" // Used to send and recieve specific information from our sensor
// #include "pyCommsLib.h"

// #define PYTHON_MODE 0
// #define DEBUG_MODE 1

// int mode = PYTHON_MODE;

// #define THUMB_CONNECTED true
// #define IDX_CONNECTED true
// #define MIDD_CONNECTED true
// #define RING_CONNECTED true
// #define PINKY_CONNECTED true


// #define PMOS_PIN 5

// #define THUMB_PIN 0
// #define INDEX_PIN 1
// #define MIDDLE_PIN 2
// #define RING_PIN 3
// #define PINKY_PIN 4

// #define THUMB_BUS 0
// #define THUMB_MUX 0x70

// #define IDX_LEFT_BUS 2
// #define IDX_RIGHT_BUS 3
// #define IDX_MUX 0x70

// #define MIDD_LEFT_BUS 4
// #define MIDD_RIGHT_BUS 5
// #define MIDD_MUX 0x70

// #define RING_LEFT_BUS 0
// #define RING_RIGHT_BUS 1
// #define RING_MUX 0x71

// #define PINKY_LEFT_BUS 2
// #define PINKY_RIGHT_BUS 3
// #define PINKY_MUX 0x71



// String msgName[] = {"Th_Dist_L_X", "Th_Dist_R_X", "Th_Dist_T_X", "Idx_Dist_L_X", "Idx_Dist_R_X", "Idx_Dist_T_X", "Midd_Dist_L_X", "Midd_Dist_R_X", "Midd_Dist_T_X", 
//   "Ring_Dist_L_X", "Ring_Dist_R_X", "Ring_Dist_T_X", "Pinky_Dist_L_X", "Pinky_Dist_R_X", "Pinky_Dist_T_X", "Midd_Midd_L_X", "Midd_Midd_R_X"};

// String dataCarrier[17];

// uint8_t I2C_Add_Th_Dist_L = 0x35;
// uint8_t I2C_Add_Th_Dist_R = 0x78;
// uint8_t I2C_Add_Th_Dist_T = 0x22;

// uint8_t I2C_Add_Idx_Dist_L = 0x78;
// uint8_t I2C_Add_Idx_Dist_R = 0x22;
// uint8_t I2C_Add_Idx_Dist_T = 0x78;

// uint8_t I2C_Add_Midd_Dist_L = 0x78;
// uint8_t I2C_Add_Midd_Dist_R = 0x22;
// uint8_t I2C_Add_Midd_Dist_T = 0x78;

// uint8_t I2C_Add_Ring_Dist_L = 0x78;
// uint8_t I2C_Add_Ring_Dist_R = 0x22;
// uint8_t I2C_Add_Ring_Dist_T = 0x78;

// uint8_t I2C_Add_Pinky_Dist_L = 0x22;
// uint8_t I2C_Add_Pinky_Dist_R = 0x22;
// uint8_t I2C_Add_Pinky_Dist_T = 0x78;


// TMAG5273 Th_Dist_L;
// TMAG5273 Th_Dist_R;
// TMAG5273 Th_Dist_T;

// TMAG5273 Idx_Dist_L;
// TMAG5273 Idx_Dist_R;
// TMAG5273 Idx_Dist_T;

// TMAG5273 Midd_Dist_L;
// TMAG5273 Midd_Dist_R;
// TMAG5273 Midd_Dist_T;

// TMAG5273 Ring_Dist_L;
// TMAG5273 Ring_Dist_R;
// TMAG5273 Ring_Dist_T;

// TMAG5273 Pinky_Dist_L;
// TMAG5273 Pinky_Dist_R;
// TMAG5273 Pinky_Dist_T;


// float Th_Dist_L_X_init=0;
// float Th_Dist_R_X_init=0;
// float Th_Dist_T_X_init=0;

// float Idx_Dist_L_X_init=0;
// float Idx_Dist_R_X_init=0;
// float Idx_Dist_T_X_init=0;

// float Midd_Dist_L_X_init=0;
// float Midd_Dist_R_X_init=0;
// float Midd_Dist_T_X_init=0;

// float Ring_Dist_L_X_init=0;
// float Ring_Dist_R_X_init=0;
// float Ring_Dist_T_X_init=0;

// float Pinky_Dist_L_X_init=0;
// float Pinky_Dist_R_X_init=0;
// float Pinky_Dist_T_X_init=0;


// void TCA9548A(uint8_t bus, uint8_t address){
//   Wire.beginTransmission(address);  // TCA9548A address is 0x70
//   Wire.write(1 << bus);          // send byte to select bus
//   Wire.endTransmission();
//   // Serial.print("bus: ");
//   // Serial.print(bus);
//   // Serial.print(" of MUX address: ");
//   // Serial.println(address, HEX);
//   delay(20);
// }

// void TCA9548A_disconnect(uint8_t address){
//   Wire.beginTransmission(address);
//   Wire.write(0);  // no channel selected
//   Wire.endTransmission();
// }

// float get_sensor_value(TMAG5273 TMAG, bool print=false){
//   float X_sensor_value=0;
//   if(TMAG.getMagneticChannel() != 0)
//     {
//       X_sensor_value=TMAG.getXData();
//       if(print==true)
//       {
//         Serial.print(X_sensor_value);
//         Serial.print(", ");
//       }
      
//     }
//     else
//     {
//       X_sensor_value=0;
//       // Serial.print("not available ");
//     }

//   // Serial.print("returned value: ");  
//   // Serial.println(X_sensor_value);  
//   return X_sensor_value;
// }

// void get_initial_values(){
//   if (THUMB_CONNECTED==true)
//   {
//     TCA9548A(THUMB_BUS,THUMB_MUX); 
//     Th_Dist_L_X_init = get_sensor_value(Th_Dist_L);
//     Th_Dist_R_X_init = get_sensor_value(Th_Dist_R);
//     Th_Dist_T_X_init = get_sensor_value(Th_Dist_T);
//   }
//   // Serial.print(" | ");

//   if (IDX_CONNECTED==true)
//   {
//     TCA9548A(IDX_LEFT_BUS,IDX_MUX); 
//     Idx_Dist_L_X_init = get_sensor_value(Idx_Dist_L);

//     TCA9548A(IDX_RIGHT_BUS,IDX_MUX); 
//     Idx_Dist_R_X_init = get_sensor_value(Idx_Dist_R);
//     Idx_Dist_T_X_init = get_sensor_value(Idx_Dist_T);
//   }
//   // Serial.print(" | ");

//   if (MIDD_CONNECTED==true)
//   {
//     TCA9548A(MIDD_LEFT_BUS,MIDD_MUX);
//     Midd_Dist_L_X_init = get_sensor_value(Midd_Dist_L);

//     TCA9548A(MIDD_RIGHT_BUS,MIDD_MUX); 
//     Midd_Dist_R_X_init = get_sensor_value(Midd_Dist_R);
//     Midd_Dist_T_X_init = get_sensor_value(Midd_Dist_T);
//   }
//   // Serial.print(" | ");

//   TCA9548A_disconnect(0x70);

//   if (RING_CONNECTED==true)
//   {
//     TCA9548A(RING_LEFT_BUS,RING_MUX);
//     Ring_Dist_L_X_init = get_sensor_value(Ring_Dist_L);

//     TCA9548A(RING_RIGHT_BUS,RING_MUX); 
//     Ring_Dist_R_X_init = get_sensor_value(Ring_Dist_R);
//     Ring_Dist_T_X_init = get_sensor_value(Ring_Dist_T);
//   }
//   // Serial.print(" | ");

//   if (PINKY_CONNECTED==true)
//   {
//     TCA9548A(PINKY_LEFT_BUS,PINKY_MUX);
//     Pinky_Dist_L_X_init = get_sensor_value(Pinky_Dist_L);

//     TCA9548A(PINKY_RIGHT_BUS,PINKY_MUX); 
//     Pinky_Dist_R_X_init = get_sensor_value(Pinky_Dist_R);
//     Pinky_Dist_T_X_init = get_sensor_value(Pinky_Dist_T);
//   }
  
//   TCA9548A_disconnect(0x71);
// }

// void setup() {

//   Serial.begin(9600);

//   // put your setup code here, to run once:
//   pinMode(PMOS_PIN,OUTPUT);
//   pinMode(INDEX_PIN,OUTPUT);
//   pinMode(MIDDLE_PIN,OUTPUT);
//   pinMode(RING_PIN,OUTPUT);
  
//   pinMode(LED_BUILTIN,OUTPUT);

//   digitalWrite(LED_BUILTIN, HIGH);

//   digitalWrite(PMOS_PIN, HIGH); //TURN OFF THE POWER FOR TMAGs
//   digitalWrite(INDEX_PIN, LOW); //TURN OFF THE POWER FOR INDEX TMAG
//   digitalWrite(MIDDLE_PIN, LOW); //TURN OFF THE POWER FOR MIDDLE TMAG
//   digitalWrite(RING_PIN, LOW); //TURN OFF THE POWER FOR RING TMAG

//   digitalWrite(PMOS_PIN, LOW); //TURN ON THE POWER FOR TMAGs

//   Wire.begin();


//   TCA9548A_disconnect(0x70);
//   TCA9548A_disconnect(0x71);


//   TCA9548A(THUMB_BUS,THUMB_MUX); 
//   Th_Dist_L.begin(I2C_Add_Th_Dist_L, Wire);
//   Th_Dist_R.begin(I2C_Add_Th_Dist_R, Wire);
//   Th_Dist_T.begin(I2C_Add_Th_Dist_T, Wire);



//   TCA9548A(IDX_LEFT_BUS,IDX_MUX); 
//   Idx_Dist_L.begin(I2C_Add_Idx_Dist_L, Wire);
  
//   TCA9548A(IDX_RIGHT_BUS,IDX_MUX);
//   Idx_Dist_R.begin(I2C_Add_Idx_Dist_R, Wire);
//   Idx_Dist_T.begin(I2C_Add_Idx_Dist_T, Wire);



//   TCA9548A(MIDD_LEFT_BUS,MIDD_MUX); 
//   Midd_Dist_L.begin(I2C_Add_Midd_Dist_L, Wire);
  
//   TCA9548A(MIDD_RIGHT_BUS,MIDD_MUX);
//   Midd_Dist_R.begin(I2C_Add_Midd_Dist_R, Wire);
//   Midd_Dist_T.begin(I2C_Add_Midd_Dist_T, Wire);

//   TCA9548A_disconnect(0x70);



//   TCA9548A(RING_LEFT_BUS,RING_MUX); 
//   Ring_Dist_L.begin(I2C_Add_Ring_Dist_L, Wire);
  
//   TCA9548A(RING_RIGHT_BUS,RING_MUX);
//   Ring_Dist_R.begin(I2C_Add_Ring_Dist_R, Wire);
//   Ring_Dist_T.begin(I2C_Add_Ring_Dist_T, Wire);




//   TCA9548A(PINKY_LEFT_BUS,PINKY_MUX); 
//   Pinky_Dist_L.begin(I2C_Add_Pinky_Dist_L, Wire);
  
//   TCA9548A(PINKY_RIGHT_BUS,PINKY_MUX);
//   Pinky_Dist_R.begin(I2C_Add_Pinky_Dist_R, Wire);
//   Pinky_Dist_T.begin(I2C_Add_Pinky_Dist_T, Wire);

  
//   TCA9548A_disconnect(0x71);

//   delay(2000);
//   get_initial_values();

//   if(mode==PYTHON_MODE){
//     init_python_communication();
//   }
// }

// void loop() {

//   float Th_Dist_L_X=0;
//   float Th_Dist_R_X=0;
//   float Th_Dist_T_X=0;

//   float Idx_Dist_L_X=0;
//   float Idx_Dist_R_X=0;
//   float Idx_Dist_T_X=0;

//   float Midd_Dist_L_X=0;
//   float Midd_Dist_R_X=0;
//   float Midd_Dist_T_X=0;

//   float Ring_Dist_L_X=0;
//   float Ring_Dist_R_X=0;
//   float Ring_Dist_T_X=0;

//   float Pinky_Dist_L_X=0;
//   float Pinky_Dist_R_X=0;
//   float Pinky_Dist_T_X=0;

//   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

//   if (THUMB_CONNECTED==true)
//   {
//     TCA9548A(THUMB_BUS,THUMB_MUX); 
//     Th_Dist_L_X = get_sensor_value(Th_Dist_L)-Th_Dist_L_X_init;
//     Th_Dist_R_X = get_sensor_value(Th_Dist_R)-Th_Dist_R_X_init;
//     Th_Dist_T_X = get_sensor_value(Th_Dist_T)-Th_Dist_T_X_init;

//     if (mode==DEBUG_MODE){
//       Serial.print(Th_Dist_L_X);
//       Serial.print(", ");
//       Serial.print(Th_Dist_R_X);
//       Serial.print(", ");
//       Serial.print(Th_Dist_T_X);
//       Serial.print(" | ");
//     }
//     if (mode==PYTHON_MODE){
//       dataCarrier[0]=String(Th_Dist_L_X);
//       dataCarrier[1]=String(Th_Dist_R_X);
//       dataCarrier[2]=String(Th_Dist_T_X);
//     }
//   }

//   if (IDX_CONNECTED==true)
//   {
//     TCA9548A(IDX_LEFT_BUS,IDX_MUX); 
//     Idx_Dist_L_X = get_sensor_value(Idx_Dist_L)-Idx_Dist_L_X_init;

//     TCA9548A(IDX_RIGHT_BUS,IDX_MUX); 
//     Idx_Dist_R_X = get_sensor_value(Idx_Dist_R)-Idx_Dist_R_X_init;
//     Idx_Dist_T_X = get_sensor_value(Idx_Dist_T)-Idx_Dist_T_X_init;

//     if (mode==DEBUG_MODE){
//       Serial.print(Idx_Dist_L_X);
//       Serial.print(", ");
//       Serial.print(Idx_Dist_R_X);
//       Serial.print(", ");
//       Serial.print(Idx_Dist_T_X);
//       Serial.print(" | ");
//     }
//     if (mode==PYTHON_MODE){
//       dataCarrier[3]=String(Idx_Dist_L_X);
//       dataCarrier[4]=String(Idx_Dist_R_X);
//       dataCarrier[5]=String(Idx_Dist_T_X);
//     }
//   }


//   if (MIDD_CONNECTED==true)
//   {
//     TCA9548A(MIDD_LEFT_BUS,MIDD_MUX);
//     Midd_Dist_L_X = get_sensor_value(Midd_Dist_L)-Midd_Dist_L_X_init;

//     TCA9548A(MIDD_RIGHT_BUS,MIDD_MUX); 
//     Midd_Dist_R_X = get_sensor_value(Midd_Dist_R)-Midd_Dist_R_X_init;
//     Midd_Dist_T_X = get_sensor_value(Midd_Dist_T)-Midd_Dist_T_X_init;

//     if (mode==DEBUG_MODE){
//       Serial.print(Midd_Dist_L_X);
//       Serial.print(", ");
//       Serial.print(Midd_Dist_R_X);
//       Serial.print(", ");
//       Serial.print(Midd_Dist_T_X);
//       Serial.print(" | ");
//     }
//     if (mode==PYTHON_MODE){
//       dataCarrier[6]=String(Midd_Dist_L_X);
//       dataCarrier[7]=String(Midd_Dist_R_X);
//       dataCarrier[8]=String(Midd_Dist_T_X);
//     }
//   }

//   TCA9548A_disconnect(0x70);

//   if (RING_CONNECTED==true)
//   {
//     TCA9548A(RING_LEFT_BUS,RING_MUX);
//     Ring_Dist_L_X = get_sensor_value(Ring_Dist_L)-Ring_Dist_L_X_init;

//     TCA9548A(RING_RIGHT_BUS,RING_MUX); 
//     Ring_Dist_R_X = get_sensor_value(Ring_Dist_R)-Ring_Dist_R_X_init;
//     Ring_Dist_T_X = get_sensor_value(Ring_Dist_T)-Ring_Dist_T_X_init;

//     if (mode==DEBUG_MODE){
//       Serial.print(Ring_Dist_L_X);
//       Serial.print(", ");
//       Serial.print(Ring_Dist_R_X);
//       Serial.print(", ");
//       Serial.print(Ring_Dist_T_X);
//       Serial.print(" | ");
//     }
//     if (mode==PYTHON_MODE){
//       dataCarrier[9]=String(Ring_Dist_L_X);
//       dataCarrier[10]=String(Ring_Dist_R_X);
//       dataCarrier[11]=String(Ring_Dist_T_X);
//     }
//   }


//   if (PINKY_CONNECTED==true)
//   {
//     TCA9548A(PINKY_LEFT_BUS,PINKY_MUX);
//     Pinky_Dist_L_X = get_sensor_value(Pinky_Dist_L)-Pinky_Dist_L_X_init;

//     TCA9548A(PINKY_RIGHT_BUS,PINKY_MUX); 
//     Pinky_Dist_R_X = get_sensor_value(Pinky_Dist_R)-Pinky_Dist_R_X_init;
//     Pinky_Dist_T_X = get_sensor_value(Pinky_Dist_T)-Pinky_Dist_T_X_init;
    
    
//     if (mode==DEBUG_MODE){
//       Serial.print(Pinky_Dist_L_X);
//       Serial.print(", ");
//       Serial.print(Pinky_Dist_R_X);
//       Serial.print(", ");
//       Serial.print(Pinky_Dist_T_X);
//       Serial.print(" | ");
//     }
//     if (mode==PYTHON_MODE){
//       dataCarrier[12]=String(Pinky_Dist_L_X);
//       dataCarrier[13]=String(Pinky_Dist_R_X);
//       dataCarrier[14]=String(Pinky_Dist_T_X);
//     }
//   }
  
//   TCA9548A_disconnect(0x71);

//   if (mode==DEBUG_MODE){
//       Serial.println("");
//   }

//   if (mode==PYTHON_MODE){
//       dataCarrier[15]=String(1);
//       dataCarrier[16]=String(2);

//       load_msg_to_python(msgName, dataCarrier, size_of_array(msgName));
//       sync();
//     }
// }



