#include <Wire.h>
#include <motor.h>
#define Aa 7 //motor pins
#define Ab 5
#define Ba 8
#define Bb 6
#define SPEED 120
bool RT, LT, Up, Down, Triangle;
int JoystickAngle;





Motor move;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  move.init();
  digitalWrite(3, OUTPUT);
  pinMode(3, 1);
}

void loop() {

  

switch (RT) { // i discovered early on that my controller actually had dead zones, even if i didnt touch the joystick it would still read a couple digits which in turn would form an angle and move the car, to remedy this i added the right trigger to be held first for the car to move, like a gas pedal.
  case 1:
    switch (JoystickAngle) {
      case 0 ... 19:
      case 342 ... 361:
        move.RIGHT();
        break;
      case 20 ... 45:
        move.FRR();
        break;  
      case 46 ... 71:
        move.FFR();
        break;
      case 72 ... 112:
        move.FWD();
        break;
      case 113 ... 138:
        move.FFL();
        break;
      case 139 ... 164:
        move.FLL();
        break;       
      case 165 ... 205:
        move.LEFT();
        break;


    }
    break;
  default:
    move.stop();
    break;
}
   switch (LT) {
  case 1:
     move.back();
        break;
}


  
// this was for troubleshooting and making sure the arduino was reading the button inputs
  Serial.print("RT: ");
  Serial.print(RT);
  Serial.print("\t");
  Serial.print("LT: ");
  Serial.print(LT);
  Serial.print("\t");
  Serial.print("UP: ");
  Serial.print(Up);
  Serial.print("\t");
  Serial.print("DOWN: ");
  Serial.print(Down);
  Serial.print("\t");
  Serial.print("TRIANGLE: ");
  Serial.print(Triangle);
  Serial.print("\t");
  Serial.print("\tAngle: ");
  Serial.println(JoystickAngle);
  Serial.println();
  digitalWrite(7, RT);
}

void receiveEvent(int bytes) {// receive the i2c info
  if (bytes == 6) {
    RT = Wire.read();
    LT = Wire.read();
    Up = Wire.read();
    Down = Wire.read();
    Triangle = Wire.read();
     byte mappedAngle = Wire.read();
      JoystickAngle = map(mappedAngle, 0, 255, 0, 360); // here i remapped the angle back to 360 degrees
  }
}



