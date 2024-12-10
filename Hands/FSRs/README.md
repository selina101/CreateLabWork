# FSR finger sensors

# Code


# PCBs
In MainPCB_V3, do not use the DMP31D0U-7 MOSFET but instead use the BSS84. The teensy is not capable of delivering enough current to drive the DMP31D0U-7 gate. 

For each hand, you will need one Thumb_V1 FPCB, three Index_Middle_Ring_V3 FPCB, one Pinky_V1 and one MainPCB_V3. 

The hall sensors exist in three versions (with three different I2C addresses). The correct sensor placement is shown in 'FullHandDiagram.png'. 
![Full hand sensor positions](FullHandDiagram.png)
