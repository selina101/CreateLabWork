# Hand hall sensors

# Code

## To test the PCBs for the full hand:
1) upload the code 'FullHand_HallSensors' to the teensy. This code reads the data of all the sensors and sends it over serial so it can be read in a python script for example. This code does not work with Kai's framework to the full hand, but allows to easily test that all the sensors work correctly. 
2) Run the python code 'FullHand_visualisation' to be able to visualise in python all the sensors of the hand. The area of the circles are proportional to the sensor response.


## To build the PCBs for the full hand:
Upload the code 'FullHand_Haptic_ForAdaptHand' to the teensy. This codes collects the data for all the sensors. This makes is the code needed to connect the PCBs to Kai's framework for the full hand. 


## Arduino code description
- FullHand_HallSensors : This code reads the data of all the sensors and sends it over serial so it can be read in a python script for example.
- FullHand_Haptic : does the same as the 'FullHand_HallSensors' code (reads all the sensor data and sends it over serial) but has in addition the haptic feedback. It controls 5 vibration motor based on the tip sensor values.
-  FullHand_Haptic_ForAdaptHand : Reads all the sensor values. It is compatible with Kai's full hand framework.
-  SingleFinger_withSpringHallSensor : Code for the single finger setup. Reads the 7 hall sensor data + the hall sensor for the spring and sends the data over serial.

## Python code description
- FullHand_tip_visualisation : receives data via serial from the teensy (running the 'FullHand_HallSensors' or 'FullHand_Haptic' code) and displays circles whose area is proportional to the sensor readings. Works only with the tip sensors.
- FullHand_visualisation : receives data via serial from the teensy (running the 'FullHand_HallSensors' or 'FullHand_Haptic' code) and displays circles whose area is proportional to the sensor readings. Works for all the sensors. 


# PCBs
In MainPCB_V3, do not use the DMP31D0U-7 MOSFET but instead use the BSS84. The teensy is not capable of delivering enough current to drive the DMP31D0U-7 gate. 

For each hand, you will need one Thumb_V1 FPCB, three Index_Middle_Ring_V3 FPCB, one Pinky_V1 and one MainPCB_V3. 

The hall sensors exist in three versions (with three different I2C addresses). The correct sensor placement is shown in 'FullHandDiagram.png'. 
![Full hand sensor positions](FullHandDiagram.png)
