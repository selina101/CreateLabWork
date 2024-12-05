#include <Wire.h>  // Used to establish serial communication on the I2C bus
#include "SparkFun_TMAG5273_Arduino_Library.h" // Used to send and recieve specific information from our sensor

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

#define HAPTIC_THUMB 14
#define HAPTIC_IDX 15
#define HAPTIC_MIDD 8
#define HAPTIC_RING 23
#define HAPTIC_PINKY 22


float datas[29];

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
}

void TCA9548A_disconnect(uint8_t address){
  Wire.beginTransmission(address);
  Wire.write(0);  // no channel selected
  Wire.endTransmission();
}

float get_sensor_value(TMAG5273 TMAG){
  float X_sensor_value=0;
  if(TMAG.getMagneticChannel() != 0)
    {
      X_sensor_value=TMAG.getXData();
    }
    else
    {
      X_sensor_value=0;
    }

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

void haptic_motor_value(int Dist_L_X, int Dist_R_X, int motor_pin){
  
  float mean_dist_value = (abs(Dist_L_X)+abs(Dist_R_X))/2;
  int motor_value=map(mean_dist_value, 0, 9, 255, 0);
  
  if (motor_value<0)
  {
    motor_value=0;
  }
  if (motor_value>255)
  {
    motor_value=255;
  }
  if(mean_dist_value<1.5)
  {
    motor_value=255;
  }
  
  analogWrite(motor_pin, motor_value);

}


void setup() {
  Serial.begin(115200);

  // put your setup code here, to run once:
  pinMode(PMOS_PIN,OUTPUT);
  pinMode(INDEX_PIN,OUTPUT);
  pinMode(MIDDLE_PIN,OUTPUT);
  pinMode(RING_PIN,OUTPUT);
  
  pinMode(LED_BUILTIN,OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(HAPTIC_THUMB,OUTPUT);
  digitalWrite(HAPTIC_THUMB, HIGH); 

  pinMode(HAPTIC_IDX,OUTPUT);
  digitalWrite(HAPTIC_IDX, HIGH); 
  
  pinMode(HAPTIC_MIDD,OUTPUT);
  digitalWrite(HAPTIC_MIDD, HIGH);
  
  pinMode(HAPTIC_RING,OUTPUT);
  digitalWrite(HAPTIC_RING, HIGH);
  
  pinMode(HAPTIC_PINKY,OUTPUT);
  digitalWrite(HAPTIC_PINKY, HIGH);

  digitalWrite(PMOS_PIN, HIGH); //TURN OFF THE POWER FOR TMAGs

  digitalWrite(INDEX_PIN, LOW); //TURN OFF THE POWER FOR INDEX TMAG
  digitalWrite(MIDDLE_PIN, LOW); //TURN OFF THE POWER FOR MIDDLE TMAG
  digitalWrite(RING_PIN, LOW); //TURN OFF THE POWER FOR RING TMAG

  Wire.begin();

  TCA9548A_disconnect(0x70);
  TCA9548A_disconnect(0x71);

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
}

void loop() {
  // digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  if (THUMB_CONNECTED==true)
  {
    TCA9548A(THUMB_BUS,THUMB_MUX); 
    datas[0] = get_sensor_value(Th_Dist_L)-Th_Dist_L_X_init;
    datas[1] = get_sensor_value(Th_Dist_R)-Th_Dist_R_X_init;
    datas[2] = get_sensor_value(Th_Dist_T)-Th_Dist_T_X_init;
  }

  if (IDX_CONNECTED==true)
  {
    TCA9548A(IDX_LEFT_BUS,IDX_MUX); 
    datas[3] = get_sensor_value(Idx_Dist_L)-Idx_Dist_L_X_init;
    datas[4] = get_sensor_value(Idx_Midd_L)-Idx_Midd_L_X_init;
    datas[5] = get_sensor_value(Idx_Prox_L)-Idx_Prox_L_X_init;

    TCA9548A(IDX_RIGHT_BUS,IDX_MUX); 
    datas[6] = get_sensor_value(Idx_Dist_R)-Idx_Dist_R_X_init;
    datas[7] = get_sensor_value(Idx_Dist_T)-Idx_Dist_T_X_init;
    datas[8] = get_sensor_value(Idx_Midd_R)-Idx_Midd_R_X_init;
    datas[9] = get_sensor_value(Idx_Prox_R)-Idx_Prox_R_X_init;
  }


  if (MIDD_CONNECTED==true)
  {
    TCA9548A(MIDD_LEFT_BUS,MIDD_MUX);
    datas[10] = get_sensor_value(Midd_Dist_L)-Midd_Dist_L_X_init;
    datas[11] = get_sensor_value(Midd_Midd_L)-Midd_Midd_L_X_init;
    datas[12] = get_sensor_value(Midd_Prox_L)-Midd_Prox_L_X_init;

    TCA9548A(MIDD_RIGHT_BUS,MIDD_MUX); 
    datas[13] = get_sensor_value(Midd_Dist_R)-Midd_Dist_R_X_init;
    datas[14] = get_sensor_value(Midd_Dist_T)-Midd_Dist_T_X_init;
    datas[15] = get_sensor_value(Midd_Midd_R)-Midd_Midd_R_X_init;
    datas[16] = get_sensor_value(Midd_Prox_R)-Midd_Prox_R_X_init;
  }

  TCA9548A_disconnect(0x70);

  if (RING_CONNECTED==true)
  {
    TCA9548A(RING_LEFT_BUS,RING_MUX);
    datas[17] = get_sensor_value(Ring_Dist_L)-Ring_Dist_L_X_init;
    datas[18] = get_sensor_value(Ring_Midd_L)-Ring_Midd_L_X_init;
    datas[19] = get_sensor_value(Ring_Prox_L)-Ring_Prox_L_X_init;

    TCA9548A(RING_RIGHT_BUS,RING_MUX); 
    datas[20] = get_sensor_value(Ring_Dist_R)-Ring_Dist_R_X_init;
    datas[21] = get_sensor_value(Ring_Dist_T)-Ring_Dist_T_X_init;
    datas[22] = get_sensor_value(Ring_Midd_R)-Ring_Midd_R_X_init;
    datas[23] = get_sensor_value(Ring_Prox_R)-Ring_Prox_R_X_init;
  }


  if (PINKY_CONNECTED==true)
  {
    TCA9548A(PINKY_LEFT_BUS,PINKY_MUX);
    datas[24] = get_sensor_value(Pinky_Dist_L)-Pinky_Dist_L_X_init;
    datas[25] = get_sensor_value(Pinky_Prox_L)-Pinky_Prox_L_X_init;

    TCA9548A(PINKY_RIGHT_BUS,PINKY_MUX); 
    datas[26] = get_sensor_value(Pinky_Dist_R)-Pinky_Dist_R_X_init;
    datas[27] = get_sensor_value(Pinky_Dist_T)-Pinky_Dist_T_X_init;
    datas[28] = get_sensor_value(Pinky_Prox_R)-Pinky_Prox_R_X_init;
  }
  
  TCA9548A_disconnect(0x71);

  for(int i = 0; i<29; i++){
    Serial.print(datas[i]); Serial.print(",");
  }
  Serial.println("");


  haptic_motor_value(datas[0],datas[1], HAPTIC_THUMB); //Th_Dist_L_X,Th_Dist_R_X
  haptic_motor_value(datas[3],datas[6], HAPTIC_IDX); //Idx_Dist_L_X,Idx_Dist_R_X,
  haptic_motor_value(datas[10],datas[13], HAPTIC_MIDD);//Midd_Dist_L_X,Midd_Dist_R_X,
  haptic_motor_value(datas[17],datas[20], HAPTIC_RING);//Ring_Dist_L_X,Ring_Dist_R_X,
  haptic_motor_value(datas[24],datas[26], HAPTIC_PINKY);//Pinky_Dist_L_X,Pinky_Dist_R_X,


}
