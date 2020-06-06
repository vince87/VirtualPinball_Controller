# Controller per virtual pinball totalmente programmabile e configurabile.

![Alt text](pinball_controller.jpg?raw=true "Pinball Controller")

sito di riferimento: https://www.vincenzobini.it/

Comincio a postare qui sorgenti e altro necessario per compilare il firmware.
Più avanti posto anche il gerber per la produzione delle PCB e il BOM

Sono graditi suggerimenti e sopratutto migliorie al codice.

Pinout della scheda:
![Alt text](Pinball_Controller_pinout.jpg?raw=true "Pinball Controller")

# Lista componenti:

1  10K              R1            0805
2	 330	            R2,R3	        0805
2  22	              R5,R4	        0805
4  1KΩ	            R7,R8,R9,R6	  0603_X4

1  100nF	          C2	          0805
2  22pF	            C5,C4	        0805
2  1uF	            C3,C1	        0805
1  GreenLED         TX	          0805
1  YellowLED        RX	          0805

1  ATMEGA32U4	      U1            QFP-44
1  MPU-6050 Module	U2
1  16MHz	          Y1	          OSC-49S-1	1
1  DIP Switch       SW1           SPST-NO
1  USB B 90         USB1          USB-M-49
4  CLIP-TERMINALI   P1,P2,P3,P4	  WJ250A-3.50-5P
1  HEADER 2x3   PASSO 2.54
1  HEADER 2x4   PASSO 2.54
