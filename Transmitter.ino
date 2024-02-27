#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
char strData[12];
const byte addresses[6] = "00001";
const int xRobo1 = A0;
const int yRobo1 = A1;
const int xRobo2 = A2;
const int yRobo2 = A3;
const int xCar = A4;
const int yCar = A5;
int xcar;
int ycar;
int xrobo1;
int yrobo1;
int xrobo2;
int yrobo2;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop() {
  xcar = analogRead(xCar);
  ycar = analogRead(yCar);
  xrobo1 = analogRead(xRobo1);
  yrobo1 = analogRead(yRobo1);
  xrobo2 = analogRead(xRobo2);
  yrobo2 = analogRead(yRobo2);
String DATA = String(xcar) + "A"+String(ycar) + "B" + String(xrobo1) + "C" + String(yrobo1) + "D" + String(xrobo2) + "E" + String(yrobo2) + "F" ;
  Serial.println(DATA);
  Serial.println();
  radio.write(DATA.c_str(), DATA.length()+1);
  delay(20);
  // Print the joystick values to the serial monitor
  Serial.print("x1: ");
  Serial.print(xcar);
  Serial.print("\t");
  Serial.print("y1: ");
  Serial.println(ycar);

  Serial.print("x2: ");
  Serial.print(xrobo1);
  Serial.print("\t");
  Serial.print("y2: ");
  Serial.println(yrobo1);  
  
  Serial.print("x3: ");
  Serial.print(xrobo2);
  Serial.print("\t");
  Serial.print("y3: ");
  Serial.println(yrobo2);
}










