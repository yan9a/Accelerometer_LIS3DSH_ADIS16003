#include <Wire.h>
int x,y,z;
float K=0.061; // (4000/65535) milli-g per digit for +/-2g full scale using 16 bit digital output
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Wire.beginTransmission(0x1E); // transmit to device #30
  Wire.write(0x20);//Send address of 'Control register 4' to write configuration
  Wire.write(0x7F);//Write a value that enables x,y,z accelerometers
  Wire.endTransmission();// stop transmitting
}

void loop()
{
  delay(1000);
  
  Wire.beginTransmission(0x1E); // transmit to device #30
  Wire.write(0x28);//Send address of LSB of x. Address is auto-increased after each reading.
  Wire.endTransmission();    // stop transmitting

  Wire.requestFrom(0x1E, 6);    // request 6 bytes from slave device #30
  x = Wire.read() | Wire.read()<<8; //x acceleration 
  y = Wire.read() | Wire.read()<<8; //y acceleration
  z = Wire.read() | Wire.read()<<8; //z acceleration
  
  Serial.println("x=" + String(K*x)+" mg  \ty=" + String(K*y)+" mg  \tz=" + String(K*z)+" mg");
}