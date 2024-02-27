
// #include<SoftwareSerial.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo servo1;
Servo servo2;
// Servo servo3;
// Servo servo4;

const int joystickThreshold = 512;
// Define the pins for motor control
int leftMotorForwardPin = 4;  // Replace with your actual pin numbers
int rightMotorForwardPin = 6;
int leftMotorBackwardPin = 3;
int rightMotorBackwardPin = 5;


RF24 radio(7, 8);  // CE, CSN
const byte addresses[6] = "00001";
String data1, data2, data3, data4, data5, data6;
int8_t indexOfA, indexOfB, indexOfC, indexOfD, indexOfE, indexOfF;
String DataIn;
int xcar;
int ycar;
int xrobo1;
int yrobo1;
int xrobo2;
int yrobo2;


int prevX = 0;
int prevY = 0;


// int M1;
// int Led  = 4;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, addresses);  // 00001
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  // pinMode(Led , OUTPUT);

  pinMode(leftMotorForwardPin, OUTPUT);
  pinMode(leftMotorBackwardPin, OUTPUT);
  pinMode(rightMotorForwardPin, OUTPUT);
  pinMode(rightMotorBackwardPin, OUTPUT);

  servo1.attach(9);   // Attach servo to pin 0
  servo2.attach(10);   // Attach servo to pin 1
  // servo3.attach(9);   // Attach servo to pin 6
  // servo4.attach(10);  // Attach servo to pin 9
}

