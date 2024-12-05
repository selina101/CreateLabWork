void setup() {

  Serial.begin(9600);
  
  pinMode(A1, INPUT); //Temperature sensor 1
  pinMode(A2, INPUT); //Temperature sensor 2
  pinMode(A3, INPUT); //Temperature sensor 3
  pinMode(A4, INPUT); //Temperature sensor 4
  pinMode(A5, INPUT); //Temperature sensor 5

}



void loop() {
  float TempSensor1 = analogRead(A1); 
  TempSensor1=TempSensor1/1023*3.3*1000; // get in mV
  TempSensor1=TempSensor1/20; //get the results in C --> 20mv / degC

  float TempSensor2 = analogRead(A2);
  TempSensor2=TempSensor2/1023*3.3*1000; // get in mV
  TempSensor2=TempSensor2/20; //get the results in C --> 20mv / degC
  
  float TempSensor3 = analogRead(A3);
  TempSensor3=TempSensor3/1023*3.3*1000; // get in mV
  TempSensor3=TempSensor3/20; //get the results in C --> 20mv / degC
  
  float TempSensor4 = analogRead(A4);
  TempSensor4=TempSensor4/1023*3.3*1000; // get in mV
  TempSensor4=TempSensor4/20; //get the results in C --> 20mv / degC
  
  float TempSensor5 = analogRead(A5);
  TempSensor5=TempSensor5/1023*3.3*1000; // get in mV
  TempSensor5=TempSensor5/20; //get the results in C --> 20mv / degC

  Serial.print("T1 = ");
  Serial.print(TempSensor1); 
  Serial.print(" || ");
  Serial.print("T2 = ");
  Serial.print(TempSensor2);
  Serial.print(" || ");
  Serial.print("T3 = ");
  Serial.print(TempSensor3);
  Serial.print(" || ");
  Serial.print("T4 = ");
  Serial.print(TempSensor4);
  Serial.print(" || ");
  Serial.print("T5 = ");
  Serial.println(TempSensor5);

  delay(100);

}
