#include "pyCommsLib.h"



// #define DEBUG true
#define DEBUG false



const uint8_t output_pins[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
const uint8_t input_pins[] = { A0, A1, A2, A3, A6, A7 };

const int num_output_pins = sizeof(output_pins) / sizeof(output_pins[0]);
const int num_input_pins = sizeof(input_pins) / sizeof(input_pins[0]);

int results_values[num_output_pins][num_input_pins];


String msgName[num_output_pins*num_input_pins];
String dataCarrier[num_output_pins*num_input_pins+1];






void setup() {

  Serial.begin(9600);
  delay(10);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);


  for (int i = 0; i < num_output_pins; i++) {
    pinMode(output_pins[i], OUTPUT);
    digitalWrite(output_pins[i], LOW);
  }

  for (int i = 0; i < num_input_pins; i++) {
    pinMode(input_pins[i], INPUT);
  }

  if (DEBUG)
  {
    Serial.print("number of output pins = ");
    Serial.print(num_output_pins);
    Serial.print("     number of input pins = ");
    Serial.print(num_input_pins);
  }

  if(!DEBUG) //If python communication
  {
    
    int index = 0; // Index for the 1D array
    for (int i = 0; i < num_output_pins; i++) {
      for (int j = 0; j < num_input_pins; j++) {
        msgName[index] = "value_" + String(i) + "_" + String(j); // Generate name
        index++;
      }
    }

    delay(10);
    
    init_python_communication();
  }
}






void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  for (int i = 0; i < num_output_pins; i++) 
  {
    digitalWrite(output_pins[i], HIGH);

    for (int j = 0; j < num_input_pins; j++) 
    {
      // results_values[i][j] = analogRead(input_pins[j]);
      results_values[i][j] = random(0,1023);
    }
    digitalWrite(output_pins[i], LOW);
  }


  if (DEBUG)
  {
    for (int i = 0; i < num_output_pins; i++) 
    {
      for (int j= 0; j < num_input_pins; j++) 
      {
        // Serial.print(analogRead(input_pins[j]));
          Serial.print(results_values[i][j]);
          Serial.print("\t");
      }
      Serial.println();
    }
    Serial.println();
    Serial.println();
    Serial.println();
  }

  if (!DEBUG)
  {
    // dataCarrier[9]=String(0);
    for (int i = 0; i < num_output_pins; i++) 
    {
      for (int j= 0; j < num_input_pins; j++) 
      {
        dataCarrier[num_input_pins*i+j]=String(results_values[i][j]);
      }
    }

    load_msg_to_python(msgName, dataCarrier, size_of_array(msgName));
    sync();
  }

  
  // delay(100);

}