void loop() {
  delay(50);
  char text[32] = "";

  if (radio.available()) {
    radio.read(&text, sizeof(text));
    Serial.println(text);
    for (int i = 0; i < sizeof(text); i++) {
      DataIn += text[i];
    }
    Serial.print("DataInString");
    Serial.println(DataIn);

    ParseTheData();
    Serial.println("Data1 : " + data1);
    Serial.println("Data2 : " + data2);
    Serial.println("Data3 : " + data3);
    Serial.println("Data4 : " + data4);
    Serial.println("Data5 : " + data5);
    Serial.println("Data6 : " + data6);
    Serial.println("----------------------------------------------------------");
    DataIn = "";

    // for(int i =0; i<sizeof(text); i++){
    //   DataIn += text[i];
    // }
    // Serial.print("DataInString");
    // Serial.println(DataIn);
    // ParseTheData();
    // Serial.println("Data1 : "+ data1);
    // Serial.println("Data2 : "+ data2);
    // Serial.println("Data3 : "+ data3);
    // Serial.println("Data4 : "+ data4);
    // Serial.println("----------------------------------------------------------");
    // DataIn = "";
    // }
  }

  xcar = data2.toInt();
  ycar = data1.toInt();
  xrobo1 = data3.toInt();
  yrobo1 = data4.toInt();
  xrobo2 = data5.toInt();
  yrobo2 = data6.toInt();


  // M1 = data1.toInt();

  // // Serial.print({"M1 : "}); Serial.println(M1);
  // if(M1 > 0 ){
  //   digitalWrite(Led, HIGH);
  //   // Serial.print("M1 Is high");
  // }
  // else{
  //   digitalWrite(Led, LOW);
  //   // Serial.print("M1 Is Low");

  if (xcar < joystickThreshold - 100) {
    // Turn left
    digitalWrite(leftMotorForwardPin, LOW);
    digitalWrite(leftMotorBackwardPin, LOW);
    digitalWrite(rightMotorForwardPin, HIGH);
    digitalWrite(rightMotorBackwardPin, LOW);
    Serial.println("turn left");
  } else if (xcar > joystickThreshold + 100) {
    // Turn right
    digitalWrite(leftMotorForwardPin, HIGH);
    digitalWrite(leftMotorBackwardPin, LOW);
    digitalWrite(rightMotorForwardPin, LOW);
    digitalWrite(rightMotorBackwardPin, LOW);
    Serial.println("turn right");

  } else {
    // Stop turning
    digitalWrite(leftMotorForwardPin, LOW);
    digitalWrite(leftMotorBackwardPin, LOW);
    digitalWrite(rightMotorForwardPin, LOW);
    digitalWrite(rightMotorBackwardPin, LOW);
    Serial.println("turn stop");

  }


  if (ycar < joystickThreshold - 100) {
    // Move forward
    digitalWrite(leftMotorForwardPin, HIGH);
    digitalWrite(leftMotorBackwardPin, LOW);
    digitalWrite(rightMotorForwardPin, HIGH);
    digitalWrite(rightMotorBackwardPin, LOW);
  } else if (ycar > joystickThreshold + 100) {
    // Move backward
    digitalWrite(leftMotorForwardPin, LOW);
    digitalWrite(leftMotorBackwardPin, HIGH);
    digitalWrite(rightMotorForwardPin, LOW);
    digitalWrite(rightMotorBackwardPin, HIGH);
  } else {
    // Stop moving
    digitalWrite(leftMotorForwardPin, LOW);
    digitalWrite(leftMotorBackwardPin, LOW);
    digitalWrite(rightMotorForwardPin, LOW);
    digitalWrite(rightMotorBackwardPin, LOW);
  }





  // int servo1Angle = map(xrobo2, 0, 1023, 0, 180);
  // int servo2Angle = map(yrobo2, 0, 1023, 0, 180);
  // int servo3Angle = map(xrobo2, 0, 1023, 0, 180);
  // int servo4Angle = map(yrobo2, 0, 1023, 0, 180);


 int angle1 = map(xrobo2, 0, 1023, 0, 180);
  int angle2 = map(yrobo2, 0, 1023, 0, 180);

  // Incrementally move the servo motors
  moveServoSmoothly(servo1, angle1, prevX);
  moveServoSmoothly(servo2, angle2, prevY);

  // Update previous joystick values
  prevX = angle1;
  prevY = angle2;


  // servo1.write(servo1Angle);
  // servo2.write(servo2Angle);
  // servo3.write(servo3Angle);
  // servo4.write(servo4Angle);


  // digitalWrite(leftMotorForwardPin, HIGH);
  //   digitalWrite(rightMotorForwardPin, HIGH);
  //   digitalWrite(leftMotorBackwardPin, LOW);
  //   digitalWrite(rightMotorBackwardPin, LOW);
  //   delay(2000);

  //   // Stop the motors for a moment
  //   digitalWrite(leftMotorForwardPin, LOW);
  //   digitalWrite(rightMotorForwardPin, LOW);
  //   digitalWrite(leftMotorBackwardPin, LOW);
  //   digitalWrite(rightMotorBackwardPin, LOW);
  //   delay(1000);

  //   // Backward motion for 2 seconds
  //   digitalWrite(leftMotorForwardPin, LOW);
  //   digitalWrite(rightMotorForwardPin, LOW);
  //   digitalWrite(leftMotorBackwardPin, HIGH);
  //   digitalWrite(rightMotorBackwardPin, HIGH);
  //   delay(2000);

  //   // Stop the motors for a moment
  //   digitalWrite(leftMotorForwardPin, LOW);
  //   digitalWrite(rightMotorForwardPin, LOW);
  //   digitalWrite(leftMotorBackwardPin, LOW);
  //   digitalWrite(rightMotorBackwardPin, LOW);
  //   delay(1000);

  //   // Left turn for 2 seconds
  //   digitalWrite(leftMotorForwardPin, LOW);
  //   digitalWrite(rightMotorForwardPin, HIGH);
  //   digitalWrite(leftMotorBackwardPin, HIGH);
  //   digitalWrite(rightMotorBackwardPin, LOW);
  //   delay(2000);

  //   // Stop the motors for a moment
  //   digitalWrite(leftMotorForwardPin, LOW);
  //   digitalWrite(rightMotorForwardPin, LOW);
  //   digitalWrite(leftMotorBackwardPin, LOW);
  //   digitalWrite(rightMotorBackwardPin, LOW);
  //   delay(1000);

  //   // Right turn for 2 seconds
  //   digitalWrite(leftMotorForwardPin, HIGH);
  //   digitalWrite(rightMotorForwardPin, LOW);
  //   digitalWrite(leftMotorBackwardPin, LOW);
  //   digitalWrite(rightMotorBackwardPin, HIGH);
  //   delay(2000);

  //   // Stop the motors for a moment
  //   digitalWrite(leftMotorForwardPin, LOW);
  //   digitalWrite(rightMotorForwardPin, LOW);
  //   digitalWrite(leftMotorBackwardPin, LOW);
  //   digitalWrite(rightMotorBackwardPin, LOW);
  //   delay(1000);





  // Serial.println("don");

  // Serial.println(text);
}

void moveServoSmoothly(Servo &servo, int targetAngle, int &prevAngle) {
  // Gradually move the servo towards the target angle
  if (targetAngle > prevAngle) {
    for (int i = prevAngle; i <= targetAngle; ++i) {
      servo.write(i);
      delay(10);
    }
  } else {
    for (int i = prevAngle; i >= targetAngle; --i) {
      servo.write(i);
      delay(10);
    }
  }

  // Update the previous angle to the target angle
  prevAngle = targetAngle;
}



void ParseTheData() {
  indexOfA = DataIn.indexOf("A");
  indexOfB = DataIn.indexOf("B");
  indexOfC = DataIn.indexOf("C");
  indexOfD = DataIn.indexOf("D");
  indexOfE = DataIn.indexOf("E");
  indexOfF = DataIn.indexOf("F");
  data1 = DataIn.substring(0, indexOfA);
  data2 = DataIn.substring(indexOfA + 1, indexOfB);
  data3 = DataIn.substring(indexOfB + 1, indexOfC);
  data4 = DataIn.substring(indexOfC + 1, indexOfD);
  data5 = DataIn.substring(indexOfD + 1, indexOfE);
  data6 = DataIn.substring(indexOfE + 1, indexOfF);
}
