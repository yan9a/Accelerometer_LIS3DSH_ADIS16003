#include <SPI.h>
const int CS_Pin = 10;// set pin 10 as the chip select
SPISettings settingsA(2000000, MSBFIRST, SPI_MODE3); // set up the speed, data order and data mode
//SPI pin configuration: pin 11 as MOSI (SDI), pin 12 as MISO (SDO) , pin 13 as clock (SPC)

int x,y,z;
float K=0.061; // (4000/65535) milli-g per digit for +/-2g full scale using 16 bit digital output

void setup() {
  Serial.begin(9600);
  pinMode (CS_Pin, OUTPUT);  //Chip Select pin to control SPI
  digitalWrite(CS_Pin, HIGH);//Disable SPI
  SPI.begin();
  SPI.beginTransaction(settingsA);

  digitalWrite(CS_Pin, LOW);//Enable SPI
  SPI.transfer(0x20);//Send address of 'Control register 4' to write configuration
  SPI.transfer(0x7F);//Write a value that enables x,y,z accelerometers
  digitalWrite(CS_Pin, HIGH);//Disable SPI
}

void loop() {
  delay(1000);
  digitalWrite(CS_Pin, LOW);//Enable SPI
  SPI.transfer(0xA8);//Send address of LSB of x. Address is auto-increased after each reading.
  x = SPI.transfer(0) | SPI.transfer(0)<<8; //x acceleration 
  y = SPI.transfer(0) | SPI.transfer(0)<<8; //y acceleration
  z = SPI.transfer(0) | SPI.transfer(0)<<8; //z acceleration
  digitalWrite(CS_Pin, HIGH);//Disable SPI
  Serial.println("x=" + String(K*x)+" mg  \ty=" + String(K*y)+" mg  \tz=" + String(K*z)+" mg");
}