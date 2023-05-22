#include <PS4Controller.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, -1);
#define SDA_PIN 32
#define SCL_PIN 33

//im using a library i found on github, ive actually looked at the files and it covers everything on the controller, it can even get the controller's battery level,
// if i had more time i wouldve wired it to an oled as well to show the battery and other info



unsigned long lastTimeStamp = 0;

void notify() // the button states are returned as boolean values which was massively helpful, it made trouble shooting easy and later on, sending the data via i2c quite doable... once i understood i2c

{
  char messageString[200];
  sprintf(messageString, "%4d,%4d,%4d,%4d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d",
  PS4.LStickX(),
  PS4.LStickY(),
  PS4.RStickX(),
  PS4.RStickY(),
  PS4.Left(),
  PS4.Down(),
  PS4.Right(),
  PS4.Up(),
  PS4.Square(),
  PS4.Cross(),
  PS4.Circle(),
  PS4.Triangle(),
  PS4.L1(),
  PS4.R1(),
  PS4.L2(),
  PS4.R2(),  
  PS4.Share(),
  PS4.Options(),
  PS4.PSButton(),
  PS4.Touchpad(),
  PS4.Charging(),
  PS4.Audio(),
  PS4.Mic(),
  PS4.Battery());

  //Only needed to print the message properly on serial monitor. Else we dont need it.
  if (millis() - lastTimeStamp > 50)
  {
    Serial.println(messageString);
    lastTimeStamp = millis();
  }
}

void onConnect()
{
  Serial.println("Connected!.");
}

void onDisConnect()
{
  Serial.println("Disconnected!.");    
}

void setup() 
{
  Serial.begin(115200);
  PS4.attach(notify);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");// this is basically for when the esp is ready for the controller to connect to it
 Wire.begin(SDA_PIN, SCL_PIN);   
  
  
}

void loop() 
{

// instead of sending the x and y values of the joystick through i2c, i turned the x and y combinations into vectors, then calculated the angle and sent that through the i2c.


  int JoystickAngle = 0;
int x = map(PS4.LStickX(), -128, 127, -255, 255);
int y = map(PS4.LStickY(), -128, 127, -255, 255);

JoystickAngle = atan2(y - y_center, x - x_center) * 180 / PI;
if (JoystickAngle < 0 ) {
  JoystickAngle = 360 + JoystickAngle;
}

byte mappedAngle = map(JoystickAngle, 0, 360, 0, 255);// it took me a good 3 hours of trouble shooting before i remembered i2c only sends bytes, between 0-255, when my angle exceeded that it wrapped back to zero, I know forever now that i2c only sends bytes


 Serial.print(mappedAngle); 





  
//int LSY_mapped = map(PS4.LStickY(), -128, 127, 0, 255);
 // send the values over I2C
  Wire.beginTransmission(8);
  Wire.write(PS4.R2());
  Wire.write(PS4.L2());
  Wire.write(PS4.Up());
  Wire.write(PS4.Down());
  Wire.write(PS4.Triangle());
  Wire.write(mappedAngle);
  Wire.endTransmission();


  // delay to avoid flooding the I2C bus
  delay(50);



  }






