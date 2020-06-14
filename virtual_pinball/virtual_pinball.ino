// A0,A1,A2,A3 sono contatti analogici programmabili
// A4,A5,D0,D1,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13 sono INGRESSI digitali pull-up
//D14,D15,D16 sono pin in/out digitali, si trovano sul connettore icsp
//è possibile aggiungere un estensore di ingressi/uscite tipo mcp23017 tramite il connettore ESP

char fw_version[] = "0.1";

#include <Wire.h>
#include <Joystick.h>
#include <Keyboard.h>

int Vibrazione = 250;  //<< IMPOSTABILE. Aumenta il valore se il controller ti sembra troppo sensibile ai tuoi movimenti da fermo.
int sens = 2500;  //<< IMPOSTABILE. Aumenta il valore se il controller si sposta troppo quando lo colpisci.
//int sensibilita_digitale = 100; //<< IMPOSTABILE.


const int MPU=0x68; 

int16_t AcX, AcY, AcZ; 

int16_t xCenter, yCenter, prevAcX, prevAcY;

int JoyX, JoyY, JoyZ;  


  //SETUP
void setup(){
  Serial.begin(9600);

  for (int i = 0; i < 13; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);

  //Begin Wire communication
  Wire.begin(); 
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); //PWR_MGMT_1 register
  Wire.write(0);//wakes up the MPU-6050
  Wire.endTransmission(true);

  //Begin joystick emulation
  Joystick.begin();
  Serial.println(F("Inizializzazione joystick completa!"));
  Keyboard.begin(); // Inizializzo la tastiera
  Serial.println(F("Inizializzazione tastiera completa!"));
}

void loop() {
  int plunger = analogRead(A0);
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  AcX = Wire.read()<<8|Wire.read();//0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
  AcY = Wire.read()<<8|Wire.read();//0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read()<<8|Wire.read();//0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  if (AcX>=prevAcX-Vibrazione && AcX<=prevAcX+Vibrazione){xCenter=AcX;}
  if (AcY>=prevAcY-Vibrazione && AcY<=prevAcY+Vibrazione){yCenter=AcY;}

  JoyX = map(AcX-xCenter, -sens, sens, -127, 127);
  JoyY = map(AcY-yCenter, -sens, sens, -127, 127);
  JoyZ = map(plunger, 0, 1023, -127, 127);
  
  if (JoyX>127){JoyX=127;} else if (JoyX<-127){JoyX=-127;}
  if (JoyY>127){JoyY=127;} else if (JoyY<-127){JoyY=-127;}
  Joystick.setYAxis(JoyY);
  Joystick.setXAxis(JoyX);
  Joystick.setZAxis(JoyZ);

  prevAcX = AcX;
  prevAcY = AcY;

  if (digitalRead(A4) == LOW) { Keyboard.press(99); } else { Keyboard.release(99); } //c
  if (digitalRead(A5) == LOW) { Keyboard.press(72+136); } else { Keyboard.release(72+136); } //pause
  if (digitalRead(0) == LOW) { Keyboard.press(KEY_ESC); } else { Keyboard.release(KEY_ESC); } //esc
  if (digitalRead(1) == LOW) { Keyboard.press(KEY_RETURN); } else { Keyboard.release(KEY_RETURN); } //enter
  if (digitalRead(4) == LOW) { Keyboard.press(122); } else { Keyboard.release(122); } //z
  if (digitalRead(5) == LOW) { Keyboard.press(120); } else { Keyboard.release(120); } //x
  if (digitalRead(6) == LOW) { Keyboard.press(108); } else { Keyboard.release(108); } //l
  if (digitalRead(7) == LOW) { Keyboard.press(114); } else { Keyboard.release(114); } //r
  if (digitalRead(8) == LOW) { Keyboard.press(49); } else { Keyboard.release(49); } //1
  if (digitalRead(9) == LOW) { Keyboard.press(53); } else { Keyboard.release(53); } //5
  if (digitalRead(10) == LOW) { Keyboard.press(KEY_UP_ARROW); } else { Keyboard.release(KEY_UP_ARROW); } //freccia su
  if (digitalRead(11) == LOW) { Keyboard.press(KEY_DOWN_ARROW); } else { Keyboard.release(KEY_DOWN_ARROW); } //freccia giu
  if (digitalRead(12) == LOW) { Keyboard.press(KEY_LEFT_ARROW); } else { Keyboard.release(KEY_LEFT_ARROW); } //freccia sx
  if (digitalRead(13) == LOW) { Keyboard.press(KEY_RIGHT_ARROW); } else { Keyboard.release(KEY_RIGHT_ARROW); } //freccia dx

  
//  if (JoyX > sensibilita_digitale) { Keyboard.press(100); } else { Keyboard.release(100); } //d
//  if (JoyX < -sensibilita_digitale) { Keyboard.press(97); } else { Keyboard.release(97); } //a
//  if (JoyY > sensibilita_digitale) { Keyboard.press(119); } else { Keyboard.release(119); } //w
//  if (JoyY < -sensibilita_digitale) { Keyboard.press(115); } else { Keyboard.release(115); } //s
}
